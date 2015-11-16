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

void xed_init()
{
	xed_state_init2(&xed_state, XED_MACHINE_MODE_LONG_64, XED_ADDRESS_WIDTH_64b);
	xed_tables_init();
}
