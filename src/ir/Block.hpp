#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <memory>
#include <vector>

#include "Instruction.hpp"
#include "Value.hpp"

/**
 * IfBlock和WhileBlock保留整个代码的高级结构特征
 * 
 * 这两个结构内部由小的Block列表组成
 * 
 * Block是具体的语句块，按照课堂介绍的Block划分法
 * 由于SYSY没有goto语句，因此只有WhileBlock包含了
 * 循环。
 * 
 * break、continue、return会在产生对Block的分割
 */

class BaseBlock;
class Block;
typedef std::shared_ptr<BaseBlock> BBPtr;
typedef std::shared_ptr<Block> BlockPtr;

class Instruction;

// BaseBlock Block 基类

class BaseBlock {
  public:
	enum BlockType {
		BLOCK,
		IFBLOCK,
		WHILEBLOCK
	};
	BlockType btype;
	std::string name;
	std::vector<BBPtr> pre;	 //前一个块	没有goto，while语句的第一个block可能由于continue、if语句的相邻下一个快可能存在多个入口
	std::vector<BBPtr> next; //下一个块	没有goto，while语句前一个块、if语句前一个块可能有多个出口
	BlockPtr next_to_build;	 //下一个构建的块
	BlockPtr *father;		 //所属高级块	唯一
	BaseBlock(BlockType _btype) : btype(_btype) {}
	// virtual void print( ) = 0;
};

// Block 指令语句块
class Block : public BaseBlock {
  public:
	std::vector<Instruction *> inst_list; //指令列表	br指令会解析到这里
	Block(BlockType _btype = BLOCK) : BaseBlock(_btype){ };
	void add_inst(Instruction *i);
	void print( );
};

// // IfBlock if语句块
// class IfBlock : public BaseBlock {
//    public:
// 	std::vector<Block *> cond;	//入口条件

// 	std::vector<Block *> if_stmt;  //if 语句
// 	std::vector<Block *> else_stmt;

//    public:
// };

// // WhileBlock while语句块
// class WhileBlock : public BaseBlock {
//    public:
// 	std::vector<Block *> cond;	//入口条件
// 	std::vector<Block *> body;	//循环体

//    public:
// 	WhileBlock( );
// };

#endif
