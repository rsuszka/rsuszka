/*Napisaæ grê, w której zadaniem u¿ytkownika bêdzie chodzenie po labiryncie, zbieranie przedmiotów oraz
unikanie  ruchomych  przeciwników.Jednym  z  elementów  mapy  powinno  byæ  wyjœcie, które  skieruje  u¿yt -
kownika  do  kolejnego  poziomu.Poziomy  powinny  byæ  zapisywane  w  osobnych  plikach;  program  powinien
obs³ugiwaæ mo¿liwoœæ dodawania nowych poziomów.Program musi zapamiêtywaæ oraz zapisywaæ w pliku
wszystkie wyniki uzyskane przez graczy.*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct Etap_
{
	int szerokosc;
	int dlugosc;
	char** etap_wsk;
} Etap;
void komunikat(void)
{
	printf("Witaj w grze LABIRYNY!\n");
	printf("Wybierz co chcesz zrobic i zatwierdz to klawiszem Enter\n");
	printf("1. Nowa gra\n");
	printf("2. Tworzenie etapow\n");
	printf("3. Tabela wynikow\n");
	printf("4. Wyjscie\n");
}
void wyswietl_etap_c(Etap* o_etap, int czysc)
{
	int i, j;
	if (czysc==1)
		system("cls");
	for (i = 0; i < o_etap->dlugosc; i++)
	{
		for (j = 0; j < o_etap->szerokosc; j++)
			printf("%c", o_etap->etap_wsk[i][j]);
		printf("\n");
	}
}
void czysc_pamiec(Etap* o_etap)
{
	int i;
	for (i = 0; i < o_etap->dlugosc; i++) //zwolnienie pamieci
		free(o_etap->etap_wsk[i]);
	free(o_etap->etap_wsk);
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
	etap = (char**)malloc(y*sizeof(char*));
	bufor = (char*)malloc((y+1)*sizeof(char));
	for (i = 0; i < y; i++)
	{
		etap[i] = (char*)malloc(x*sizeof(char));
	}
	for (k = 0; k < y; k++)
	{
		scanf_s("%s", bufor, y+1);
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
	wyswietl_etap_c(&tworzony_etap, 0);
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
int main()
{
	int wybor, w_x, w_y, dlugosc_etapu, szerokosc_etapu;
	bool spr_wyboru = true;
	char nazwa_etapu[20];
	char** etap_wsk;
	Etap Obecny_etap;
	komunikat();
	while (spr_wyboru == true)
	{
		scanf_s("%d", &wybor);
		switch (wybor)
		{
		case 1:
			printf("Wybrales nowa gre\n");
			wyswietl_liste_etapow();
			printf("Wybierz etap z powyzszej listy.\n");
			scanf_s("%s", nazwa_etapu, 20);
			etap_wsk = wczytaj_etap(nazwa_etapu, &Obecny_etap);
			wyswietl_etap_c(&Obecny_etap, 1);
			czysc_pamiec(&Obecny_etap);
			spr_wyboru = false;
			break;
		case 2:
			printf("Wybrales tworzenie etapow\n");
			printf("Podaj szerokosc mapy.\n");
			scanf_s("%d", &w_x);
			printf("Podaj dlugosc mapy.\n");
			scanf_s("%d", &w_y);
			tworzenie_etapu(w_x, w_y);
			spr_wyboru = false;
			break;
		case 3:
			printf("Wybrales tabele wynikow\n");
			spr_wyboru = false;
			break;
		case 4:
			spr_wyboru = false;
			break;
		default:
			printf("Wybrales bledna opcje. Sprobuj ponownie\n");
			spr_wyboru = true;
			break;
		}
	}
	system("Pause");
	return 0;
}