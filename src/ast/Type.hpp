#ifndef TYPE_H
#define TYPE_H
//数据类型
enum Type { TYPE_INT,
			TYPE_VOID };

//单目运算符
enum Unary_OP {
	OP_POS, // +
	OP_NEG, // -
	OP_NOT	// !
};
//双目运算符
enum Binary_OP {
	OP_GT,	// >
	OP_LT,	// <
	OP_GTE, // >=
	OP_LTE, // <=
	OP_EQ,	// ==
	OP_NEQ, // !=
	OP_ADD, // +
	OP_SUB, // -
	OP_MUL, // *
	OP_DIV, // /
	OP_MOD, // %
	OP_AND, // &&
	OP_OR	// ||
};

// //加式算符
// enum Add_OP {
// 	OP_ADD, // +
// 	OP_SUB	// -
// };

// //乘式运算符
// enum Mul_OP {
// 	OP_MUL, // *
// 	OP_DIV, // /
// 	OP_MOD	// %
// };

// //逻辑运算符
// enum And_OP {
// 	OP_AND // &&

// };
// enum Or_op {
// 	OP_OR // ||
// };

#endif 