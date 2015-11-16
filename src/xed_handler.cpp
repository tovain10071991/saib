/*********************************************
 * 文件名：		xed_handler.cpp
 * 文件描述：	xed相关的源文件，定义了一些与xed有关的函数
 * 创建人：		skyin, 1025年11月15日
 * 版本号：		1.0
 * 修改记录：	第一次创建
*********************************************/
extern "C"{
	#include <xed-interface.h>
}
#include "../include/xed_handler.h"
#include "../include/common.h"

static xed_state_t xed_state;

/*===========================================
 * 函数名：	init_xed
 * 参数：
 *	功能描述：初始化xed。
 *	返回值：void，只准成功
 *	抛出异常
===========================================*/
void init_xed()
{
	xed_state_init2(&xed_state, XED_MACHINE_MODE_LONG_64, XED_ADDRESS_WIDTH_64b);
	xed_tables_init();
}

/*===========================================
 * 函数名：	get_inst_size
 * 参数：
 *	功能描述：根据字节获取指令长度
 *	返回值：uint32_t，指令长度
 *	抛出异常
===========================================*/
uint32_t get_inst_size(inst_byte_set_t inst_byte_set)
{
	xed_decoded_inst_t decoded_inst;
	xed_decoded_inst_zero_set_mode(&decoded_inst, &xed_state);
	xed_decode(&decoded_inst, inst_byte_set.data(), INST_MAX_SIZE);
#ifdef DEBUG
	char buf[50] = "";
	xed_format_context(XED_SYNTAX_ATT, &decoded_inst, buf, 49, 0, 0, 0);
	debug_output_with_filePath("out/disas.out", "%s\n", buf);
#endif
	return xed_decoded_inst_get_length(&decoded_inst);
}
