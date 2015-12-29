/*********************************************
 * 文件名：		llvm_handler.cpp
 * 文件描述：	LLVM库相关的接口封装
 * 创建人：		skyin, 1025年12月29日
 * 版本号：		1.0
 * 修改记录：	第一次创建
*********************************************/

#include "../include/llvm_handler.h"
#include "../include/common.h"

#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/system_error.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/OwningPtr.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

using namespace std;
using namespace llvm;

/*===========================================
 * 函数名：	get_bitcode
 * 参数：
 *			string binary_file：指定的二进制可执行文件
 *	功能描述：利用dagger将二进制文件翻译为llvm bitcode文件
 *	返回值
 *	抛出异常
===========================================*/
const string& get_bitcode(const string& binary_file)
{
	//暂时直接读入bc文件然后返回bc文件吧
	return binary_file;
}

/*===========================================
 * 函数名：	get_bitcode
 * 参数：
 *			string binary_file：llvm bc文件
 *	功能描述：解析llvm ir文件，遍历指令，找到间接分支，分析相关数据的use-def链
 *	返回值
 *	抛出异常
===========================================*/
void parse_bitcode(const std::string& bitcode_file)
{
	//先把bc文件读到内存里吧
	//创建Module
	OwningPtr<MemoryBuffer> buf;
	MemoryBuffer::getFile(Twine(bitcode_file), buf);
	if(!buf)
		errx(-1, "get file failed.");
	debug_output_with_FILE(stderr, "succeed to read bc into memory\n");
}
