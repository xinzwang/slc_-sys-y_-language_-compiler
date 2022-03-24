#include "pre.hpp"

Pre::Pre( ) {
}

std::string *Pre::run(std::string path) {
	//返回对象
	std::string *res = new std::string( );

	//打开文件
	std::fstream file;
	file.open(path);

	//预处理操作
	int comment_t2_flag = 0;
	std::string line_content = "";
	while (getline(file, line_content)) {
		if (comment_t2_flag == 1) {
			if (line_content.find("*/") == std::string::npos) //形如 /*...换行....*/ 的格式中对于中间行的处理
			{
				*res += "\n";
				continue;
			} else //形如 /*....换行....*/ 的格式中对于最后一行的处理
			{
				*res += line_content.substr(line_content.find("*/") + 2, line_content.length( ) - line_content.find("*/"));
				*res += "\n";
				comment_t2_flag = 0;
				continue;
			}
		} else {
			if (line_content.find("/*") != std::string::npos) {
				if (line_content.find("*/") != std::string::npos) //形如 /*....同一行....*/ 的格式
				{
					*res += "\n";
					continue;
				} else //形如 /*...换行...*/ 的格式的/*部分的处理
				{
					comment_t2_flag = 1;
					*res += line_content.substr(0, line_content.find("/*"));
					*res += "\n";
					continue;
				}
			}
		}
		if (line_content.find("//") != std::string::npos) //形如 //...... 的格式的处理
		{
			*res += line_content.substr(0, line_content.find("//"));
			*res += "\n";
		} else //没有注释的行的处理
		{
			*res += line_content;
			*res += "\n";
		}
	}

	file.close( );
	return res;
}