/*********************************************
 * 文件名：		elf_handler.h
 * 文件描述：	elf头文件，声明了一些与libelf有关的函数
 * 创建人：		skyin, 1025年11月13日
 * 版本号：		1.0
 * 修改记录：	第一次创建
*********************************************/
#ifndef _ELF_HANDLER_H_
#define _ELF_HANDLER_H_

#include <string>

void init_elf(const std::string& file_path);		//初始化elf
//uint32_t get_next_inst_offset(uint32_t offset);

#endif
