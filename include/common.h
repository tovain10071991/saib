/*********************************************
 * 文件名：		common.h
 * 文件描述：	公共头文件，该文件是主程序文件与具体库文件之间的衔接。为主程序文件提供了具体库文件的函数接口
 * 创建人：		skyin, 1025年11月12日
 * 版本号：		1.0
 * 修改记录：	第一次创建
*********************************************/
#ifndef _COMMON_H_
#define _COMMON_H_

#include <vector>
#include <string>
#include <stdint.h>

typedef std::vector<uint8_t> inst_byte_set_t;

extern void global_init(const std::string& file_path);
//extern uint32_t get_next_inst_offset(uint32_t offset);
//extern const inst_byte_set_t& get_inst_from_offset(uint32_t offset);
//extern bool is_indirect_branch(const inst_byte_set_t& inst_str);

#endif
