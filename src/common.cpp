/*********************************************
 * 文件名：		common.cpp
 * 文件描述：	公共源文件，定义了一些与具体库无关的函数，或对具体库函数封装的函数
 * 创建人：		skyin, 1025年11月12日
 * 版本号：		1.0
 * 修改记录：	第一次创建
*********************************************/
#include <string>
#include "../include/elf_handler.h"

using namespace std;

/*===========================================
 * 函数名：	global_init
 * 参数：
 *			string file_path：二进制文件路径，初始化elf和dwarf需要
 *	功能描述：全局初始化，该程序会用到libelf, libdwarf, llvm, clang, xed。该函数需对这些库进行初始化操作
 *	返回值
 *	抛出异常
===========================================*/
void global_init(const string& file_path)
{
	init_elf(file_path);		//初始化elf
//	init_dwarf(fie_path);
//	xed_init();
//	llvm_init();
//	clang_init();
}
