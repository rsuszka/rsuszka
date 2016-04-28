#include<stdio.h>
#include<stdlib.h>
typedef struct HexByte_
{
	char bajt_sz[2]; // reprezntacja bajtu w postaci 16-owej (ascii)
	unsigned char bajt_b;// w postci binarnej
} HexByte;
void konw_na_16(int kod_ASCI, char* t_bajt)
{
	int i, reszta;
	for (i = 1; i >= 0; i--)
	{
		reszta = kod_ASCI % 16;
		switch (reszta)
		{
		case 1:
			t_bajt[i] = '1';
			break;
		case 2:
			t_bajt[i] = '2';
			break;
		case 3:
			t_bajt[i] = '3';
			break;
		case 4:
			t_bajt[i] = '4';
			break;
		case 5:
			t_bajt[i] = '5';
			break;
		case 6:
			t_bajt[i] = '6';
			break;
		case 7:
			t_bajt[i] = '7';
			break;
		case 8:
			t_bajt[i] = '8';
			break;
		case 9:
			t_bajt[i] = '9';
			break;
		case 10:
			t_bajt[i] = 'A';
			break;
		case 11:
			t_bajt[i] = 'B';
			break;
		case 12:
			t_bajt[i] = 'C';
			break;
		case 13:
			t_bajt[i] = 'D';
			break;
		case 14:
			t_bajt[i] = 'E';
			break;
		case 15:
			t_bajt[i] = 'F';
			break;
		}
		kod_ASCI = kod_ASCI / 16;
	}
}
void wczytaj_plik_b(HexByte* tab, char* nazwa_pliku)
{
	FILE* plik;
	int licznik = 1;
	unsigned char bufor;
	HexByte str_pom;
	fopen_s(&plik, nazwa_pliku, "rb");
	if (plik == NULL)
	{
		printf("Blad otwarica pliku\n");
		exit(-10);
	}
	tab = (HexByte*)malloc(sizeof(HexByte));
	while (!feof(plik))
	{
		tab = realloc(tab, licznik*sizeof(HexByte));
		fread(&bufor, sizeof(char), 1, plik);
		str_pom.bajt_b = bufor;
		konw_na_16(bufor, str_pom.bajt_sz);
		printf("%c %c\n", str_pom.bajt_sz[0], str_pom.bajt_sz[1]);
		tab[licznik - 1] = str_pom;
		licznik++;  //ostatni element wczytuje siê 2x !!
	}
	fclose(plik);
}
int main()
{
	HexByte* tablica = NULL;
	wczytaj_plik_b(tablica, "abc");
	system("Pause");
	return 0;
}