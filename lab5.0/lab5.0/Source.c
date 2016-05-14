/*Napisaæ program który wczytuje pliki binarne  do tablicy dynamicznej tab:
Hex * tab;
typedef struct HexByte
 {
   char [2]; // reprezntacja bajtu w postaci 16-owej (ascii)
   unsigned char;// w postci binarnej
 } HexByte
 
Program wywo³uje siê z lini komend (cmd) z nastepuj¹cymi opcjami:
hex.exe plik.in -ot plik.txt // zapisuje wczytany plik w postaci tekstowej
hex.exe plik.in -ob plik.bin  // zapisuje wczytany plik w postaci binarne
hex.exe plik.in  -d FA36  // usuwa z pliku ci¹g bajtów 
hex.exe plik.in  -r  DB A908 FFAA33 // zastêpuje jeden ci¹g bajtów innym ci¹giem
Opcje -d i -r mog¹ wystêpowaæ opcj¹ -ot albo -ob*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct HexByte_
{
	char bajt_sz[2]; // reprezntacja bajtu w postaci 16-owej (ascii)
	unsigned char bajt_b;// w postci binarnej
} HexByte;
int dlugosc(char* ciag) //funkcja obliczajaca dlugosc ciagu znakow
{
	int licznik;
	licznik = 0;
	while (1)
	{
		if (ciag[licznik] == '\0')
			break;
		licznik++;
	}
	return licznik;
}
void konw_na_16(int kod_ASCI, char* t_bajt) //funkcja zamienia kod ASCI z postaci dziesietnej na szesnastkow¹
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
char konw_na_bin(char a, char b) //funkcja zamienia kod ASCI z postaci szesnastkowej na dziesietna (i zwraca znak odpowiadajacy temu kodowi)
{
	int i, ASCI;
	char wybor, wynik;
	wybor = a;
	ASCI = 0;
	for (i = 0; i < 2; i++)
	{
		switch (wybor)
		{
		case '1':
			if (i == 0)
				ASCI = ASCI + 1 * 16;
			else
				ASCI = ASCI + 1;
			break;
		case '2':
			if (i == 0)
				ASCI = ASCI + 2 * 16;
			else
				ASCI = ASCI + 2;
			break;
		case '3':
			if (i == 0)
				ASCI = ASCI + 3 * 16;
			else
				ASCI = ASCI + 3;
			break;
		case '4':
			if (i == 0)
				ASCI = ASCI + 4 * 16;
			else
				ASCI = ASCI + 4;
			break;
		case '5':
			if (i == 0)
				ASCI = ASCI + 5 * 16;
			else
				ASCI = ASCI + 5;
			break;
		case '6':
			if (i == 0)
				ASCI = ASCI + 6 * 16;
			else
				ASCI = ASCI + 6;
			break;
		case '7':
			if (i == 0)
				ASCI = ASCI + 7 * 16;
			else
				ASCI = ASCI + 7;
			break;
		case '8':
			if (i == 0)
				ASCI = ASCI + 8 * 16;
			else
				ASCI = ASCI + 8;
			break;
		case '9':
			if (i == 0)
				ASCI = ASCI + 9 * 16;
			else
				ASCI = ASCI + 9;
			break;
		case 'A':
			if (i == 0)
				ASCI = ASCI + 10 * 16;
			else
				ASCI = ASCI + 10;
			break;
		case 'B':
			if (i == 0)
				ASCI = ASCI + 11 * 16;
			else
				ASCI = ASCI + 11;
			break;
		case 'C':
			if (i == 0)
				ASCI = ASCI + 12 * 16;
			else
				ASCI = ASCI + 12;
			break;
		case 'D':
			if (i == 0)
				ASCI = ASCI + 13 * 16;
			else
				ASCI = ASCI + 13;
			break;
		case 'E':
			if (i == 0)
				ASCI = ASCI + 14 * 16;
			else
				ASCI = ASCI + 14;
			break;
		case 'F':
			if (i == 0)
				ASCI = ASCI + 15 * 16;
			else
				ASCI = ASCI + 15;
			break;
		}
		wybor = b;
	}
	wynik = ASCI;
	return ASCI;
}
HexByte** wczytaj_plik_b(HexByte* tab, char* nazwa_pliku, int* dl_tab) //funkcja wczytujaca plik binarny
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
	while (!feof(plik)) //wczytywanie az do napotkania znaku konca pliku
	{
		tab = realloc(tab, licznik*sizeof(HexByte));
		fread(&bufor, sizeof(char), 1, plik);
		str_pom.bajt_b = bufor;
		konw_na_16(bufor, str_pom.bajt_sz);
		tab[licznik - 1] = str_pom;
		licznik++;
	}
	fclose(plik);
	*dl_tab = licznik - 1;
	return tab;
}
void zapisz_txt(HexByte* tab, char* nazwa_pliku, int dlugosc_tab) //funkcja zapisuje strukture do pliku tekstowego
{
	FILE* plik;
	HexByte bufor;
	int licznik;
	fopen_s(&plik, nazwa_pliku, "w");
	if (plik == NULL)
	{
		printf("Blad otwarica pliku\n");
		exit(-10);
	}
	for (licznik = 0; licznik < dlugosc_tab; licznik++)
	{
		bufor = tab[licznik];
		fwrite(&bufor.bajt_sz[0], sizeof(char), 1, plik);
		fwrite(&bufor.bajt_sz[1], sizeof(char), 1, plik);
	}
	fclose(plik);
}
void zapisz_bin(HexByte* tab, char* nazwa_pliku, int dlugosc_tab) //funkcja zapisuje strukture do pliku binarnego
{
	FILE* plik;
	int i;
	HexByte bufor;
	fopen_s(&plik, nazwa_pliku, "wb");
	if (plik == NULL)
	{
		printf("Blad otwarcia pliku\n");
		exit(-10);
	}
	for (i = 0; i < dlugosc_tab; i++)
	{
		bufor = tab[i];
		fwrite(&bufor.bajt_b, sizeof(char), 1, plik);
	}
	fclose(plik);
}
void usun_ciag_bajtow(HexByte* tab, int dlugosc_tab, char* ciag, char* nazwa_pliku) //funcja usuwa ciag bajtow z pliku zrodlowego
{
	FILE* plik;
	char* bufor_pomocniczy;
	char* wskaznik_na_wystapienie;
	int i, j, k, l, licznik, dl_ciagu;
	HexByte zm_pomocnicza;
	HexByte* kopia_tablicy;
	licznik = 0;
	bufor_pomocniczy = (char*)malloc((2 * dlugosc_tab)*sizeof(char));
	kopia_tablicy = (HexByte*)malloc(dlugosc_tab*sizeof(char));
	for (k = 0; k < dlugosc_tab; k++) //zrobienie kopii tablicy
	{
		kopia_tablicy[k] = tab[k];
	}
	dl_ciagu = dlugosc(ciag);
	for (i = 0; i < dlugosc_tab; i++) //wczytanie do tablicy pomocniczej bajtow w postaci szesnastkowej
	{
		zm_pomocnicza = tab[i];
		bufor_pomocniczy[licznik] = zm_pomocnicza.bajt_sz[0];
		licznik++;
		bufor_pomocniczy[licznik] = zm_pomocnicza.bajt_sz[1];
		licznik++;
	}
	wskaznik_na_wystapienie = strstr(bufor_pomocniczy, ciag); //znalezienie wystapienia danego ciagu
	if (wskaznik_na_wystapienie != NULL)
	{
		for (j = 0; j < dl_ciagu; j++)
		{
			*wskaznik_na_wystapienie = '*'; //"usuniêcie" ciagu
			wskaznik_na_wystapienie++;
		}
		fopen_s(&plik, nazwa_pliku, "wb");
		if (plik == NULL)
		{
			printf("Blad otwarcia pliku\n");
			exit(-10);
		}
		licznik = 0;
		for (l = 0; l < dlugosc_tab; l++) //zapis do pliku
		{
			if (bufor_pomocniczy[licznik] != '*')
			{
				zm_pomocnicza = kopia_tablicy[l];
				fwrite(&zm_pomocnicza.bajt_b, sizeof(char), 1, plik);
			}
			licznik = licznik + 2;
		}
		fclose(plik);
	}
	free(bufor_pomocniczy);
	free(kopia_tablicy);
}
void zamien_ciagi_bajtow(HexByte* tab, int dlugosc_tab, char* ciag_p, char* ciag_n, char* nazwa_pliku)
{
	FILE* plik;
	int i, j, k, l, m, licznik, dl_ciagu_p, dl_ciagu_n;
	HexByte zm_pomocnicza;
	char* bufor_pomocniczy;
	char* wskaznik_na_wystapienie;
	char* bufor_koncowy;
	char znak_do_zapisu;
	int licznik_koncowy = 0;
	bufor_pomocniczy = (char*)malloc((2 * dlugosc_tab)*sizeof(char));
	licznik = 0;
	for (i = 0; i < dlugosc_tab; i++) //wczytanie do tablicy pomocniczej bajtow w postaci szesnastkowej
	{
		zm_pomocnicza = tab[i];
		bufor_pomocniczy[licznik] = zm_pomocnicza.bajt_sz[0];
		licznik++;
		bufor_pomocniczy[licznik] = zm_pomocnicza.bajt_sz[1];
		licznik++;
	}

	wskaznik_na_wystapienie = strstr(bufor_pomocniczy, ciag_p); //znalezienie wystapienia danego ciagu
	if (wskaznik_na_wystapienie != NULL)
	{
		dl_ciagu_p = dlugosc(ciag_p);
		dl_ciagu_n = dlugosc(ciag_n);
		for (j = 0; j < dl_ciagu_p; j++)
		{
			*wskaznik_na_wystapienie = '*'; //"usuniêcie" ciagu
			wskaznik_na_wystapienie++;
		}
		bufor_koncowy = (char*)malloc(((2 * dlugosc_tab) - dl_ciagu_p + dl_ciagu_n)*sizeof(char));
		for (k = 0; k < (((2 * dlugosc_tab) - dl_ciagu_p + dl_ciagu_n - (dl_ciagu_n - dl_ciagu_p))); k++) //wpisanie do bufora ca³ego pliku (w postaci szesnastkowej) po zamianie ciagu bajtow
		{
			if (bufor_pomocniczy[k] != '*')
			{
				bufor_koncowy[licznik_koncowy] = bufor_pomocniczy[k];
				licznik_koncowy++;
			}
			else
			{
				for (l = 0; l < dl_ciagu_n; l++)
				{
					bufor_koncowy[licznik_koncowy] = ciag_n[l];
					licznik_koncowy++;
				}
				k = k + dl_ciagu_p - 1;
			}
		}
		fopen_s(&plik, nazwa_pliku, "wb");
		if (plik == NULL)
		{
			printf("Blad otwarcia pliu\n");
			exit(-10);
		}
		for (m = 0; m < ((2 * dlugosc_tab) - dl_ciagu_p + dl_ciagu_n); m = m + 2) //zapis do pliku
		{
			znak_do_zapisu = konw_na_bin(bufor_koncowy[m], bufor_koncowy[m + 1]);
			fwrite(&znak_do_zapisu, sizeof(char), 1, plik);
		}
		fclose(plik);
		free(bufor_koncowy);
	}
	free(bufor_pomocniczy);
}
void czysc_pamiec(HexByte* tab)
{
	free(tab);
}
int main(int argc, char* argv[])
{
	HexByte* tablica = NULL;
	int dl_tab;
	char* nazwa_pliku;
	int i;
	i = 2;
	if (argc > 0)
	{
		nazwa_pliku = argv[1];
		tablica = wczytaj_plik_b(tablica, nazwa_pliku, &dl_tab);
		while (argc > i)
		{
			if (strcmp(argv[i], "-ot") == 0)
			{
				i++;
				zapisz_txt(tablica, argv[i], dl_tab);
				i++;
			}
			else
			{
				if (strcmp(argv[i], "-ob") == 0)
				{
					i++;
					zapisz_bin(tablica, argv[i], dl_tab);
					i++;
				}
				else
				{
					if (strcmp(argv[i], "-d") == 0)
					{
						i++;
						usun_ciag_bajtow(tablica, dl_tab, argv[i], nazwa_pliku);
						free(tablica);
						tablica = wczytaj_plik_b(tablica, nazwa_pliku, &dl_tab);
						i++;
					}
					else
					{
						if (strcmp(argv[i], "-r") == 0)
						{
							i++;
							zamien_ciagi_bajtow(tablica, dl_tab, argv[i], argv[i + 1], nazwa_pliku);
							free(tablica);
							tablica = wczytaj_plik_b(tablica, nazwa_pliku, &dl_tab);
							i += 2;
						}
					}
				}
			}
		}
		czysc_pamiec(tablica);
	}
	system("Pause");
	return 0;
}