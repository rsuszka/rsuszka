/*Napisa� gr�, w kt�rej zadaniem u�ytkownika b�dzie chodzenie po labiryncie, zbieranie przedmiot�w oraz
unikanie  ruchomych  przeciwnik�w.Jednym  z  element�w  mapy  powinno  by�  wyj�cie, kt�re  skieruje  u�yt -
kownika  do  kolejnego  poziomu.Poziomy  powinny  by�  zapisywane  w  osobnych  plikach;  program  powinien
obs�ugiwa� mo�liwo�� dodawania nowych poziom�w.Program musi zapami�tywa� oraz zapisywa� w pliku
wszystkie wyniki uzyskane przez graczy.*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
typedef struct Etap_ //struktura przechowuj�ca etap w pami�ci
{
	int szerokosc;
	int dlugosc;
	char** etap_wsk;
} Etap;
typedef struct Gra_ //struktura przechowuj�ca informacje o obecnej grze w pami�ci
{
	char nazwa_etapu[20];
	char nazwa_gracza[20];
	int liczba_punktow;
} Gra;
void instrukcja_do_gry(void) //instrukcja obs�ugi gry
{
	printf("Celem gry jest dotarcie postacia ('a') do mety ('M')\n");
	printf("Po drodze nalezy zbierac przedmioty: \n");
	printf("- ('.') - 1 punkt\n");
	printf("- ('*') - 5 punktow\n");
	printf("oraz unikac przeciwnikow ('x') - po starciu z nim postac ('a') umiera.\n");
	printf("Postacia steruje sie za pomoca 'strzalek' na klawiaturze.\n");
	printf("Meta przekierowuje do kolejnego etapu.\n");
	printf("Podane przez uzytkownika imie nie moze przekraczac 20 znakow.\n");
}
void instrukcja_tworzenia_etapu(void) //intrukcja tworzenia etapow
{
	printf("Na poczatku tworzenia etapu nalezy podac jego wymiary.\n");
	printf("Nastepnie nalezy podac ciagi znakow odpowiadajace tworzonemu etapowi oraz zatwierdzac je klawiszem 'enter'.\n");
	printf("Mozna uzywac nastpujacych symboli: \n");
	printf("- ('|') - ograniczenia etapu (bariery) w pionie i poziomie\n");
	printf("- ('a') - postac, symbolu mozna uzyc tylko raz!\n");
	printf("- ('x') - przeciwnicy\n");
	printf("- ('.') - przedmiot za 1 punkt\n");
	printf("- ('*') - przedmiot na 5 punktow\n");
	printf("- ('M') - meta, symblolu mozna uzyc tylko raz!\n");
	printf("Na samym koncu nalezy wybrac nazwe etapu (musi konczyc sie na '.txt'). Maksymalna dlugosc nazwy to 20 znakow\n");
}
void komunikat(void) //komunikat dotyczacy interfejsu programu
{
	printf("Witaj w grze LABIRYNY!\n");
	printf("Wybierz co chcesz zrobic i zatwierdz to klawiszem Enter\n");
	printf("1. Nowa gra\n");
	printf("2. Tworzenie etapow\n");
	printf("3. Tabela wynikow\n");
	printf("4. Wyjscie\n");
}
void komunikat_koncowy(void) //komunikat ko�ca gry w przypadku wygranej
{
	printf("Ukonczyles etap!\n");
}
void komunikat_koncowy2(void) //komunikat ko�ca gry w przypadku pora�ki
{
	printf("GAME OVER\n");
}
void wyswietl_etap_c(Etap o_etap, int czysc) //funkcja wy�wietlaj�ca pojedy�czy etap (tablic� dwuwymiarow�)
{
	int i, j; //liczniki p�tli
	if (czysc == 1) //parametr wskazujacy czy nale�y czy�ci� ekran
		system("cls");
	for (i = 0; i < o_etap.dlugosc; i++)
	{
		for (j = 0; j < o_etap.szerokosc; j++)
			printf("%c", o_etap.etap_wsk[i][j]); //wy�wietlanie poszczeg�lnych element�w
		printf("\n");
	}
}
void wyswietl_liste_etapow(void) //funckja wy�wietlaj�ca list� etap�w znajduj�c� si� w pliku (je�eli plik nie istnieje zostaje utworzony)
{
	FILE* log_etapow;
	char nazwa_etapu[20]; //tablica przechowujaca tymczasowo nazw� etapu
	int c;
	fopen_s(&log_etapow, "log.txt", "r");
	if (log_etapow == NULL)
		printf("Brak etapow na liscie.\n");
	else
	{
		printf("Lista nazw etapow:\n");
		while ((c = fgetc(log_etapow)) != EOF) //przeszukiwanie pliku a� do znaku ko�ca pliku
		{
			fseek(log_etapow, -1, SEEK_CUR);
			fscanf_s(log_etapow, "%s", nazwa_etapu, 20); //wczytanie elementu do tablicy
			printf("%s\n", nazwa_etapu, 20); //wy�wietlenie elementu
			fseek(log_etapow, 1, SEEK_CUR);
		}
		fclose(log_etapow);
	}
}
void czysc_pamiec(Etap* o_etap) //funkcja usuwaj�ca etap z pami�ci
{
	int i;
	for (i = 0; i < o_etap->dlugosc; i++) //zwolnienie pamieci
		free(o_etap->etap_wsk[i]);
	free(o_etap->etap_wsk);
}
void tworzenie_etapu(int x, int y) //funkcja tworz�ca etap o podanych wymiarach
{
	FILE* zapis_etapu;
	FILE* log_etapow;
	Etap tworzony_etap;
	int i,j,k,l,m,n; //liczniki petli
	char** etap;
	char* bufor;
	char nazwa_etapu[20];
	int rozmiar_bufora; //bufor wczytuj�cy dane
	rozmiar_bufora = (x + ceil((x * 0.2))); //bufor + 20%zapasu
	etap = (char**)malloc(y*sizeof(char*));
	bufor = (char*)calloc(rozmiar_bufora, sizeof(char)); //alokacja pami�ci dla bufora
	for (i = 0; i < y; i++)
	{
		etap[i] = (char*)malloc(x*sizeof(char)); //alokacja pami�ci dla ka�dej kolumny tablicy
	}
	for (k = 0; k < y; k++) //zczytywanie wierszy a� do ograniczone rozmiarem
	{
		scanf_s("%s", bufor, rozmiar_bufora);
		for (l = 0; l < x; l++)
		{
			etap[k][l] = bufor[l]; //kopiowanie danych z bufora do tablicy (etapu)
		}
	}
	free(bufor);
	wyswietl_liste_etapow();
	printf("Podaj nazwe etapu (Nie dluzsza niz 20 znakow): ");
	scanf_s("%s", nazwa_etapu, 20);
	fopen_s(&zapis_etapu, nazwa_etapu, "w");
	if (zapis_etapu == NULL) //sprawdzenie poprawno�ci otwarcia pliku do zapisu etapu
	{
		perror("blad otwarcia pliku z etapem");
		exit(-10);
	}
	fprintf(zapis_etapu, "%d ", x); //zapis wymiar�w
	fprintf(zapis_etapu, "%d ", y);
	for (m = 0; m < y; m++)
	{
		for (n = 0; n < x; n++)
		{
			fprintf(zapis_etapu, "%c", etap[m][n]); //zapis tablicy dwuwymiarowej znak po znaku
		}
	}
	fclose(zapis_etapu);
	fopen_s(&log_etapow, "log.txt", "a"); 
	if (log_etapow == NULL) //sprawdzenie poprawno�ci otwarcia pliku z logiem
	{
		perror("blad otwarcia pliku z logiem etapow"); 
		exit(-10);
	}
	fprintf(log_etapow, "%s", nazwa_etapu, 20); //aktualizacja logu
	fprintf(log_etapow, " ");
	fclose(log_etapow);
	printf("Zapisano nastepujacy etap:\n");
	tworzony_etap.dlugosc = y; //"wpisanie" etapu do struktury
	tworzony_etap.szerokosc = x;
	tworzony_etap.etap_wsk = etap;
	wyswietl_etap_c(tworzony_etap, 0); //wy�wietlenie etapu
	czysc_pamiec(&tworzony_etap); //usuni�cie etapu z pami�ci
}
void wczytaj_etap(char* nazwa_etapu, Etap* o_etap) //funkcja wczytuj�ca etap z pliku do pami�ci
{
	FILE* etap;
	int szerokosc, dlugosc;
	char** etap_tab;
	char bufor_znakowy;
	int i,j,k; //liczniki p�tli
	fopen_s(&etap, nazwa_etapu, "r");
	if (etap == NULL) //sprawdzenie poprawno�ci otwarcia pliku z etapem
	{
		perror("Blad otwarcia pliku z etapem.");
		exit(-10);
	}
	fscanf_s(etap, "%d", &szerokosc);
	fseek(etap, 1, SEEK_CUR);
	fscanf_s(etap, "%d", &dlugosc);
	fseek(etap, 1, SEEK_CUR);
	etap_tab = (char**)malloc(dlugosc*sizeof(char*)); //alokacja tablicy dwuwymiarowej przeznaczonej do wczytania etapu
	for (i = 0; i < dlugosc; i++)
	{
		etap_tab[i] = (char*)malloc(szerokosc*sizeof(char));
	}
	for (j = 0; j < dlugosc; j++)
	{
		for (k = 0; k < szerokosc; k++)
			fscanf_s(etap, "%c", &etap_tab[j][k]); //wczytywanie etapu znak po znaku
	}
	fclose(etap);
	o_etap->dlugosc = dlugosc; //"wpisanie" wczytanego etapu do struktury
	o_etap->szerokosc = szerokosc;
	o_etap->etap_wsk = etap_tab;
}
int znajdz_a_K(Etap o_etap) //funkcja wyszukuj�ca kolumny w kt�rej znajduje si� posta�
{
	int i, j;
	for (i = 0; i < o_etap.dlugosc; i++)
	{
		for (j = 0; j < o_etap.szerokosc; j++)
		{
			if (o_etap.etap_wsk[i][j] == 'a')
				return j; //zwr�cenie numeru kolumny
		}
	}
}
int znajdz_a_W(Etap o_etap) //funkcja wyszukuj�ca wiersza w kt�rej znajduje si� posta�
{
	int i, j;
	for (i = 0; i < o_etap.dlugosc; i++)
	{
		for (j = 0; j < o_etap.szerokosc; j++)
		{
			if (o_etap.etap_wsk[i][j] == 'a')
				return i; //zwr�cenie numeru wiersza
		}
	}
}
void ruch_w_gore(Etap* o_etap, int* obecne_polozenie_W, int* obecne_polozenie_K) //funkcja przesuwaj�ca element o 1 pole w g�r�
{
	o_etap->etap_wsk[*(obecne_polozenie_W) - 1][*obecne_polozenie_K] = o_etap->etap_wsk[*obecne_polozenie_W][*obecne_polozenie_K]; //przeniesienie elementu
	o_etap->etap_wsk[*obecne_polozenie_W][*obecne_polozenie_K] = ' '; //wyczyszczenie obecnego pola
	*(obecne_polozenie_W) = *(obecne_polozenie_W)-1; //aktualizacja po�o�enia
}
void ruch_w_dol(Etap* o_etap, int* obecne_polozenie_W, int* obecne_polozenie_K) //funkcja przesuwaj�ca element o 1 pole w d�
{
	o_etap->etap_wsk[*(obecne_polozenie_W) + 1][*obecne_polozenie_K] = o_etap->etap_wsk[*obecne_polozenie_W][*obecne_polozenie_K]; //przeniesienie elementu
	o_etap->etap_wsk[*obecne_polozenie_W][*obecne_polozenie_K] = ' '; //wyczyszczenie obecnego pola
	*(obecne_polozenie_W) = *(obecne_polozenie_W)+1; //aktualizacja po�o�enia
}
void ruch_w_lewo(Etap* o_etap, int* obecne_polozenie_W, int* obecne_polozenie_K) //funkcja przesuwaj�ca element o 1 pole w lewo
{
	o_etap->etap_wsk[*obecne_polozenie_W][*(obecne_polozenie_K) - 1] = o_etap->etap_wsk[*obecne_polozenie_W][*obecne_polozenie_K]; //przeniesienie elementu
	o_etap->etap_wsk[*obecne_polozenie_W][*obecne_polozenie_K] = ' '; //wyczyszczenie obecnego pola
	*(obecne_polozenie_K) = *(obecne_polozenie_K)-1; //aktualizacja po�o�enia
}
void ruch_w_prawo(Etap* o_etap, int* obecne_polozenie_W, int* obecne_polozenie_K) //funkcja przesuwaj�ca element o 1 pole w prawo
{
	o_etap->etap_wsk[*obecne_polozenie_W][*(obecne_polozenie_K) + 1] = o_etap->etap_wsk[*obecne_polozenie_W][*obecne_polozenie_K]; //przeniesienie elementu
	o_etap->etap_wsk[*obecne_polozenie_W][*obecne_polozenie_K] = ' '; //wyczyszczenie obecnego pola
	*(obecne_polozenie_K) = *(obecne_polozenie_K)+1; //aktualizacja po�o�enia
}
int sterowanie(Etap* o_etap, Gra* n_gra) //funkcja obs�uguj�ca dzia�anie gry
{
	int znak, obecne_polozenie_K, obecne_polozenie_W;
	int wyjscie;
	obecne_polozenie_W = znajdz_a_W(*o_etap); //znalezienie po�o�enia postaci na mapie
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
			znak = _getch(); //zcztanie znaku z klawiatury
			switch (znak)
			{
			case 72: //ruch w g�re
				if ((obecne_polozenie_W - 1 >= 0) && (o_etap->etap_wsk[obecne_polozenie_W - 1][obecne_polozenie_K] != '|')) //sprawdzenie mo�liwo�ci ruchu na dane pole
				{
					if (o_etap->etap_wsk[obecne_polozenie_W - 1][obecne_polozenie_K] == 'x') //sprawdzenie czy nie trafiamy na przeciwnika
					{
						o_etap->etap_wsk[obecne_polozenie_W][obecne_polozenie_K] = ' ';
						n_gra->liczba_punktow = 0;
						wyjscie = -1; //pora�ka
					}
					else
					{
						wyjscie = meta(*o_etap, znak, obecne_polozenie_W, obecne_polozenie_K); //sprawdzenie czy nie trafimy na met�
						n_gra->liczba_punktow = n_gra->liczba_punktow + punkty(*o_etap, znak, obecne_polozenie_W, obecne_polozenie_K); //aktualizacja punkt�w
						ruch_w_gore(o_etap, &obecne_polozenie_W, &obecne_polozenie_K);
					}
				}
				break;
			case 75: //ruch w lewo
				if ((obecne_polozenie_K - 1 >= 0) && (o_etap->etap_wsk[obecne_polozenie_W][obecne_polozenie_K - 1] != '|')) //sprawdzenie mo�liwo�ci ruchu na dane pole
				{
					if (o_etap->etap_wsk[obecne_polozenie_W][obecne_polozenie_K - 1] == 'x') //sprawdzenie czy nie trafiamy na przeciwnika
					{
						o_etap->etap_wsk[obecne_polozenie_W][obecne_polozenie_K] = ' ';
						n_gra->liczba_punktow = 0;
						wyjscie = -1; //pora�ka
					}
					else
					{
						wyjscie = meta(*o_etap, znak, obecne_polozenie_W, obecne_polozenie_K); //sprawdzenie czy nie trafimy na met�
						n_gra->liczba_punktow = n_gra->liczba_punktow + punkty(*o_etap, znak, obecne_polozenie_W, obecne_polozenie_K); //aktualizacja punkt�w
						ruch_w_lewo(o_etap, &obecne_polozenie_W, &obecne_polozenie_K);
					}
				}
				break;
			case 80: //ruch w d�
				if ((obecne_polozenie_W + 1 < o_etap->dlugosc) && (o_etap->etap_wsk[obecne_polozenie_W + 1][obecne_polozenie_K] != '|')) //sprawdzenie mo�liwo�ci ruchu na dane pole
				{
					if (o_etap->etap_wsk[obecne_polozenie_W + 1][obecne_polozenie_K] == 'x') //sprawdzenie czy nie trafiamy na przeciwnika
					{
						o_etap->etap_wsk[obecne_polozenie_W][obecne_polozenie_K] = ' ';
						n_gra->liczba_punktow = 0;
						wyjscie = -1; //pora�ka
					}
					else
					{
						wyjscie = meta(*o_etap, znak, obecne_polozenie_W, obecne_polozenie_K); //sprawdzenie czy nie trafimy na met�
						n_gra->liczba_punktow = n_gra->liczba_punktow + punkty(*o_etap, znak, obecne_polozenie_W, obecne_polozenie_K); //aktualizacja punkt�w
						ruch_w_dol(o_etap, &obecne_polozenie_W, &obecne_polozenie_K);
					}
				}
				break;
			case 77: //ruch w prawo
				if ((obecne_polozenie_K + 1 < o_etap->szerokosc) && (o_etap->etap_wsk[obecne_polozenie_W][obecne_polozenie_K + 1] != '|')) //sprawdzenie mo�liwo�ci ruchu na dane pole
				{
					if (o_etap->etap_wsk[obecne_polozenie_W][obecne_polozenie_K + 1] == 'x') //sprawdzenie czy nie trafiamy na przeciwnika
					{
						o_etap->etap_wsk[obecne_polozenie_W][obecne_polozenie_K] = ' ';
						n_gra->liczba_punktow = 0;
						wyjscie = -1; //pora�ka
					}
					else
					{
						wyjscie = meta(*o_etap, znak, obecne_polozenie_W, obecne_polozenie_K); //sprawdzenie czy nie trafimy na met�
						n_gra->liczba_punktow = n_gra->liczba_punktow + punkty(*o_etap, znak, obecne_polozenie_W, obecne_polozenie_K); //aktualizacja punkt�w
						ruch_w_prawo(o_etap, &obecne_polozenie_W, &obecne_polozenie_K);
					}
				}
				break;
			}
			if (wyjscie == 0)
				wyjscie = ruch_przeciwnikow(o_etap, n_gra); //ruch przeciwnik�w
			wyswietl_etap_c(*o_etap, 1);
			printf("Wynik: %d\n", n_gra->liczba_punktow);
		}
	}
	if (wyjscie == 1) //uko�czenie gry
		komunikat_koncowy();
	if (wyjscie == -1) //pora�ka
		komunikat_koncowy2();
	return wyjscie; //zwr�cenie informacji o ko�cu gry
}
int meta(Etap o_etap, int znak, int wiersz, int kolumna) //funkcja sprawdzaj�ca czy na danym polu znajduje si� meta
{
	int wynik = 0;
	switch (znak) //zmienna "znak" informuje o kierunku ruchu postaci
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
	return wynik; //zwr�cenie odpowiedzi (1-tak, 0-nie)
}
int punkty(Etap o_etap, int znak, int wiersz, int kolumna) //funkcja zliczaj�ca punkty
{
	int points = 0;
	switch (znak) //zmienna "znak" informuje o kierunku ruchu postaci
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
	return points; //zwr�cenie liczby punkt�w
}
int ruch_przeciwnikow(Etap* o_etap, Gra* n_gra) //funkcja przesuwaj�ca przeciwnk�w po mapie
{
	int i, j, itmp, jtmp, p_blok_W, p_blok_K;
	int ziarno;
	ziarno = rand() % 4; //wylosowanie kierunku ruchy
	p_blok_K = o_etap->szerokosc + 1;
	p_blok_W = o_etap->dlugosc + 1;
	for (i = 0; i < o_etap->dlugosc; i++)
	{
		for (j = 0; j < o_etap->szerokosc; j++)
		{
			if (o_etap->etap_wsk[i][j] == 'x') //wyszukanie przeciwnika
			{
				itmp = i;
				jtmp = j;
				switch (ziarno) //wybranie kierunku ruchu
				{
				case 0: //ruch w g�r�
					if ((i - 1 >= 0) && (o_etap->etap_wsk[i - 1][j] != '|') && (o_etap->etap_wsk[i - 1][j] != '*')  && (o_etap->etap_wsk[i - 1][j] != 'x')) //sprawdzenie mo�liwo�ci ruchu na dane pole
					{
						if (o_etap->etap_wsk[i - 1][j] == 'a') //wykrycie postaci na polu do ruchu
						{
							ruch_w_gore(o_etap, &itmp, &jtmp);
							o_etap->etap_wsk[i][j] = '.';
							n_gra->liczba_punktow = 0;
							return -1; //pora�ka
						}
						ruch_w_gore(o_etap, &itmp, &jtmp); //ruch w g�r�
						o_etap->etap_wsk[i][j] = '.';
					}
					break;
				case 1: //ruch w lewe
					if ((j - 1 >= 0) && (o_etap->etap_wsk[i][j - 1] != '|') && (o_etap->etap_wsk[i][j - 1] != '*') && (o_etap->etap_wsk[i][j - 1] != 'x')) //sprawdzenie mo�liwo�ci ruchu na dane pole
					{
						if (o_etap->etap_wsk[i][j - 1] == 'a') //wykrycie postaci na polu do ruchu
						{
							ruch_w_lewo(o_etap, &itmp, &jtmp);
							o_etap->etap_wsk[i][j] = '.';
							n_gra->liczba_punktow = 0;
							return -1; //pora�ka
						}
						ruch_w_lewo(o_etap, &itmp, &jtmp); //ruch w lewo
						o_etap->etap_wsk[i][j] = '.';
					}
					break;
				case 2: //ruch w d�
					if ((i + 1 <= o_etap->dlugosc) && (p_blok_W != i) && (o_etap->etap_wsk[i + 1][j] != '|') && (o_etap->etap_wsk[i + 1][j] != '*') && (o_etap->etap_wsk[i + 1][j] != 'x')) //sprawdzenie mo�liwo�ci ruchu na dane pole
					{
						if (o_etap->etap_wsk[i + 1][j] == 'a') //wykrycie postaci na polu do ruchu
						{
							ruch_w_dol(o_etap, &itmp, &jtmp);
							o_etap->etap_wsk[i][j] = '.';
							n_gra->liczba_punktow = 0;
							return -1; //pora�ka
						}
						ruch_w_dol(o_etap, &itmp, &jtmp); //ruch w d�
						o_etap->etap_wsk[i][j] = '.';
						p_blok_W = i + 1;
					}
					break;
				case 3: //ruch w prawo
					if ((j + 1 <= o_etap->szerokosc) && (p_blok_K != j) && (o_etap->etap_wsk[i][j + 1] != '|') && (o_etap->etap_wsk[i][j + 1] != '*') && (o_etap->etap_wsk[i][j + 1] != 'x')) //sprawdzenie mo�liwo�ci ruchu na dane pole
					{
						if (o_etap->etap_wsk[i][j + 1] == 'a') //wykrycie postaci na polu do ruchu
						{
							ruch_w_prawo(o_etap, &itmp, &jtmp);
							o_etap->etap_wsk[i][j] = '.';
							n_gra->liczba_punktow = 0;
							return -1; //pora�ka
						}
						ruch_w_prawo(o_etap, &itmp, &jtmp); //ruch w prawo
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
void zapisz_wyniki(Gra n_gra) //funkcja zapisuj�ca wyniki do pliku
{
	FILE* plik;
	fopen_s(&plik, "wyniki.txt", "a");
	if (plik == NULL) //sprawdzenie poprawno�ci otwarcia pliku do zapisu wynik�w
	{
		perror("Blad otwarcia pliku do zapisu wynikow.\n");
		exit(-10);
	}
	fprintf(plik, "%s ", n_gra.nazwa_etapu, 20); //zapis nazwy etapu
	fprintf(plik, "%s ", n_gra.nazwa_gracza, 20); //zapis nazwy gracza
	fprintf(plik, "%d\n", n_gra.liczba_punktow); //zapis liczby punkt�w
	fclose(plik);
}
void wyswietl_wyniki(void) //funkcja wy�wietlaj�ca wyniki zapisane w pliku
{
	FILE* plik;
	int c;
	Gra bufor; //zmienna pomocnicza
	fopen_s(&plik, "wyniki.txt", "r");
	if (plik == NULL) //sprawdzenie poprawno�ci otwarcia pliku do zapisu wynik�w
	{
		printf("Blad otwarcia pliku z wynikami/Plik z wynikami nie istnieje\n");
	}
	else
	{
		printf("Nazwa etapu/Nazwa gracza/ilosc punktow\n");
		while ((c = fgetc(plik)) != EOF) //przeszukiwanie pliku a� do znaku ko�ca pliku
		{
			fseek(plik, -1, SEEK_CUR);
			fscanf_s(plik, "%s", bufor.nazwa_etapu, 20); //wczytanie wynik�w do zmiennej pomocniczej
			fscanf_s(plik, "%s", bufor.nazwa_gracza, 20);
			fscanf_s(plik, "%d", &bufor.liczba_punktow);
			printf("%s/", bufor.nazwa_etapu, 20); //wy�wietlenie wynik�w na ekranie
			printf("%s/", bufor.nazwa_gracza, 20);
			printf("%d\n", bufor.liczba_punktow);
			fseek(plik, 2, SEEK_CUR);
		}
		fclose(plik);
	}
	
}
int main()
{
	srand(time(NULL));
	int wybor, w_x, w_y, dlugosc_etapu, szerokosc_etapu, wyjscie;
	char nazwa_etapu[20]; //tablica pomocnicza
	Etap Obecny_etap;
	Gra Nowa_gra;
	wyjscie = 1;
	while (1)
	{
		komunikat();
		scanf_s("%d", &wybor); //wybranie opcji z MENU
		switch (wybor)
		{
		case 1: //nowa gra
			printf("Wybrales nowa gre.\n");
			instrukcja_do_gry();
			printf("Podaj swoje imie.\n");
			scanf_s("%s", Nowa_gra.nazwa_gracza, 20);
			printf("---------------\n");
			while (wyjscie == 1) //przej�cie do kolejnego poziomu (po dotarciu na met� w poprzednim)
			{
				wyswietl_liste_etapow();
				printf("Wybierz etap z powyzszej listy.\n");
				scanf_s("%s", &Nowa_gra.nazwa_etapu, 20);
				wczytaj_etap(Nowa_gra.nazwa_etapu, &Obecny_etap);
				wyjscie = sterowanie(&Obecny_etap, &Nowa_gra);
				zapisz_wyniki(Nowa_gra);
				czysc_pamiec(&Obecny_etap);
				printf("\n");
			}
			break;
		case 2: //tworzenie etapu
			printf("Wybrales tworzenie etapow\n");
			instrukcja_tworzenia_etapu();
			printf("Podaj szerokosc mapy.\n");
			scanf_s("%d", &w_x);
			printf("Podaj dlugosc mapy.\n");
			scanf_s("%d", &w_y);
			tworzenie_etapu(w_x, w_y);
			printf("\n");
			break;
		case 3: //wy�wietlenie wynik�w
			printf("Wybrales tabele wynikow\n");
			wyswietl_wyniki();
			printf("\n");
			break;
		case 4: //wyj�cie
			exit(0);
		default:
			printf("Wybrales bledna opcje. Sprobuj ponownie\n\n");
			break;
		}
	}
	system("Pause");
	return 0;
}