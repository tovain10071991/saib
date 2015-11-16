/*********************************************
 * 文件名：		elf_handler.cpp
 * 文件描述：	elf相关的源文件，定义了一些与libelf有关的函数
 * 创建人：		skyin, 1025年11月13日
 * 版本号：		1.0
 * 修改记录：	第一次创建
*********************************************/

#include <string>
#include <gelf.h>		//libelf头文件
#include "../include/elf_handler.h"
#include "../include/common.h"
#include <map>

using namespace std;

typedef GElf_Shdr sec_info_t;
static map<int, sec_info_t> sec_info_set;	//节号对应节信息

static int fd;
//程序一次执行只会读取一个二进制文件，所有elf相关的对象都做为static放在这里吧
static Elf* elf;
static char* file_rawdata;
static size_t file_size;

void create_execSec_set();

/*===========================================
 * 函数名：	init_elf
 * 参数：
 *			const string& file_path：二进制文件，创建Elf对象需要绑定文件描述符
 *	功能描述：初始化elf。利用libelf读取二进制文件的信息和内容
 *	返回值：void，只准成功
 *	抛出异常
===========================================*/
void init_elf(const string& file_path)
{
	//打开文件，设置文件描述符
	fd = open(file_path.c_str(), O_RDONLY);
	if(fd==-1)
		err(errno, "open file <%s> failed", file_path.c_str());
	if(elf_version(EV_CURRENT)==EV_NONE)
		errx(elf_errno(), "elf_version failed: %s\n", elf_errmsg(elf_errno()));

	//创建Elf对象
	elf = elf_begin(fd, ELF_C_READ, NULL);
	if(elf==NULL)
		errx(elf_errno(), "elf_begin failed: %s\n", elf_errmsg(elf_errno()));
	
	//其他初始化工作
	file_rawdata = elf_rawfile(elf, &file_size);
	if(file_rawdata==NULL)
		errx(elf_errno(), "elf_rawfile failed: %s\n", elf_errmsg(elf_errno()));
#ifdef DEBUG
	debug_output_with_filePath("out/file_rawdata.out", "%zu\n", file_size);
	int j=0;
	for(size_t i=0; i<file_size; ++i)
	{
		debug_output_with_filePath("out/file_rawdata.out", "%x\t", (uint8_t)file_rawdata[i]);
		++j;
		if(j==15)
		{
			j=0;
			debug_output_with_filePath("out/file_rawdata.out", "\n");
		}
	}
#endif

	//创建可执行节列表，在common.cpp中遍历指令字节需要
	create_execSec_set();
}

/*===========================================
 * 函数名：	create_execSec_list
 * 参数：用static的变量
 *	功能描述：创建可执行节列表
 *	返回值：void
 *	抛出异常
===========================================*/
void create_execSec_set()
{
	GElf_Ehdr ehdr;
	if(gelf_getehdr(elf, &ehdr)==NULL)
		errx(elf_errno(), "elf_getehdr failed: %s\n", elf_errmsg(elf_errno()));

	GElf_Shdr shdr;
	int sec_ndx = 1;		//大概scn的遍历是从索引为1的节开始的
	Elf_Scn* scn = NULL;
	while((scn=elf_nextscn(elf, scn))!=NULL)
	{
		if(gelf_getshdr(scn, &shdr)==NULL)
			errx(elf_errno(), "gelf_getshdr failed: %s\n", elf_errmsg(elf_errno()));
		if((shdr.sh_type == SHT_PROGBITS) && (shdr.sh_flags & SHF_EXECINSTR))
		{
			sec_info_set[sec_ndx] = shdr;
		}
		++sec_ndx;
	}
#ifdef DEBUG
	for(auto iter=sec_info_set.begin(); iter!=sec_info_set.end(); ++iter)
		debug_output_with_filePath("out/xec_info_set.out", "%d\n", iter->first);
#endif
}

/*===========================================
 * 函数名：	get_byte_set_from_offset
 * 参数：
 *			const string& file_path：二进制文件，创建Elf对象需要绑定文件描述符
 *	功能描述：根据文件偏移读取字节集
 *	返回值：byte_set_t
 *	抛出异常
===========================================*/
byte_set_t get_byte_set_from_offset(uint32_t offset)
{
	if(offset>file_size)
		errx(-1, "off>file_size");
	if(lseek(fd, offset, SEEK_SET)==-1)
		err(errno, "seek in offset <%u> failed in get_byte_set_from_offset", offset);
	byte_set_t byte_set;
	read(fd, byte_set.data(), 15);

#ifdef DEBUG
	for(auto iter=byte_set.begin(); iter!=byte_set.end(); ++iter)
		debug_output_with_filePath("out/btye_set.out", "%x\t", *iter);
	debug_output_with_filePath("out/btye_set.out", "\n");
#endif
	return byte_set;
}
