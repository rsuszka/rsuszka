/*aby program dzia³a³ prawid³owo wyrazy w pliku mog¹ byæ rodzielane tylko i wy³¹cznie spacjami*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Tekst_
{
	char *t; //wskaŸnik na tekst
	int r; //rozmiar tekstu w bajtach
	int lw; //liczba wyrazów w tekœcie 
} Tekst;
void czytaj(Tekst* mt, char *nazwa_pliku)
{
	FILE* plik;
	fpos_t dlugosc;
	int i = 0;
	int j;
	int licznik_wyrazow = 0;
	fopen_s(&plik, nazwa_pliku, "r");
	if (plik == NULL)
	{
		printf("Blad wczytywania pliku\n");
	}
	else
	{
		fseek(plik, 0, SEEK_END);
		fgetpos(plik, &dlugosc);
		printf("%d\n", dlugosc); //usunac
		fseek(plik, 0, SEEK_SET);
		mt->r = dlugosc;
		(mt->t) = malloc(sizeof(dlugosc));
		while (!feof(plik))
		{
			mt->t[i] = fgetc(plik);
			i++;
		}
		mt->t[i] = '\0';
		printf("%s\n", mt->t, dlugosc); //usunac
		for (j = 0; j < dlugosc; j++)
		{
			if (mt->t[j] == ' ')
				licznik_wyrazow++;
		}
		licznik_wyrazow++; //doliczenie ostatniego wyrazu
		mt->lw = licznik_wyrazow;
	}
	fclose(plik);
}
char* znajdz(Tekst *mt, char *wzorzec, int offset)
{
	char* wskaznik_na_wzorzec;
	int licznik_wzorca;
	int i;
	if (offset == 0)
	{
		wskaznik_na_wzorzec = strstr((mt->t), wzorzec);
	}
	else
	{
		licznik_wzorca=strlen(wzorzec);
		wskaznik_na_wzorzec = strstr((mt->t), wzorzec);
		for (i = 0; i < licznik_wzorca; i++)
		{
			*(wskaznik_na_wzorzec + i) = '*';
		}
		wskaznik_na_wzorzec = strstr((mt->t), wzorzec);
	}
	return wskaznik_na_wzorzec;
}
int main()
{
	Tekst* nowy_tekst = NULL;
	int offset = 0;
	char* wskaznik;
	nowy_tekst = (Tekst*)malloc(sizeof(Tekst));
	czytaj(nowy_tekst, "abc.txt");
	wskaznik=znajdz(nowy_tekst, "Rafal", offset); //znalezienie pierwszego wyst¹pienia wzorca
	printf("%d\n", wskaznik);
	while (wskaznik != NULL)
	{
		offset++;
		wskaznik = znajdz(nowy_tekst, "Rafal", offset);
		printf("%d\n", wskaznik);
	}
	czytaj(nowy_tekst, "abc.txt"); //przywrócenie "zniszczonego" tekstu
	system("Pause");
	return 0;
}