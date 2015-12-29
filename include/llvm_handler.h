/*********************************************
 * 文件名：		llvm_handler.h
 * 文件描述：	LLVM库相关的接口封装
 * 创建人：		skyin, 1025年12月29日
 * 版本号：		1.0
 * 修改记录：	第一次创建
*********************************************/
#ifndef _LLVM_HANDLER_H_
#define _LLVM_HANDLER_H_

#include <string>


extern const std::string& get_bitcode(const std::string& binary_file);
extern void parse_bitcode(const std::string& bitcode_file);

#endif
