int a = 1;
const int b = 2;

int fun(int p, int q) {
	int c;
	return p + q;
}

int main( ) {
	int c;
	a = a + b;

	c = fun(a, b);
}