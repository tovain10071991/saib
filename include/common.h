/*********************************************
 * 文件名：		common.h
 * 文件描述：	公共头文件，该文件是主程序文件与具体库文件之间的衔接。为主程序文件提供了具体库文件的函数接口
 * 创建人：		skyin, 1025年11月12日
 * 版本号：		1.0
 * 修改记录：	第一次创建
*********************************************/
#ifndef _COMMON_H_
#define _COMMON_H_

#include <array>
#include <string>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#ifdef DEBUG
	#include <map>
#endif

#define INST_MAX_SIZE 15	//指令字节的长度上限
typedef std::array<uint8_t, INST_MAX_SIZE> inst_byte_set_t;
typedef inst_byte_set_t byte_set_t;

extern void global_init(const std::string& file_path);
uint32_t get_next_inst_offset();
//extern uint32_t get_next_inst_offset(uint32_t offset);
//extern const inst_byte_set_t& get_inst_from_offset(uint32_t offset);
//extern bool is_indirect_branch(const inst_byte_set_t& inst_str);

#ifdef DEBUG
extern std::map<std::string, int> file_count;
#define SINGLE_FILE_MAX_SIZE 10485760	//限制单个输出文件的上限为10M=10485760B，不过结果上限似乎都是10.5M
/*===========================================
 * 宏名：	debug_output_with_FILE
 * 参数：
 *			FILE* out_stream：可以是stdin, stdout, stderr(这三个FILE指针声明在stdio.h)，也可以是其它文件流
 *			format, arg...：和printf()的参数一样
 *	功能描述：接收文件流，调试状态下格式化写
 *	返回值
 *	抛出异常
===========================================*/
	#define debug_output_with_FILE(out_stream, format, args...) \
	({ \
		fprintf(out_stream, format, ##args);	\
	})
/*===========================================
 * 宏名：	debug_output_with_FilePath
 * 参数：
 *			const string& file_name：文件路径名
 *			format, arg...：和printf()的参数一样
 *	功能描述：接收文件路径名，调试状态下格式化写
 *	返回值
 *	抛出异常
===========================================*/
	#define debug_output_with_filePath(file_path, format, args...) \
	({ \
		/*根据当前计数判断文件大小*/ \
		struct stat st;	\
		if(file_count.find(file_path)==file_count.end())	\
			file_count[file_path] = 0;	\
		string full_path(file_path+string(".")+to_string(file_count[file_path]));	\
		int fd = open(full_path.c_str(), O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);	\
		if(fd==-1)	\
			err(errno, "open file <%s> in debug_output_filePath failed", full_path.c_str());	\
		if(fstat(fd, &st))	\
			err(errno, "stat from file <%s> in debug_output_filePath failed", full_path.c_str());	\
		/*如果超过单个文件的大小上限，则计数加1，新输出文件*/ \
		if(st.st_size>SINGLE_FILE_MAX_SIZE)	\
		{	\
			debug_output_with_FILE(stderr, "complete output of the file <%s>\n", full_path.c_str());	\
			++file_count[file_path];\
			full_path.clear();	\
			full_path = file_path + string(".") + to_string(file_count[file_path]);	\
		}	\
		close(fd);	\
		FILE* fp = fopen(full_path.c_str(), "a+");	\
		if(fp==NULL)	\
			errx(-1, "fopen file <%s> in debug_output_filePath failed", full_path.c_str());	\
	fprintf(fp, format, ##args);	\
	fclose(fp);	\
	})
#else
	#define debug_output_with_FILE(out_stream, format, args...)
	#define debug_output_with_filePath(file_path, format, args...)
#endif

#endif
