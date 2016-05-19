/*Napisaæ grê, w której zadaniem u¿ytkownika bêdzie chodzenie po labiryncie, zbieranie przedmiotów oraz
unikanie  ruchomych  przeciwników.Jednym  z  elementów  mapy  powinno  byæ  wyjœcie, które  skieruje  u¿yt -
kownika  do  kolejnego  poziomu.Poziomy  powinny  byæ  zapisywane  w  osobnych  plikach;  program  powinien
obs³ugiwaæ mo¿liwoœæ dodawania nowych poziomów.Program musi zapamiêtywaæ oraz zapisywaæ w pliku
wszystkie wyniki uzyskane przez graczy.*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>
typedef struct Etap_
{
	int szerokosc;
	int dlugosc;
	char** etap_wsk;
} Etap;
typedef struct Gra_
{
	char nazwa_etapu[20];
	char nazwa_gracza[20];
	int liczba_punktow;
} Gra;
void komunikat(void)
{
	printf("Witaj w grze LABIRYNY!\n");
	printf("Wybierz co chcesz zrobic i zatwierdz to klawiszem Enter\n");
	printf("1. Nowa gra\n");
	printf("2. Tworzenie etapow\n");
	printf("3. Tabela wynikow\n");
	printf("4. Wyjscie\n");
}
void komunikat_koncowy(void)
{
	printf("Ukonczyles etap!\n");
}
void komunikat_koncowy2(void)
{
	printf("GAME OVER\n");
}
void wyswietl_etap_c(Etap o_etap, int czysc)
{
	int i, j;
	if (czysc == 1)
		system("cls");
	for (i = 0; i < o_etap.dlugosc; i++)
	{
		for (j = 0; j < o_etap.szerokosc; j++)
			printf("%c", o_etap.etap_wsk[i][j]);
		printf("\n");
	}
}
void wyswietl_liste_etapow(void)
{
	FILE* log_etapow;
	char nazwa_etapu[20];
	int c;
	fopen_s(&log_etapow, "log.txt", "r");
	if (log_etapow == NULL)
		printf("Brak etapow na liscie.\n");
	else
	{
		printf("Lista nazw etapow:\n");
		while ((c = fgetc(log_etapow)) != EOF)
		{
			fseek(log_etapow, -1, SEEK_CUR);
			fscanf_s(log_etapow, "%s", nazwa_etapu, 20);
			printf("%s\n", nazwa_etapu, 20);
			fseek(log_etapow, 1, SEEK_CUR);
		}
		fclose(log_etapow);
	}
}
void czysc_pamiec(Etap* o_etap)
{
	int i;
	for (i = 0; i < o_etap->dlugosc; i++) //zwolnienie pamieci
		free(o_etap->etap_wsk[i]);
	free(o_etap->etap_wsk);
}
void tworzenie_etapu(int x, int y)
{
	FILE* zapis_etapu;
	FILE* log_etapow;
	Etap tworzony_etap;
	int i,j,k,l,m,n; //liczniki petli
	int a = x;
	char** etap;
	char* bufor;
	char nazwa_etapu[20];
	int c;
	int rozmiar_bufora;
	rozmiar_bufora = (x + ceil((x * 0.2))); //bufor + 20%zapasu
	etap = (char**)malloc(y*sizeof(char*));
	bufor = (char*)calloc(rozmiar_bufora, sizeof(char));
	for (i = 0; i < y; i++)
	{
		etap[i] = (char*)malloc(x*sizeof(char));
	}
	for (k = 0; k < y; k++)
	{
		scanf_s("%s", bufor, rozmiar_bufora);
		for (l = 0; l < x; l++)
		{
			etap[k][l] = bufor[l];
		}
	}
	free(bufor);
	wyswietl_liste_etapow();
	printf("Podaj nazwe etapu (Nie dluzsza niz 20 znakow): ");
	scanf_s("%s", nazwa_etapu, 20);
	fopen_s(&zapis_etapu, nazwa_etapu, "w");
	if (zapis_etapu == NULL)
	{
		perror("blad otwarcia pliku z etapem");
		exit(-10);
	}
	fprintf(zapis_etapu, "%d ", x);
	fprintf(zapis_etapu, "%d ", y);
	for (m = 0; m < y; m++)
	{
		for (n = 0; n < x; n++)
		{
			fprintf(zapis_etapu, "%c", etap[m][n]);
		}
	}
	fclose(zapis_etapu);
	fopen_s(&log_etapow, "log.txt", "a");
	if (log_etapow == NULL)
	{
		perror("blad otwarcia pliku z logiem etapow");
		exit(-10);
	}
	fprintf(log_etapow, "%s", nazwa_etapu, 20);
	fprintf(log_etapow, " ");
	fclose(log_etapow);
	printf("Zapisano nastepujacy etap:\n");
	tworzony_etap.dlugosc = y;
	tworzony_etap.szerokosc = x;
	tworzony_etap.etap_wsk = etap;
	wyswietl_etap_c(tworzony_etap, 0);
	czysc_pamiec(&tworzony_etap);
}
char** wczytaj_etap(char* nazwa_etapu, Etap* o_etap)
{
	FILE* etap;
	int szerokosc, dlugosc;
	char** etap_tab;
	char bufor_znakowy;
	int i,j,k;
	fopen_s(&etap, nazwa_etapu, "r");
	if (etap == NULL)
	{
		perror("Blad otwarcia pliku z etapem.");
		exit(-10);
	}
	fscanf_s(etap, "%d", &szerokosc);
	fseek(etap, 1, SEEK_CUR);
	fscanf_s(etap, "%d", &dlugosc);
	fseek(etap, 1, SEEK_CUR);
	etap_tab = (char**)malloc(dlugosc*sizeof(char*));
	for (i = 0; i < dlugosc; i++)
	{
		etap_tab[i] = (char*)malloc(szerokosc*sizeof(char));
	}
	for (j = 0; j < dlugosc; j++)
	{
		for (k = 0; k < szerokosc; k++)
			fscanf_s(etap, "%c", &etap_tab[j][k]);
	}
	fclose(etap);
	o_etap->dlugosc = dlugosc;
	o_etap->szerokosc = szerokosc;
	o_etap->etap_wsk = etap_tab;
	return etap_tab;
}
int znajdz_a_K(Etap o_etap)
{
	int i, j;
	for (i = 0; i < o_etap.dlugosc; i++)
	{
		for (j = 0; j < o_etap.szerokosc; j++)
		{
			if (o_etap.etap_wsk[i][j] == 'a')
				return j;
		}
	}
}
int znajdz_a_W(Etap o_etap)
{
	int i, j;
	for (i = 0; i < o_etap.dlugosc; i++)
	{
		for (j = 0; j < o_etap.szerokosc; j++)
		{
			if (o_etap.etap_wsk[i][j] == 'a')
				return i;
		}
	}
}
void ruch_w_gore(Etap* o_etap, int* obecne_polozenie_W, int* obecne_polozenie_K)
{
	o_etap->etap_wsk[*(obecne_polozenie_W) - 1][*obecne_polozenie_K] = o_etap->etap_wsk[*obecne_polozenie_W][*obecne_polozenie_K];
	o_etap->etap_wsk[*obecne_polozenie_W][*obecne_polozenie_K] = ' ';
	*(obecne_polozenie_W) = *(obecne_polozenie_W)-1;
}
void ruch_w_dol(Etap* o_etap, int* obecne_polozenie_W, int* obecne_polozenie_K)
{
	o_etap->etap_wsk[*(obecne_polozenie_W) + 1][*obecne_polozenie_K] = o_etap->etap_wsk[*obecne_polozenie_W][*obecne_polozenie_K];
	o_etap->etap_wsk[*obecne_polozenie_W][*obecne_polozenie_K] = ' ';
	*(obecne_polozenie_W) = *(obecne_polozenie_W)+1;
}
void ruch_w_lewo(Etap* o_etap, int* obecne_polozenie_W, int* obecne_polozenie_K)
{
	o_etap->etap_wsk[*obecne_polozenie_W][*(obecne_polozenie_K) - 1] = o_etap->etap_wsk[*obecne_polozenie_W][*obecne_polozenie_K];
	o_etap->etap_wsk[*obecne_polozenie_W][*obecne_polozenie_K] = ' ';
	*(obecne_polozenie_K) = *(obecne_polozenie_K)-1;
}
void ruch_w_prawo(Etap* o_etap, int* obecne_polozenie_W, int* obecne_polozenie_K)
{
	o_etap->etap_wsk[*obecne_polozenie_W][*(obecne_polozenie_K) + 1] = o_etap->etap_wsk[*obecne_polozenie_W][*obecne_polozenie_K];
	o_etap->etap_wsk[*obecne_polozenie_W][*obecne_polozenie_K] = ' ';
	*(obecne_polozenie_K) = *(obecne_polozenie_K)+1;
}
void sterowanie(Etap* o_etap, Gra* n_gra)
{
	int znak, obecne_polozenie_K, obecne_polozenie_W;
	int wyjscie;
	obecne_polozenie_W = znajdz_a_W(*o_etap);
	obecne_polozenie_K = znajdz_a_K(*o_etap);
	wyjscie = 0;
	n_gra->liczba_punktow = 0;
	wyswietl_etap_c(*o_etap, 1);
	printf("Wynik: %d\n", n_gra->liczba_punktow);
	while ((wyjscie == 0))
	{
		znak = _getch();
		if (znak == 224)
		{
			znak = _getch();
			switch (znak)
			{
			case 72:
				if ((obecne_polozenie_W - 1 >= 0) && (o_etap->etap_wsk[obecne_polozenie_W - 1][obecne_polozenie_K] != '|'))
				{
					if (o_etap->etap_wsk[obecne_polozenie_W - 1][obecne_polozenie_K] == 'x')
					{
						o_etap->etap_wsk[obecne_polozenie_W][obecne_polozenie_K] = ' ';
						n_gra->liczba_punktow = 0;
						wyjscie = -1;
					}
					else
					{
						wyjscie = meta(*o_etap, znak, obecne_polozenie_W, obecne_polozenie_K);
						n_gra->liczba_punktow = n_gra->liczba_punktow + punkty(*o_etap, znak, obecne_polozenie_W, obecne_polozenie_K);
						ruch_w_gore(o_etap, &obecne_polozenie_W, &obecne_polozenie_K);
					}
				}
				break;
			case 75:
				if ((obecne_polozenie_K - 1 >= 0) && (o_etap->etap_wsk[obecne_polozenie_W][obecne_polozenie_K - 1] != '|'))
				{
					if (o_etap->etap_wsk[obecne_polozenie_W][obecne_polozenie_K - 1] == 'x')
					{
						o_etap->etap_wsk[obecne_polozenie_W][obecne_polozenie_K] = ' ';
						n_gra->liczba_punktow = 0;
						wyjscie = -1;
					}
					else
					{
						wyjscie = meta(*o_etap, znak, obecne_polozenie_W, obecne_polozenie_K);
						n_gra->liczba_punktow = n_gra->liczba_punktow + punkty(*o_etap, znak, obecne_polozenie_W, obecne_polozenie_K);
						ruch_w_lewo(o_etap, &obecne_polozenie_W, &obecne_polozenie_K);
					}
				}
				break;
			case 80:
				if ((obecne_polozenie_W + 1 < o_etap->dlugosc) && (o_etap->etap_wsk[obecne_polozenie_W + 1][obecne_polozenie_K] != '|'))
				{
					if (o_etap->etap_wsk[obecne_polozenie_W + 1][obecne_polozenie_K] == 'x')
					{
						o_etap->etap_wsk[obecne_polozenie_W][obecne_polozenie_K] = ' ';
						n_gra->liczba_punktow = 0;
						wyjscie = -1;
					}
					else
					{
						wyjscie = meta(*o_etap, znak, obecne_polozenie_W, obecne_polozenie_K);
						n_gra->liczba_punktow = n_gra->liczba_punktow + punkty(*o_etap, znak, obecne_polozenie_W, obecne_polozenie_K);
						ruch_w_dol(o_etap, &obecne_polozenie_W, &obecne_polozenie_K);
					}
				}
				break;
			case 77:
				if ((obecne_polozenie_K + 1 < o_etap->szerokosc) && (o_etap->etap_wsk[obecne_polozenie_W][obecne_polozenie_K + 1] != '|'))
				{
					if (o_etap->etap_wsk[obecne_polozenie_W][obecne_polozenie_K + 1] == 'x')
					{
						o_etap->etap_wsk[obecne_polozenie_W][obecne_polozenie_K] = ' ';
						n_gra->liczba_punktow = 0;
						wyjscie = -1;
					}
					else
					{
						wyjscie = meta(*o_etap, znak, obecne_polozenie_W, obecne_polozenie_K);
						n_gra->liczba_punktow = n_gra->liczba_punktow + punkty(*o_etap, znak, obecne_polozenie_W, obecne_polozenie_K);
						ruch_w_prawo(o_etap, &obecne_polozenie_W, &obecne_polozenie_K);
					}
				}
				break;
			}
			if (wyjscie == 0)
				wyjscie = ruch_przeciwnikow(o_etap, n_gra);
			wyswietl_etap_c(*o_etap, 1);
			printf("Wynik: %d\n", n_gra->liczba_punktow);
		}
	}
	if (wyjscie == 1) //ukoñczenie gry
		komunikat_koncowy();
	if (wyjscie == -1) //pora¿ka
		komunikat_koncowy2();
}
int meta(Etap o_etap, int znak, int wiersz, int kolumna)
{
	int wynik = 0;
	switch (znak)
	{
	case 72:
		if (o_etap.etap_wsk[wiersz - 1][kolumna] == 'M')
			wynik = 1;
		break;
	case 75:
		if (o_etap.etap_wsk[wiersz][kolumna - 1] == 'M')
			wynik = 1;
		break;
	case 80:
		if (o_etap.etap_wsk[wiersz + 1][kolumna] == 'M')
			wynik = 1;
		break;
	case 77:
		if (o_etap.etap_wsk[wiersz][kolumna + 1] == 'M')
			wynik = 1;
		break;
	}
	return wynik;
}
int punkty(Etap o_etap, int znak, int wiersz, int kolumna)
{
	int points = 0;
	switch (znak)
	{
	case 72:
		if (o_etap.etap_wsk[wiersz - 1][kolumna] == '*')
			points = points + 5;
		if (o_etap.etap_wsk[wiersz - 1][kolumna] == '.')
			points++;
		break;
	case 75:
		if (o_etap.etap_wsk[wiersz][kolumna - 1] == '*')
			points = points + 5;
		if (o_etap.etap_wsk[wiersz][kolumna - 1] == '.')
			points++;
		break;
	case 80:
		if (o_etap.etap_wsk[wiersz + 1][kolumna] == '*')
			points = points + 5;
		if (o_etap.etap_wsk[wiersz + 1][kolumna] == '.')
			points++;
		break;
	case 77:
		if (o_etap.etap_wsk[wiersz][kolumna + 1] == '*')
			points = points + 5;
		if (o_etap.etap_wsk[wiersz][kolumna + 1] == '.')
			points++;
		break;
	}
	return points;
}
int ruch_przeciwnikow(Etap* o_etap, Gra* n_gra)
{
	int i, j, itmp, jtmp, p_blok_W, p_blok_K;
	int ziarno = 55;
	ziarno = rand() % 4;
	p_blok_K = o_etap->szerokosc + 1;
	p_blok_W = o_etap->dlugosc + 1;
	for (i = 0; i < o_etap->dlugosc; i++)
	{
		for (j = 0; j < o_etap->szerokosc; j++)
		{
			if (o_etap->etap_wsk[i][j] == 'x')
			{
				itmp = i;
				jtmp = j;
				switch (ziarno)
				{
				case 0:
					if ((i - 1 >= 0) && (o_etap->etap_wsk[i - 1][j] != '|') && (o_etap->etap_wsk[i - 1][j] != '*')  && (o_etap->etap_wsk[i - 1][j] != 'x'))
					{
						if (o_etap->etap_wsk[i - 1][j] == 'a')
						{
							ruch_w_gore(o_etap, &itmp, &jtmp);
							o_etap->etap_wsk[i][j] = '.';
							n_gra->liczba_punktow = 0;
							return -1;
						}
						ruch_w_gore(o_etap, &itmp, &jtmp);
						o_etap->etap_wsk[i][j] = '.';
					}
					break;
				case 1:
					if ((j - 1 >= 0) && (o_etap->etap_wsk[i][j - 1] != '|') && (o_etap->etap_wsk[i][j - 1] != '*') && (o_etap->etap_wsk[i][j - 1] != 'x'))
					{
						if (o_etap->etap_wsk[i][j - 1] == 'a')
						{
							ruch_w_lewo(o_etap, &itmp, &jtmp);
							o_etap->etap_wsk[i][j] = '.';
							n_gra->liczba_punktow = 0;
							return -1;
						}
						ruch_w_lewo(o_etap, &itmp, &jtmp);
						o_etap->etap_wsk[i][j] = '.';
					}
					break;
				case 2:
					if ((i + 1 <= o_etap->dlugosc) && (p_blok_W != i) && (o_etap->etap_wsk[i + 1][j] != '|') && (o_etap->etap_wsk[i + 1][j] != '*') && (o_etap->etap_wsk[i + 1][j] != 'x'))
					{
						if (o_etap->etap_wsk[i + 1][j] == 'a')
						{
							ruch_w_dol(o_etap, &itmp, &jtmp);
							o_etap->etap_wsk[i][j] = '.';
							n_gra->liczba_punktow = 0;
							return -1;
						}
						ruch_w_dol(o_etap, &itmp, &jtmp);
						o_etap->etap_wsk[i][j] = '.';
						p_blok_W = i + 1;
					}
					break;
				case 3:
					if ((j + 1 <= o_etap->szerokosc) && (p_blok_K != j) && (o_etap->etap_wsk[i][j + 1] != '|') && (o_etap->etap_wsk[i][j + 1] != '*') && (o_etap->etap_wsk[i][j + 1] != 'x'))
					{
						if (o_etap->etap_wsk[i][j + 1] == 'a')
						{
							ruch_w_prawo(o_etap, &itmp, &jtmp);
							o_etap->etap_wsk[i][j] = '.';
							n_gra->liczba_punktow = 0;
							return -1;
						}
						ruch_w_prawo(o_etap, &itmp, &jtmp);
						o_etap->etap_wsk[i][j] = '.';
						p_blok_K = j + 1;
					}
					break;
				}
			}
		}
	}
	return 0;
}
void zapisz_wyniki(Gra n_gra)
{
	FILE* plik;
	fopen_s(&plik, "wyniki.txt", "a");
	if (plik == NULL)
	{
		perror("Blad otwarcia pliku do zapisu wynikow.\n");
		exit(-10);
	}
	fprintf(plik, "%s ", n_gra.nazwa_etapu, 20);
	fprintf(plik, "%s ", n_gra.nazwa_gracza, 20);
	fprintf(plik, "%d\n", n_gra.liczba_punktow);
	fclose(plik);
}
void wyswietl_wyniki(void)
{
	FILE* plik;
	int c;
	Gra bufor;
	fopen_s(&plik, "wyniki.txt", "r");
	if (plik == NULL)
	{
		perror("Blad otwarcia pliku z wynikami");
		exit(-10);
	}
	printf("Nazwa etapu/Nazwa gracza/ilosc punktow\n");
	while ((c = fgetc(plik)) != EOF)
	{
		fseek(plik, -1, SEEK_CUR);
		fscanf_s(plik, "%s", bufor.nazwa_etapu, 20);
		fscanf_s(plik, "%s", bufor.nazwa_gracza, 20);
		fscanf_s(plik, "%d", &bufor.liczba_punktow);
		printf("%s/", bufor.nazwa_etapu, 20);
		printf("%s/", bufor.nazwa_gracza, 20);
		printf("%d\n", bufor.liczba_punktow);
		fseek(plik, 2, SEEK_CUR);
	}
	fclose(plik);
	
}
int main()
{
	srand(time(NULL));
	int wybor, w_x, w_y, dlugosc_etapu, szerokosc_etapu;
	char nazwa_etapu[20];
	char** etap_wsk;
	Etap Obecny_etap;
	Gra Nowa_gra;
	while (1)
	{
		komunikat();
		scanf_s("%d", &wybor);
		switch (wybor)
		{
		case 1:
			printf("Wybrales nowa gre.\n");
			printf("Podaj swoje imie.\n");
			scanf_s("%s", Nowa_gra.nazwa_gracza, 20);
			printf("---------------\n");
			wyswietl_liste_etapow();
			printf("Wybierz etap z powyzszej listy.\n");
			scanf_s("%s", &Nowa_gra.nazwa_etapu, 20);
			etap_wsk = wczytaj_etap(Nowa_gra.nazwa_etapu, &Obecny_etap);
			sterowanie(&Obecny_etap, &Nowa_gra);
			zapisz_wyniki(Nowa_gra);
			czysc_pamiec(&Obecny_etap);
			printf("\n");
			break;
		case 2:
			printf("Wybrales tworzenie etapow\n");
			printf("Podaj szerokosc mapy.\n");
			scanf_s("%d", &w_x);
			printf("Podaj dlugosc mapy.\n");
			scanf_s("%d", &w_y);
			tworzenie_etapu(w_x, w_y);
			printf("\n");
			break;
		case 3:
			printf("Wybrales tabele wynikow\n");
			wyswietl_wyniki();
			printf("\n");
			break;
		case 4:
			exit(0);
		default:
			printf("Wybrales bledna opcje. Sprobuj ponownie\n\n");
			break;
		}
	}
	system("Pause");
	return 0;
}