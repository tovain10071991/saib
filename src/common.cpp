/*********************************************
 * 文件名：		common.cpp
 * 文件描述：	公共源文件，定义了一些与具体库无关的函数，或对具体库函数封装的函数
 * 创建人：		skyin, 1025年11月12日
 * 版本号：		1.0
 * 修改记录：	第一次创建
*********************************************/
#include <string>
#include "../include/common.h"

using namespace std;

#ifdef DEBUG
std::map<std::string, int> file_count;
#endif

static uint32_t current_offset = 0;		//当前返回的指令字节的文件偏移，初始为0，表示第一次要返回第一个指令字节，下次再为0表示遍历结束
static int current_execSec_index = -1;	//当前可执行节索引，可用来访问可执行节列表。初始为-1，表示还未开始读

/*===========================================
 * 函数名：	global_init
 * 参数：
 *			string file_path：二进制文件路径，初始化elf和dwarf需要
 *	功能描述：全局初始化，该程序会用到libelf, libdwarf, llvm, clang, xed。该函数需对这些库进行初始化操作
 *	返回值
 *	抛出异常
===========================================*/
void global_init()
{
//	llvm_init();
//	clang_init();
}
