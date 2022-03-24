#ifndef SCOPE_HPP
#define SCOPE_HPP

#include <map>
#include <stack>
#include <string>
#include <vector>

#include "Value.hpp"

class Scope { //定义scope类

  private:
	std::vector<std::map<std::string, ValuePtr>> layers; //定义一层的（一个Block）内的变量容器。
														 // std::vector<std::map<std::string, std::vector<Value *>>> layers_param; //定义一层容器

  public:
	void enter( ) //进入一个Scope,对两个数组初始话，给这个block准备两个环境
	{
		layers.push_back({ });
		// layers_param.push_back({});
	}

	void leave( ) //退出一个Scope，将给他们准备的环境弹出
	{
		layers.pop_back( );
		// layers_param.pop_back();
	}

	int is_global( ) //返回当前在局部函数还是全局变量域信息，返回1为全局变量域，0为局部变量域
	{
		if (layers.size( ) == 1)
			return 1;
		return 0;
	}

	bool insert_item(ValuePtr val) //在本层插入一个变量item，返回插入成功与否信息
	{
		auto Insert_res = layers[layers.size( ) - 1].insert({val->name, val});
		return Insert_res.second;
	}

	ValuePtr find_item(std::string name) {
		for (auto i = layers.rbegin( ); i != layers.rend( ); i++) {
			auto iter = i->find(name);
			if (iter != i->end( )) {
				return iter->second;
			}
		}
		return nullptr;
	}

	// bool insert_param(std::string name, ValuePtr val, std::vector<ValuePtr> params)
	// {
	//     auto Insert_res = layers_param[layers_param.size() - 1].insert({name, params});
	//     return Insert_res.second;
	// }

	// Value *find_para(std::string name, std::vector<ValuePtr> &params)
	// {
	//     for (auto i = layers_param.rbegin(); i != layers_param.rend(); i++)
	//     {
	//         auto iter = i->find(name);
	//         if (iter != i->end())
	//         {
	//             params.assign(iter->second.begin(), iter->second.end());
	//             return iter->second[0];
	//         }
	//     }
	//     return nullptr;
	// }
};

#endif
