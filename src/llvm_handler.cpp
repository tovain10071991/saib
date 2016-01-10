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
#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"

using namespace std;
using namespace llvm;

#ifdef DEBUG
	static string output_str;
	static raw_string_ostream output_ostream(output_str);
	#define debug_print(x) \
	({ \
		output_str.clear(); \
		x->print(output_ostream); \
		output_str; \
	})
#else
	#define debug_print(x)
#endif

static void iterate_func_inst(Module* mdl);
static void iterate_inst(Function* func);
static bool is_indirect_branch(Instruction* inst);
static bool is_indirect_call(Instruction* inst);

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
	//创建Module
	LLVMContext context;
	Module* mdl = ParseBitcodeFile(&*buf, context);
	if(!mdl)
		errx(-1, "parse bitcode file failed.");
	debug_output_with_FILE(stderr, "succeed to create Module\n");
	//迭代函数然后迭代指令
	debug_output_with_FILE(stderr, "now iterate func\n");
	iterate_func_inst(mdl);
}

/*===========================================
 * 函数名：	iterate_func_inst
 * 参数：
 *			Module* mdl
 *	功能描述：迭代指定模块的函数，然后迭代函数中的指令
 *	返回值
 *	抛出异常
===========================================*/
static void iterate_func_inst(Module* mdl)
{
	for(auto func_iter = mdl->begin(); func_iter != mdl->end(); ++func_iter)
	{
		debug_output_with_filePath("out/ins_iter.out", "\nFucntion: %s\n", func_iter->hasName()?func_iter->getName().data():"noname");
		//迭代指令
		debug_output_with_FILE(stderr, "now iterate inst in %s\n", func_iter->hasName()?func_iter->getName().data():"noname");
		iterate_inst(&*func_iter);
	}
}

/*===========================================
 * 函数名：	iterate_inst
 * 参数：
 *			Function* func
 *	功能描述：迭代指定函数中的指令，判断指令是否为间接分支，是则继续分析
 *	返回值
 *	抛出异常
===========================================*/
static void iterate_inst(Function* func)
{
	for(auto inst_iter = inst_begin(func); inst_iter != inst_end(func); ++inst_iter)
	{
		debug_output_with_filePath("out/ins_iter.out", "\n\t%s\t%s\n\t\t%s\n", inst_iter->hasName()?inst_iter->getName().data():"noname", inst_iter->getOpcodeName(), debug_print(inst_iter).c_str());
		if(is_indirect_branch(&*inst_iter))
		{
		}
	}
}

/*===========================================
 * 函数名：	is_indirect_branch
 * 参数：
 *			Instruction* inst
 *	功能描述：判断指令是否为间接分支，间接分支包括间接call/jmp/ret
 *	返回值
 *	抛出异常
===========================================*/
static bool is_indirect_branch(Instruction* inst)
{
	if(is_indirect_call(inst))
		return true;
	else
		return false;
}

static bool is_indirect_call(Instruction* inst)
{
	if(inst->getOpcode()==Instruction::Call)
	{
		if(CallInst* call_inst = dyn_cast<CallInst>(inst))
		{
			if(IntrinsicInst* intrinsic_inst = dyn_cast<IntrinsicInst>(inst))	//固有函数跳过不分析
			{
				debug_output_with_filePath("out/ins_iter.out", "\tinst_type: intrinsic_inst\n");
				return false;
			}
			else if(call_inst->getCalledFunction()!=NULL)		//只是直接调用
			{
				debug_output_with_filePath("out/ins_iter.out", "\tinst_type: direct_call\n");
				return false;
			}
			else
			{
				debug_output_with_filePath("out/ins_iter.out", "\tinst_type: indirect_call\n");
				return true;
			}
		}
		else
			errx(-1, "really?");	//这里应该不会达到
	}
	else
	{
		debug_output_with_filePath("out/ins_iter.out", "\tinst_type: not_call\n");
		return false;
	}
}
