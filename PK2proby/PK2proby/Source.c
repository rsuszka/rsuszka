#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE* odczyt;
	FILE* zapis;
	int bufor, dlugosc;
	bufor = 0;
	fopen_s(&odczyt, "abc.dat", "rb");
	if (odczyt == NULL)
		printf("Brak pliku wejsciowego\n");
	else
	{
		fopen_s(&zapis, "wynik.txt", "w");
		printf("Podaj ilosc liczb w pliku: ");
		scanf_s("%d", &dlugosc);
		for (int i = 0; i < dlugosc; i++)
		{
			fread(&bufor, sizeof(int), 1, odczyt);
			fprintf(zapis, "%d\n", bufor);
		}
		fclose(odczyt);
		fclose(zapis);
	}
	system("Pause");
	return 0;
}