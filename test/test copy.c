int a;
int b, c = 0;
int d[5][4][3] = {1, 2, 3, 4, 5};
const int ca = 1;
const int cb[2] = {ca, 2};
const int cc[4][4] = {{ca, 2}, {cb[0], cb[1], 3}, ca, 4};
const int cd[3] = {cb[1], cc[2][2]};
int e[4][4] = {{ca, 2}, {cb[0], cb[1], 3}, ca, 4};

void fun(int a, int b) {
	int fc = 1;
	int f;
	fun(a - 1, b - 1);
	return 0;
}

int fun1(int a, int b) {
	int fc = 1;
	while (fc < b) {
		fc = fc + 1;
	}
	return a + b + fc;
}

void fun2(int p[][2], int q[2][3][4]) {
	a[4] = 2;
	return;
}

int main( ) {
	const int ma = 1;
	int b = 2;
	int c = cb[1];
	if (ma > b) {
		ma = b + c;
		b = fun1(ma, c);
		return 0;
	} else {
		fun(b, c);
		return 1;
	}
}