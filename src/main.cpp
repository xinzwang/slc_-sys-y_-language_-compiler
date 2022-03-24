///////////////////////////////
//      SLC sysy语言编译器
// 构建方法：

#include <iostream>
#include <ostream>

#include "AsmCodeGen.hpp"
#include "Driver.hpp"
#include "IrGen.hpp"
#include "JsonGen.hpp"

using namespace std;

bool save_mid_file = true; //all mid file will be saved

bool pre = true;
bool lexer = true;
bool parser = false;
bool ir = false;
bool codegen = false;

string file_name;
string input_path;
string output_path;
string mid_path;
string no_extension_path;

void print_help( );
bool analyse_args(int argc, char *argv[]);

int main(int argc, char *argv[]) {
	if (!analyse_args(argc, argv)) {
		return 0;
	} //分析命令行参数

	//front
	Marker::Driver driver;
	driver.run(input_path);

	JsonGen json;
	json.print(driver.ast, output_path + ".json");

	IrGen irgen;
	irgen.visit(*driver.ast.root);

	Module *_module = irgen.builder._module;
	_module->module_name = "SLC code";
	_module->source_file_name = file_name;

	_module->print( );

	CodeGen codegen(_module);

	string asm_code = codegen.codegen_main( );

	cout << "-------------------------  arm code  -------------------------" << endl;
	cout << asm_code << endl;

	std::ofstream f;
	f.open(output_path);
	f << asm_code;
	f.close( );
}

void print_help( ) {
	// TODO: add help list
	return;
}

bool analyse_args(int argc, char *argv[]) {
	// print help list
	if (argc == 2 && (argv[2] == "-h"s || argv[2] == "--help"s)) {
		print_help( );
		return false;
	}

	// analyse argv
	for (int i = 1; i < argc; i++) {
		// output path
		if (argv[i] == "-o"s) {
			if (!(i + 1 < argc)) {
				printf("Please input a path.\n");
				return false;
			} else if (!output_path.empty( )) {
				printf("Get two output file.\n");
				return false;
			}
			output_path = argv[i + 1];
			i++;
		}
		// ignore
		else if (argv[i] == "-S"s) {
			continue;
		}
		// input path
		else {
			if (!input_path.empty( )) {
				printf("Get two input file.\n");
				return false;
			}
			input_path = argv[i];
		}
	}
	if (input_path.empty( )) {
		printf("No input file.\n");
		return false;
	} else if (output_path.empty( )) {
		printf("No output file.\n");
		return false;
	}

	// analyse the path
	no_extension_path = input_path;
	int point_place = no_extension_path.rfind(".");
	if (point_place == -1) {
		printf("Not a file.\n");
		return false;
	}
	no_extension_path.erase(point_place);

	// get filename
	file_name = input_path;
	int z = file_name.rfind("/");
	if (z != -1) {
		file_name.erase(z);
	}
	return true;
}
