#include<stdio.h>
#include<stdlib.h>
void tworz(char* nazwa_pliu)
{
	char tab[5] = "abcde";
	int zmienna = 15;
	FILE* plik;
	fopen_s(&plik, nazwa_pliu, "wb");
	fwrite(tab, sizeof(char), 5, plik);
	//fwrite(&zmienna, sizeof(int), 1, plik);
	fclose(plik);
}
void czytaj(char* nazwa_pliku)
{
	char a,b;
	int zmienna;
	FILE* plik;
	fopen_s(&plik, nazwa_pliku, "rb");
	fread(&a, sizeof(char), 1, plik);
	fseek(plik, 1, SEEK_CUR);
	fread(&b, sizeof(char), 1, plik);
	fseek(plik, 2, SEEK_CUR);
	fread(&zmienna, sizeof(int), 1, plik);
	fclose(plik);
	printf("%c\n", b);
	printf("%d\n", zmienna);
}
int main()
{
	tworz("abc");
	czytaj("abc");
	system("Pause");
	return 0;
}