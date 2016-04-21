#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
typedef struct Slowo_
{
	int lw; //liczba wyst�pie� s�owa
	char *slowo;// slowo
	struct Slowo_ *prawy; //prawy i lewy potomek
	struct Slowo_ *lewy; //
} Slowo;
typedef struct Slownik_
{
	int ls; //liczba wszystkich unikalnych s��w
	int h; // wysoko�� drzewa - liczba poziom�w
	Slowo *korzen;
	Slowo *mf; // wska�nik na s�owo najcz�sciej wyst�puj�ce
	Slowo **t; // realokowalna tablica wska�nik�w do wszystkich nie powtarzaj�cych si� s��w w drzewie (realokacja co K=1000 element�w)
			   // pomocna przy sortowaniu (przestawiamy wska�niki) - funkcja nr 2 (dalsza cz�� zadnia)

} Slownik;
int dlugosc_slowa(char* slowo)
{
	int licznik = 0;
	while (slowo[licznik] != '\0')
		licznik++;
	licznik++; //dodanie miejsca na znak ko�ca �a�cucha
	return licznik;
}
Slowo* wstaw(Slownik *s, char *slowo)
{
	Slowo* korzen_tmp;
	Slowo* nowe_slowo;
	nowe_slowo = NULL;
	korzen_tmp = s->korzen; //zapami�tanie korzenia
	int dl_slowa = dlugosc_slowa(slowo); //funkcja zwraca d�ugo�� s�owa+1 (miejsce na znak ko�ca �a�cucha)
	char* slowo_tab;
	slowo_tab = (char*)malloc(dl_slowa*sizeof(char));
	memcpy(slowo_tab, slowo, dl_slowa*sizeof(char));
	while (s->korzen != NULL)
	{
		if (strcmp(s->korzen->slowo, slowo) == 0) //sprawdzenie czy s�owo jest ju� w drzewie
		{
			s->korzen->lw = s->korzen->lw + 1;
			if (s->korzen->lw > s->mf->lw) //sprawdzenie czy najliczniejsze s�owo dalej nim jest
			{
				s->mf = s->korzen;
			}
			s->korzen = korzen_tmp; //przywr�cenie w�a�ciwego korzenia
			return NULL;
		}
		if (strcmp(s->korzen->slowo, slowo) > 0)
		{
			if (s->korzen->lewy != NULL)
				s->korzen = s->korzen->lewy;
			else
			{
				nowe_slowo = (Slowo*)malloc(sizeof(Slowo)); //dodanie s�owa "na lewo"
				nowe_slowo->lewy = NULL;
				nowe_slowo->prawy = NULL;
				nowe_slowo->slowo = slowo_tab;
				nowe_slowo->lw = 1;
				s->korzen->lewy = nowe_slowo;
				if (s->korzen->prawy == NULL)
					s->h = s->h + 1;
				break;
			}
		}
		else
		{
			if(s->korzen->prawy!=NULL)
				s->korzen = s->korzen->prawy;
			else
			{
				nowe_slowo = (Slowo*)malloc(sizeof(Slowo)); //dodanie s�owa "na prawo"
				nowe_slowo->lewy = NULL;
				nowe_slowo->prawy = NULL;
				nowe_slowo->slowo = slowo_tab;
				nowe_slowo->lw = 1;
				s->korzen->prawy = nowe_slowo;
				if (s->korzen->lewy == NULL)
					s->h = s->h + 1;
				break;
			}
		}
	}
	if (s->korzen == NULL)
	{
		nowe_slowo = (Slowo*)malloc(sizeof(Slowo)); //tworzenie pierwszego s�owa (gdy �adne nie by�o jeszcze dodane)
		nowe_slowo->lewy = NULL;
		nowe_slowo->prawy = NULL;
		nowe_slowo->slowo = slowo_tab;
		nowe_slowo->lw = 1;
		s->korzen = nowe_slowo;
		s->mf = nowe_slowo;
		s->h = 1;
	}
	else
		s->korzen = korzen_tmp;
	return nowe_slowo;
}
Slownik* tworz_slownik(char* nazwa_pliku)
{
	FILE* plik;
	Slownik* nowy_slownik;
	nowy_slownik = (Slownik*)malloc(sizeof(Slownik));
	Slowo* wstawiany_element;
	int max_dl = 50; //maksymalna dlugosc slowa
	char bufor[50]; //bufor wczytuj�cy s�owa
	int slowa_il = 1000;
	int licznik = 0;
	int licznik2 = 1;
	nowy_slownik->t = (Slowo**)malloc(slowa_il*sizeof(Slowo*)); //pocz�tkowa imicjalizacja s�ownika
	nowy_slownik->mf = NULL;
	nowy_slownik->ls = 0;
	nowy_slownik->h = 0;
	nowy_slownik->korzen = NULL;
	fopen_s(&plik, nazwa_pliku, "r");
	while (!feof(plik))
	{
		fscanf_s(plik, "%s", bufor, max_dl);
		wstawiany_element = wstaw(nowy_slownik, bufor);
		if (wstawiany_element != NULL)
		{
			nowy_slownik->ls = nowy_slownik->ls + 1;
			if (licznik == (licznik2*slowa_il)-1) //sprawdzenie tablica s�ow nie b�dzie przepe�niona
			{
				licznik2++;
				nowy_slownik->t = (Slowo**)realloc(nowy_slownik->t, licznik2*sizeof(Slowo*));
			}
			nowy_slownik->t[licznik] = wstawiany_element;
			licznik++;
			if (nowy_slownik->mf == NULL)
				nowy_slownik->mf = wstawiany_element;
		}
	}
	//fclose(plik);
	return nowy_slownik;
}
void zapisz_do_pliku(Slownik aktualny_slownik, char* nazwa_pliku)
{
	FILE* plik;
	int i; //licznim p�tli
	int licznik = aktualny_slownik.mf->lw;
	fopen_s(&plik, nazwa_pliku, "w");
	while (licznik != 0)
	{
		for (i = 0; i < aktualny_slownik.ls; i++)
		{
			if (aktualny_slownik.t[i]->lw == licznik)
			{
				fprintf(plik, "%s", aktualny_slownik.t[i]->slowo);
				fprintf(plik, "%d", aktualny_slownik.t[i]->lw);
				fprintf(plik, " ");
			}
		}
		licznik--;
	}
	fclose(plik);
}
double wys_drzewa_iloraz(Slownik aktualny_slownik)
{
	double iloraz;
	double idealna_wysokosc, idealna_wysokosc_zaokr;
	idealna_wysokosc = log2(aktualny_slownik.ls);
	idealna_wysokosc_zaokr = ceil(idealna_wysokosc);
	iloraz = aktualny_slownik.h / idealna_wysokosc_zaokr;
	return iloraz;
}
void usun_drzewo(Slowo* korzen)
{
	if (korzen != NULL)
	{
		if ((korzen->lewy != NULL) && (korzen->prawy != NULL))
		{
			usun_drzewo(korzen->lewy);
			usun_drzewo(korzen->prawy);
		}
		else
		{
			if (korzen->lewy != NULL)
				usun_drzewo(korzen->lewy);
			else
				usun_drzewo(korzen->prawy);
		}
		free(korzen->slowo);
		free(korzen);
	}
}
int main()
{
	Slownik* nowy_slownik;
	double stos_wys_drzewa;
	nowy_slownik = tworz_slownik("drzewo.txt");
	//printf("%s", nowy_slownik->korzen->lewy->slowo, 20); //usun��
	zapisz_do_pliku(*nowy_slownik, "zapis.txt");
	stos_wys_drzewa = wys_drzewa_iloraz(*nowy_slownik);
	printf("stosunek wysokosci drzewa do idealnego drzewa wynosi: %f\n", stos_wys_drzewa);
	usun_drzewo(nowy_slownik->korzen);
	free(nowy_slownik);
	system("Pause");
	return 0;
}