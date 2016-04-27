#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
int main()
{
	while (1)
	{
		int znak = _getch();
		if (znak == 224)
		{
			znak = _getch();
			if (znak == 72)
			{
				printf("gora\n");
			}
			if (znak == 75)
			{
				printf("lewo\n");
			}
			if (znak == 80)
			{
				printf("dol\n");
			}
			if (znak == 77)
			{
				printf("prawo\n");
			}
		}
	}
	return 0;
}