#include "Const.hpp"

int ConstArray::get_byte_size( ) {
	int res = 1;
	for (int32_t t : dim) {
		res *= t;
	}
	return res * 4; //这里确定数组的字节大小
}