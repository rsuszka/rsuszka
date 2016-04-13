/*Napisa� gr�, w kt�rej zadaniem u�ytkownika b�dzie chodzenie po labiryncie, zbieranie przedmiot�w oraz
unikanie  ruchomych  przeciwnik�w.Jednym  z  element�w  mapy  powinno  by�  wyj�cie, kt�re  skieruje  u�yt -
kownika  do  kolejnego  poziomu.Poziomy  powinny  by�  zapisywane  w  osobnych  plikach;  program  powinien
obs�ugiwa� mo�liwo�� dodawania nowych poziom�w.Program musi zapami�tywa� oraz zapisywa� w pliku
wszystkie wyniki uzyskane przez graczy.*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
void komunikat(void)
{
	printf("Witaj w grze LABIRYNY!\n");
	printf("Wybierz co chcesz zrobic i zatwierdz to klawiszem Enter\n");
	printf("1. Nowa gra\n");
	printf("2. Tworzenie etapow\n");
	printf("3. Tabela wynikow\n");
	printf("4. Wyjscie\n");
}
int d_etapu(char* nazwa_pliku)
{
	FILE* plik;
	int dlugosc;
	fopen_s(&plik, nazwa_pliku, "r");
	if (plik == NULL)
	{
		perror("Blad otwarcia pliku z etapem.");
		exit(-10);
	}
	fseek(plik, 2, SEEK_SET);
	fscanf_s(plik, "%d", &dlugosc);
	fclose(plik);
	return dlugosc;
}
int s_etapu(char* nazwa_pliku)
{
	FILE* plik;
	int szerokosc;
	fopen_s(&plik, nazwa_pliku, "r");
	if (plik == NULL)
	{
		perror("Blad otwarcia pliku z etapem.");
		exit(-10);
	}
	fscanf_s(plik, "%d", &szerokosc);
	fclose(plik);
	return szerokosc;
}
void wyswietl_etap_c(char** etap_wsk, int dlugosc, int szerokosc, int czysc)
{
	int i, j;
	if (czysc==1)
		system("cls");
	for (i = 0; i < dlugosc; i++)
	{
		for (j = 0; j < szerokosc; j++)
			printf("%c", etap_wsk[i][j]);
		printf("\n");
	}
}
void czysc_pamiec(char** tablica_wsk, int dlugosc)
{
	int i;
	for (i = 0; i < dlugosc; i++) //zwolnienie pamieci
		free(tablica_wsk[i]);
	free(tablica_wsk);
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
		scanf_s("%s", bufor,50);
		for (l = 0; l < x; l++)
		{
			etap[k][l] = bufor[l];
		}
	}
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
	wyswietl_etap_c(etap, y, x, 0);
	czysc_pamiec(etap, y);
}
char** wczytaj_etap(char* nazwa_etapu)
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
	return etap_tab;
}
int main()
{
	int wybor, w_x, w_y, dlugosc_etapu, szerokosc_etapu;
	bool spr_wyboru = true;
	char nazwa_etapu[20];
	char** etap_wsk;
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
			etap_wsk = wczytaj_etap(nazwa_etapu);
			dlugosc_etapu = d_etapu(nazwa_etapu);
			szerokosc_etapu = s_etapu(nazwa_etapu);
			wyswietl_etap_c(etap_wsk, dlugosc_etapu, szerokosc_etapu, 1);
			czysc_pamiec(etap_wsk, dlugosc_etapu);
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