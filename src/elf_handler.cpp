/*********************************************
 * 文件名：		elf_handler.cpp
 * 文件描述：	elf相关的源文件，定义了一些与libelf有关的函数
 * 创建人：		skyin, 1025年11月13日
 * 版本号：		1.0
 * 修改记录：	第一次创建
*********************************************/

#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <gelf.h>		//libelf头文件

using namespace std;

static int fd;
//程序一次执行只会读取一个二进制文件，所有elf相关的对象都做为static放在这里吧
static Elf* elf;

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
}
