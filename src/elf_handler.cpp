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

using namespace std;

static int fd;
//程序一次执行只会读取一个二进制文件，所有elf相关的对象都做为static放在这里吧
static Elf* elf;

void create_function_list();

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
	//创建函数列表，在common.cpp中遍历指令字节需要
	create_function_list();
}

/*===========================================
 * 函数名：	create_function_list
 * 参数：用static的变量
 *	功能描述：创建函数列表
 *	返回值：void
 *	抛出异常
===========================================*/
void create_function_list()
{
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
