#include<iostream>
#include<string>
#include<cstdio>
#include<conio.h>
#include<fstream>
#include<cmath>
using namespace std;
struct Wezel
{
	string nazwa;
	int Lp;
	double R_kwota;
	double M_kwota;
	Wezel* nastepny;
};
struct GlOg
{
	Wezel* Glowa;
	Wezel* Ogon;
	int Aktualny_licznik;
};

void suma_wydatkow(GlOg glowaogon, double&R_suma, double&M_suma);
void maximum(GlOg glowaogon, Wezel*&R_max, Wezel*&M_max);
void minimum(GlOg glowaogon, Wezel*&R_min, Wezel*&M_min);
void zaokraglenie_do_2_po_przecinku(double&liczba);
void Rafal_statystyki(GlOg glowaogon, int ilosc_dni);
void Mateusz_statystyki(GlOg glowaogon, int ilosc_dni);

void MENU(void)
{
	cout << "Wybierz jedna z podanych opcji:" << endl;
	cout << "1. Dodaj element" << endl;
	cout << "2. Wyswietl" << endl;
	cout << "3. Edytuj rekord" << endl;
	cout << "4. Usun rekord" << endl;
	cout << "5. Zapisz kopie danych do pliku" << endl;
	cout << "6. Wczytaj kopie danych z pliku" << endl;
	cout << "7. Wyjscie" << endl;
}
void komunikat(void)
{
	cout << "1. Wyswietl calosc" << endl;
	cout << "2. Wyswietl pojedyncza osobe" << endl;
	cout << "3. Cofnij" << endl;
}
void wstaw_element(GlOg&glowaogon, string nazwa, double cena1, double cena2)
{
	glowaogon.Aktualny_licznik++;
	Wezel* nowy_element;
	nowy_element = new Wezel;
	nowy_element->nazwa = nazwa;
	nowy_element->R_kwota = cena1;
	nowy_element->M_kwota = cena2;
	nowy_element->Lp = glowaogon.Aktualny_licznik;
	nowy_element->nastepny = NULL;
	if (glowaogon.Glowa == NULL)
	{
		glowaogon.Glowa = nowy_element;
		glowaogon.Ogon = nowy_element;
	}
	else
	{
		glowaogon.Ogon->nastepny = nowy_element;
		glowaogon.Ogon = nowy_element;
	}
}
void czysc_pamiec(GlOg&glowaogon)
{
	Wezel tmp;
	while (glowaogon.Glowa != NULL)
	{
		tmp = *glowaogon.Glowa;
		delete glowaogon.Glowa;
		glowaogon.Glowa = tmp.nastepny;
	}
}
void wyswietl_calosc(GlOg glowaogon)
{
	cout << "L.p.\tArtykul\tRafal\tMateusz\t" << endl;
	while (glowaogon.Glowa != NULL)
	{
		cout << glowaogon.Glowa->Lp << "\t";
		cout << glowaogon.Glowa->nazwa << "\t";
		cout << glowaogon.Glowa->R_kwota << "\t";
		cout << glowaogon.Glowa->M_kwota << "\t" << endl;
		glowaogon.Glowa = glowaogon.Glowa->nastepny;
	}
}
void wyswietl_uzytkownika(GlOg glowaogon, string uzytkownik, int ilosc_dni)
{
	GlOg glowaogon_tmp = glowaogon;
	int licznik_Lp = 0;
	int wybor = 0;
	if (uzytkownik == "Rafal")
		wybor = 1;
	if (uzytkownik == "Mateusz")
		wybor = 2;
	switch (wybor)
	{
	case 1:
		cout << "Wydatki od " << uzytkownik << endl;
		cout << "L.p.\tArtykul\tKwota" << endl;
		while (glowaogon.Glowa != NULL)
		{
			if (glowaogon.Glowa->R_kwota != 0)
			{
				licznik_Lp++;
				cout << licznik_Lp << "\t";
				cout << glowaogon.Glowa->nazwa << "\t";
				cout << glowaogon.Glowa->R_kwota << "\t" << endl;
			}
			glowaogon.Glowa = glowaogon.Glowa->nastepny;
		}
		cout << "" << endl;
		Rafal_statystyki(glowaogon_tmp, ilosc_dni);
		cout << "" << endl;
		break;
	case 2:
		cout << "Wydatki od " << uzytkownik << endl;
		cout << "L.p.\tArtykul\tKwota" << endl;
		while (glowaogon.Glowa != NULL)
		{
			if (glowaogon.Glowa->M_kwota != 0)
			{
				licznik_Lp++;
				cout << licznik_Lp << "\t";
				cout << glowaogon.Glowa->nazwa << "\t";
				cout << glowaogon.Glowa->M_kwota << "\t" << endl;
			}
			glowaogon.Glowa = glowaogon.Glowa->nastepny;
		}
		cout << "" << endl;
		Mateusz_statystyki(glowaogon_tmp, ilosc_dni);
		cout << "" << endl;
		break;
	default:
		cout << "Brak uzytkownika: " << uzytkownik << " w bazie danych" << endl;
		break;
	}
}
void wyswietl_rekord(Wezel wezel)
{
	cout << "L.p.\tArtykul\tRafal\tMateusz\t" << endl;
	cout << wezel.Lp << "\t";
	cout << wezel.nazwa << "\t";
	cout << wezel.R_kwota << "\t";
	cout << wezel.M_kwota << "\t" << endl;
}
Wezel* wyszukaj_rekord(GlOg glowaogon, int szukane_Lp)
{
	Wezel* szukana = NULL;
	while (glowaogon.Glowa != NULL)
	{
		if (glowaogon.Glowa->Lp == szukane_Lp)
		{
			szukana = glowaogon.Glowa;
			break;
		}
		else
			glowaogon.Glowa = glowaogon.Glowa->nastepny;
	}
	return szukana;
}
void dekrementacja_Lp(Wezel* dekr)
{
	while (dekr != NULL)
	{
		dekr->Lp--;
		dekr = dekr->nastepny;
	}
}
void zaokraglenie_do_2_po_przecinku(double&liczba)
{
	int tmp;
	liczba = liczba * 100;
	tmp = liczba;
	ceil(tmp);
	liczba = tmp;
	liczba = liczba / 100;
}
void suma_wydatkow(GlOg glowaogon, double&R_suma, double&M_suma)
{
	R_suma = M_suma = 0;
	while (glowaogon.Glowa != NULL)
	{
		R_suma = R_suma + glowaogon.Glowa->R_kwota;
		M_suma = M_suma + glowaogon.Glowa->M_kwota;
		glowaogon.Glowa = glowaogon.Glowa->nastepny;
	}
}
int Rafal_ilosc(GlOg glowaogon)
{
	int ilosc = 0;
	while (glowaogon.Glowa != NULL)
	{
		if (glowaogon.Glowa->R_kwota != 0)
			ilosc++;
		glowaogon.Glowa = glowaogon.Glowa->nastepny;
	}
	return ilosc;
}
int Mateusz_ilosc(GlOg glowaogon)
{
	int ilosc = 0;
	while (glowaogon.Glowa != NULL)
	{
		if (glowaogon.Glowa->M_kwota != 0)
			ilosc++;
		glowaogon.Glowa = glowaogon.Glowa->nastepny;
	}
	return ilosc;
}
void maximum(GlOg glowaogon, Wezel*&R_max, Wezel*&M_max)
{
	R_max = M_max = NULL;
	if (glowaogon.Glowa != NULL)
	{
		R_max = glowaogon.Glowa;
		M_max = glowaogon.Glowa;
		while (glowaogon.Glowa != NULL)
		{
			if (glowaogon.Glowa->R_kwota > R_max->R_kwota)
				R_max = glowaogon.Glowa;
			if (glowaogon.Glowa->M_kwota > M_max->M_kwota)
				M_max = glowaogon.Glowa;
			glowaogon.Glowa = glowaogon.Glowa->nastepny;
		}
	}
}
void minimum(GlOg glowaogon, Wezel*&R_min, Wezel*&M_min)
{
	R_min = M_min = NULL;
	GlOg tmp = glowaogon;
	GlOg tmp2 = glowaogon;
	if (glowaogon.Glowa != NULL)
	{
		while (tmp.Glowa != NULL)
		{
			if (tmp.Glowa->R_kwota != 0)
			{
				R_min = tmp.Glowa;
				break;
			}
			else
				tmp.Glowa = tmp.Glowa->nastepny;
		}
		while (tmp2.Glowa != NULL)
		{
			if (tmp2.Glowa->M_kwota != 0)
			{
				M_min = tmp2.Glowa;
				break;
			}
			else
				tmp2.Glowa = tmp2.Glowa->nastepny;
		}
		while (glowaogon.Glowa != NULL)
		{
			if ((glowaogon.Glowa->R_kwota < R_min->R_kwota) && (glowaogon.Glowa->R_kwota > 0))
				R_min = glowaogon.Glowa;
			if ((glowaogon.Glowa->M_kwota < M_min->M_kwota) && (glowaogon.Glowa->M_kwota > 0))
				M_min = glowaogon.Glowa;
			glowaogon.Glowa = glowaogon.Glowa->nastepny;
		}
	}
}
void statystki_ogolne(GlOg glowaogon, int ilosc_dni)
{
	cout << "" << endl;
	Rafal_statystyki(glowaogon, ilosc_dni);
	cout << "" << endl;
	Mateusz_statystyki(glowaogon, ilosc_dni);
	cout << "" << endl;
}
void Rafal_statystyki(GlOg glowaogon, int ilosc_dni)
{
	double R_wydatki, M_wydatki, R_sredniaD, R_srednia;
	int licznik;
	Wezel *R_maximum, *M_maximum, *R_minimum, *M_minimum;
	suma_wydatkow(glowaogon, R_wydatki, M_wydatki);
	maximum(glowaogon, R_maximum, M_maximum);
	minimum(glowaogon, R_minimum, M_minimum);
	licznik = Rafal_ilosc(glowaogon);
	R_sredniaD = R_wydatki / ilosc_dni;
	R_srednia = R_wydatki / licznik;
	zaokraglenie_do_2_po_przecinku(R_sredniaD);
	zaokraglenie_do_2_po_przecinku(R_srednia);
	cout << "Statystyki RAFAL:" << endl;
	cout << "SUMA: " << R_wydatki << " zl" << endl;
	cout << "SREDNIA na dzien: " << R_sredniaD << " zl" << endl;
	cout << "SREDNI wydatek: " << R_srednia << " zl" << endl;
	cout << "Najwiekszy wydatek: " << R_maximum->R_kwota << " zl" << " (" << R_maximum->nazwa << ")" << endl;
	cout << "Najmniejszy wydatek: " << R_minimum->R_kwota << " zl" << " (" << R_minimum->nazwa << ")" << endl;
}
void Mateusz_statystyki(GlOg glowaogon, int ilosc_dni)
{
	double R_wydatki, M_wydatki, M_sredniaD, M_srednia;
	int licznik;
	Wezel *R_maximum, *M_maximum, *R_minimum, *M_minimum;
	suma_wydatkow(glowaogon, R_wydatki, M_wydatki);
	maximum(glowaogon, R_maximum, M_maximum);
	minimum(glowaogon, R_minimum, M_minimum);
	licznik = Mateusz_ilosc(glowaogon);
	M_sredniaD = M_wydatki / ilosc_dni;
	M_srednia = M_wydatki / licznik;
	zaokraglenie_do_2_po_przecinku(M_sredniaD);
	zaokraglenie_do_2_po_przecinku(M_srednia);
	cout << "Statystyki MATEUSZ:" << endl;
	cout << "SUMA: " << M_wydatki << " zl" << endl;
	cout << "SREDNIA na dzien: " << M_sredniaD << " zl" << endl;
	cout << "SREDNI wydatek: " << M_srednia << " zl" << endl;
	cout << "Najwiekszy wydatek: " << M_maximum->M_kwota << " zl" << " (" << M_maximum->nazwa << ")" << endl;
	cout << "Najmniejszy wydatek: " << M_minimum->M_kwota << " zl" << " (" << M_minimum->nazwa << ")" << endl;
}
void edytuj_rekord(GlOg glowaogon, int edytowane_Lp)
{
	Wezel* tmp;
	tmp = wyszukaj_rekord(glowaogon, edytowane_Lp);
	if (tmp == NULL)
		cout << "Brak rekordu w bazie danych" << endl;
	else
	{
		system("cls");
		cout << "Edytujesz nastepujacy rekord" << endl;
		wyswietl_rekord(*tmp);
		cout << "Podaj nowe dane" << endl;
		cout << "Nazwa artykulu: ";
		cin >> tmp->nazwa;
		cout << "Rafal: ";
		cin >> tmp->R_kwota;
		cout << "Mateusz: ";
		cin >> tmp->M_kwota;
		system("cls");
		cout << "Rekord po zmianach" << endl;
		wyswietl_rekord(*tmp);
	}
}
void usun_rekord(GlOg&glowaogon, int usuwane_Lp)
{
	string wybor;
	Wezel* tmp;
	GlOg poprzedni = glowaogon;
	tmp = wyszukaj_rekord(glowaogon, usuwane_Lp);
	if (tmp == NULL)
		cout << "Brak rekordu w bazie danych" << endl;
	else
	{
		system("cls");
		cout << "Czy chcesz usunac nastepujacy rekord? Wybierz T/N i zatwierdz klawiszem 'Enter'" << endl;
		wyswietl_rekord(*tmp);
		cin >> wybor;
		if (wybor == "T")
		{
			if (glowaogon.Glowa->Lp == usuwane_Lp)
			{
				glowaogon.Glowa = glowaogon.Glowa->nastepny;
				delete tmp;
				dekrementacja_Lp(glowaogon.Glowa);
			}
			else
			{
				if (glowaogon.Ogon->Lp == usuwane_Lp)
				{
					while (poprzedni.Glowa->nastepny->nastepny != NULL)
						poprzedni.Glowa = poprzedni.Glowa->nastepny;
					glowaogon.Ogon = poprzedni.Glowa;
					glowaogon.Ogon->nastepny = NULL;
					delete tmp;
				}
				else
				{
					while (poprzedni.Glowa != NULL)
					{
						if (poprzedni.Glowa->nastepny->Lp == usuwane_Lp)
						{
							poprzedni.Glowa->nastepny = poprzedni.Glowa->nastepny->nastepny;
							dekrementacja_Lp(poprzedni.Glowa->nastepny);
							delete tmp;
							break;
						}
						else
							poprzedni.Glowa = poprzedni.Glowa->nastepny;
					}
				}
			}
			glowaogon.Aktualny_licznik--;
			cout << "USUNIETO" << endl;
		}
		else
			cout << "Rekord nie zostal usuniety" << endl;
	}
}
void zapisz_do_pliku(GlOg glowaogon, string nazwa)
{
	int ilosc;
	ofstream zapis;
	zapis.open(nazwa);
	if (!zapis.is_open())
		cout << "Blad otwarcia do zapisu" << endl;
	else
	{
		ilosc = glowaogon.Aktualny_licznik;
		zapis << ilosc << endl;
		while (glowaogon.Glowa != NULL)
		{
			zapis << glowaogon.Glowa->nazwa << endl;
			zapis << glowaogon.Glowa->R_kwota << endl;
			zapis << glowaogon.Glowa->M_kwota << endl;
			glowaogon.Glowa = glowaogon.Glowa->nastepny;
		}
		zapis.close();
	}
}
void odczyt_z_pliku(GlOg&glowaogon, string nazwa)
{
	int ilosc;
	Wezel tmp;
	ifstream odczyt;
	odczyt.open(nazwa);
	if (!odczyt.is_open())
		cout << "Blad otwarcia do odczytu" << endl;
	else
	{
		odczyt >> ilosc;
		for (int i = 0; i < ilosc; i++)
		{
			odczyt >> tmp.nazwa;
			odczyt >> tmp.R_kwota;
			odczyt >> tmp.M_kwota;
			wstaw_element(glowaogon, tmp.nazwa, tmp.R_kwota, tmp.M_kwota);
		}
		odczyt.close();
	}
}
int main()
{
	int wybor, Lp;
	double cena1, cena2;
	int wybor2, ilosc_dni;
	string nazwa, uzytkownik, nazwa_pliku, pelna_nazwa_pliku, rozszerzenie;
	GlOg glowa_ogon;
	glowa_ogon.Glowa = NULL;
	glowa_ogon.Ogon = NULL;
	glowa_ogon.Aktualny_licznik = 0;
	rozszerzenie = ".txt";
	odczyt_z_pliku(glowa_ogon, "dane.txt");
	poczatek:while (1)
	{
		system("cls");
		MENU();
		wybor = _getch();
		switch (wybor)
		{
		case 49:
			system("cls");
			cout << "Aby cofnac wprowadz nazwe artykulu jako 'cofnij' i zatwierdz klawiszem 'Enter'" << endl;
			cout << "Nazwa artykulu: ";;
			cin >> nazwa;
			if (nazwa == "cofnij")
				goto poczatek;
			cout << "Rafal: ";
			cin >> cena1;
			cout << "Mateusz: ";
			cin >> cena2;
			wstaw_element(glowa_ogon, nazwa, cena1, cena2);
			system("cls");
			cout << "Dodano rekord:" << endl;
			wyswietl_rekord(*glowa_ogon.Ogon);
			cout << "Nacisnij dowolny klawisz by przejsc dalej";
			_getch();
			break;
		case 50:
			system("cls");
			cout << "Podaj ilosc dni i zatwierdz klawiszem 'Enter'" << endl;
			cin >> ilosc_dni;
			system("cls");
			komunikat();
			wybor2 = _getch();
			switch (wybor2)
			{
			case 49:
				system("cls");
				wyswietl_calosc(glowa_ogon);
				statystki_ogolne(glowa_ogon, ilosc_dni);
				cout << "Nacisnij dowolny klawisz by przejsc dalej";
				_getch();
				goto poczatek;
			case 50:
				system("cls");
				cout << "Podaj imie osoby do wyswietlenia (Rafal/Mateusz) i zatwierdz klawiszem 'Enter'" << endl;
				cout << "Aby cofnac wprowadz imie jako 'cofnij'" << endl;
				cin >> uzytkownik;
				if (uzytkownik == "cofnij")
					goto poczatek;
				system("cls");
				wyswietl_uzytkownika(glowa_ogon, uzytkownik, ilosc_dni);
				cout << "Nacisnij dowolny klawisz by przejsc dalej";
				_getch();
				goto poczatek;
			default:
				goto poczatek;
			break;
			}
		case 51:
			system("cls");
			wyswietl_calosc(glowa_ogon);
			cout << "Podaj Lp rekordu, ktrory chcesz edytowac i zatwierdz klawiszem 'Enter'" << endl;
			cout << "Jezeli chcesz cofnac podaj Lp rekordu, ktory nie istnieje i zatwierdz klawiszem 'Enter'" << endl;
			cin >> Lp;
			edytuj_rekord(glowa_ogon, Lp);
			cout << "Nacisnij dowolny klawisz by przejsc dalej";
			_getch();
			break;
		case 52:
			system("cls");
			wyswietl_calosc(glowa_ogon);
			cout << "Podaj Lp rekordu, ktrory chcesz usunac i zatwierdz klawiszem 'Enter'" << endl;
			cout << "Jezeli chcesz cofnac podaj Lp rekordu, ktory nie istnieje i zatwierdz klawiszem 'Enter'" << endl;
			cin >> Lp;
			usun_rekord(glowa_ogon, Lp);
			cout << "Nacisnij dowolny klawisz by przejsc dalej";
			_getch();
			break;
		case 53:
			system("cls");
			cout << "Podaj nazwe pliku do zapisu i zatwierdz klawiszem 'Enter'" << endl;
			cout << "Aby cofnac wprowadz nazwe pliku jako 'cofnij'" << endl;
			cin >> nazwa_pliku;
			if (nazwa_pliku == "cofnij")
				goto poczatek;
			pelna_nazwa_pliku = nazwa_pliku + rozszerzenie;
			zapisz_do_pliku(glowa_ogon, pelna_nazwa_pliku);
			cout << "Pomyslnie zapisano baze danych do pliku: " << pelna_nazwa_pliku << endl;
			cout << "Nacisnij dowolny klawisz by przejsc dalej";
			_getch();
			break;
		case 54:
			system("cls");
			cout << "Podaj nazwe pliku do wczytania i zatwierdz klawiszem 'Enter'" << endl;
			cout << "Aby cofnac wprowadz nazwe pliku jako 'cofnij'" << endl;
			cin >> nazwa_pliku;
			if (nazwa_pliku == "cofnij")
				goto poczatek;
			pelna_nazwa_pliku = nazwa_pliku + rozszerzenie;
			czysc_pamiec(glowa_ogon);
			glowa_ogon.Aktualny_licznik = 0;
			odczyt_z_pliku(glowa_ogon, pelna_nazwa_pliku);
			cout << "Pomyslnie wczytano baze danych z pliku: " << pelna_nazwa_pliku << endl;
			cout << "Nacisnij dowolny klawisz by przejsc dalej";
			_getch();
			break;
		case 55:
			zapisz_do_pliku(glowa_ogon, "dane.txt");
			czysc_pamiec(glowa_ogon);
			exit(0);
		}
	}
	system("Pause");
	return 0;
}