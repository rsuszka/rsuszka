/*aby program dzia³a³ prawid³owo wyrazy w pliku mog¹ byæ rodzielane tylko i wy³¹cznie spacjami oraz musza skladac sie wylacznie z malych liter*/
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
		fgetpos(plik, &dlugosc); //znalezie dlugosci tekst
		fseek(plik, 0, SEEK_SET);
		mt->r = dlugosc;
		(mt->t) = malloc(sizeof(dlugosc));
		while (!feof(plik))
		{
			mt->t[i] = fgetc(plik); //wczytywanie bajt po bajcie
			i++;
		}
		mt->t[i] = '\0';
		for (j = 0; j < dlugosc; j++) //zliczenie wyrazow
		{
			if (mt->t[j] == ' ')
				licznik_wyrazow++;
		}
		licznik_wyrazow++; //doliczenie ostatniego wyrazu
		mt->lw = licznik_wyrazow;
		fclose(plik);
	}
}
char* znajdz(Tekst *mt, char *wzorzec, int offset)
{
	char* wskaznik_na_wzorzec;
	int licznik_wzorca;
	int i;
	if (offset == 0) //znalezie pierwszego powtorzenia
	{
		wskaznik_na_wzorzec = strstr((mt->t), wzorzec);
	}
	else //szukanie powtorze przy ponownym wywolaniu funkcji
	{
		licznik_wzorca = strlen(wzorzec);
		wskaznik_na_wzorzec = strstr((mt->t), wzorzec);
		for (i = 0; i < licznik_wzorca; i++)
		{
			*(wskaznik_na_wzorzec + i) = '*';
		}
		wskaznik_na_wzorzec = strstr((mt->t), wzorzec);
	}
	return wskaznik_na_wzorzec;
}
int porownanie(const void *a, const void *b)
{
	int wynik;
	const char **ia = (const char **)a;
	const char **ib = (const char **)b;
	wynik = strcmp(*ia, *ib);
	return wynik;
}
int dlugosc_slowa(char* tekst_wsk)
{
	int dlugosc = 0;
	while (((*tekst_wsk) != ' ') && ((*tekst_wsk != '\0')))
	{
		dlugosc++;
		tekst_wsk = tekst_wsk + 1;
	}
	return dlugosc;
}
Tekst* sortuj(Tekst *mt)
{
	int i, j, k, l; //liczniki pêtli
	int licznik = 0;
	int dl_slowa;
	char **bufor;
	char *sl_wsk;
	char* sl_wska2;
	sl_wsk = (mt->t);
	bufor = (char**)malloc((mt->lw) * sizeof(char*));
	for (i = 0; i < (mt->lw); i++) //przepisanie ciagu znakow do tablicy
	{
		dl_slowa = dlugosc_slowa(sl_wsk);
		bufor[i] = (char*)malloc(dl_slowa + 1);
		memcpy(bufor[i], sl_wsk, dl_slowa);
		bufor[i][dl_slowa] = '\0';
		sl_wsk = sl_wsk + dl_slowa + 1;
	}
	qsort(bufor, (mt->lw), sizeof(char*), porownanie); //sortowanie
	for (j = 0; j < (mt->lw); j++) //przepisanie posortowanej tablicy na ciag znakow
	{
		sl_wska2 = bufor[j];
		dl_slowa = dlugosc_slowa(sl_wska2);
		for (k = 0; k < dl_slowa; k++)
		{
			mt->t[licznik] = bufor[j][k];
			licznik++;
		}
		mt->t[licznik] = ' ';
		licznik++;
	}
	mt->t[licznik] = '\0';
	for (l = 0; l < mt->lw; l++) //zwolnienie pamiêci z tablicy tymczasowej
	{
		free(bufor[l]);
	}
	free(bufor);
}
int main()
{
	Tekst* nowy_tekst = NULL;
	int offset = 0;
	char* wskaznik;
	nowy_tekst = (Tekst*)malloc(sizeof(Tekst));
	czytaj(nowy_tekst, "abc.txt");
	wskaznik = znajdz(nowy_tekst, "english", offset); //znalezienie pierwszego wyst¹pienia wzorca
	while (wskaznik != NULL)
	{
		offset++;
		wskaznik = znajdz(nowy_tekst, "english", offset);
	}
	if (offset != 0)
	{
		czytaj(nowy_tekst, "abc.txt"); //przywrócenie "zniszczonego" tekstu
	}
	sortuj(nowy_tekst);
	free(nowy_tekst); //czyszczenie pamieci
	system("Pause");
	return 0;
}