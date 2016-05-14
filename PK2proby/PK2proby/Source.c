#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
int main(int argc, char* argv[])
{
	int A[10][5];
	double B[6] = { 1,2,3,4,5,6 };
	int p;
	int *w;
	w = &(B[2]);
	p = &(B[0]);
	printf("%d %d\n", w, p);
	system("Pause");
	return 0;
}