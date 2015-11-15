/*********************************************
 * 文件名：		common.cpp
 * 文件描述：	公共源文件，定义了一些与具体库无关的函数，或对具体库函数封装的函数
 * 创建人：		skyin, 1025年11月12日
 * 版本号：		1.0
 * 修改记录：	第一次创建
*********************************************/
#include <string>
#include "../include/common.h"
#include "../include/elf_handler.h"

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
void global_init(const string& file_path)
{
	init_elf(file_path);		//初始化elf
//	init_dwarf(fie_path);
//	xed_init();
//	llvm_init();
//	clang_init();
}

/*===========================================
 * 函数名：	get_next_inst_offset
 * 参数：
 *	功能描述：返回下一条指令的偏移，反正就一直往下返回指令偏移，所以需要维护一个statis变量表示当前的指令偏移。遍历指令是只可执行节中的指令，也就是读完一个可执行节，再读下一个可执行节，所以还有维护一个static变量表示当前正在读的可执行节，还要维护一个可执行节列表(可执行节列表放在elf_handler中维护吧)
 *	返回值：void，只准成功
 *	抛出异常
===========================================*/
uint32_t get_next_inst_offset()
{
	if(current_execSec_index==-1)	//第一次读
		goto update_execSec;
	inst_byte_set_t inst_byte_set = get_byte_set_from_offset(current_offset);
	current_offset = current_offset+get_inst_size(inst_byte_set);
	if(!is_offset_in_function(current_offset, current_function_index))
	{
update_execSec:
		++current_execSex_index;
		current_offset = get_function_offset(current_function_index);
		inst_byte_set_t inst_byte_set = get_byte_set_from_offset(current_offset);
		maybe_next_inst_offset = current_offset+get_inst_size(inst_byte_set);
	}
	return current_offset;
}
