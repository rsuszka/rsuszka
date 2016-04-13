/*Napisaæ grê, w której zadaniem u¿ytkownika bêdzie chodzenie po labiryncie, zbieranie przedmiotów oraz
unikanie  ruchomych  przeciwników.Jednym  z  elementów  mapy  powinno  byæ  wyjœcie, które  skieruje  u¿yt -
kownika  do  kolejnego  poziomu.Poziomy  powinny  byæ  zapisywane  w  osobnych  plikach;  program  powinien
obs³ugiwaæ mo¿liwoœæ dodawania nowych poziomów.Program musi zapamiêtywaæ oraz zapisywaæ w pliku
wszystkie wyniki uzyskane przez graczy.*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
void komunikat()
{
	printf("Witaj w grze LABIRYNY!\n");
	printf("Wybierz co chcesz zrobic i zatwierdz to klawiszem Enter\n");
	printf("1. Nowa gra\n");
	printf("2. Tworzenie etapow\n");
	printf("3. Tabela wynikow\n");
	printf("4. Wyjscie\n");
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
	//
	for (int s = 0; s < y; s++)
	{
		for (int ss = 0; ss < x; ss++)
			printf("%c ", etap[s][ss]);
		printf("\n");
	}
	//
	fopen_s(&log_etapow, "log.txt", "r");
	if (log_etapow == NULL)
		printf("Wszystkie nazwy sa dostepne.\n");
	else
	{
		printf("Zajete juz nazwy etapow:\n");
		while ((c = fgetc(log_etapow)) != EOF)
		{
			fseek(log_etapow, -1, SEEK_CUR);
			fscanf_s(log_etapow, "%s", nazwa_etapu, 20);
			printf("%s\n", nazwa_etapu, 20);
			fseek(log_etapow, 1, SEEK_CUR);
		}
		fclose(log_etapow);
	}
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
			fprintf(zapis_etapu, "%c ", etap[m][n]);
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
	for (j = 0; j < y; j++) //zwolnienie pamieci
		free(etap[j]);
	free(etap);
}
int main()
{
	int wybor, w_x, w_y;
	bool spr_wyboru = true;
	komunikat();
	while (spr_wyboru == true)
	{
		scanf_s("%d", &wybor);
		switch (wybor)
		{
		case 1:
			printf("Wybrales nowa gre\n");
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
			system("cls");
			break;
		}
	}
	system("Pause");
	return 0;
}