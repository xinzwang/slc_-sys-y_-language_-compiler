#include "Driver.hpp"

#include <iostream>
#include <sstream>

using namespace Marker;
using namespace std;

//构造方法
Driver::Driver( ) : pre( ), scanner(*this), parser(scanner, *this) {}

//析构方法
Driver::~Driver( ) {}

//执行前端
int Driver::run(std::string &path) {

	string *file = pre.run(path); //预处理

	istringstream in_string_stream(*file); //转化为流

	scanner.switch_streams(&in_string_stream, 0); //指定词法分析的输入、输出流

	int res = parser.parse( ); //词法分析、语法分析均通过此函数完成

	delete file; //file用完了  释放

	return res;
}