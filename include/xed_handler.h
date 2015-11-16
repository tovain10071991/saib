/*********************************************
 * 文件名：		xed_handler.h
 * 文件描述：	xed相关的头文件，定义了一些与xed有关的函数
 * 创建人：		skyin, 1025年11月15日
 * 版本号：		1.0
 * 修改记录：	第一次创建
*********************************************/
#ifndef _XED_HANDLER_H_
#define _XED_HANDLER_H_

#include "../include/common.h"

extern void init_xed();
extern void get_inst_size(inst_byte_set_t inst_byte_set);

#endif
