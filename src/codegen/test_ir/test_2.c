// clang test1.c - S - emit - llvm

int a;
int b=0;
int c[5]={1,2,3,4,5};
int d[2][3] = {{1,3,5},{2,4,6}};

const int ca=0;
const int cb=ca;
const int cc[5]={ca*2,ca+cb,3,4,5};
const int cd[2][3] = {{1,3,5},{2,4,6}};

int main(){
	int a;
	int ma;
	int mb=0;
	int mc[3] = {3,6,9};
	int md[2][4][6];

	const int cma=4;

	ma=b;
	mc[2]=ma;
	md[1][3][4]=mc[2];	

	int me[2][3]={{33,26,21},{90,45,13}};

	print(me[0][0]);
}
