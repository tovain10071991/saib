/*********************************************
 * 文件名：		saib.cpp
 * 文件描述：	静态分析主文件
 * 创建人：		skyin, 1025年11月12日
 * 版本号：		1.0
 * 修改记录：	第一次创建
*********************************************/

#include "../include/common.h"
#include <string>

using namespace std;

/*===========================================
 * 函数名：	main
 * 参数：
 *			argc
 *			argv
 *	功能描述：读取二进制文件，遍历指令，分析其中的间接分支指令，找到操作数的定值Value，从而判断间接分支指令的目标地址
 *	返回值
 *	抛出异常
===========================================*/
int main(int argc, const char** argv)
{
#ifdef DEBUG
	debug_output_with_FILE(stderr, "now is debug mode\n");
#endif
	//读取二进制文件，全局初始化
	global_init();
	parse_bitcode(get_bitcode(string(argv[1])));
	//遍历指令
//	global_end();
	return 0;
}
