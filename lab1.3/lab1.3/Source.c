#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void zamiana_bajtow(unsigned int liczba, char ciag[])
{
	int l_przed_zmiana[32] = { 0 };
	int l_po_zmianie[32] = { 0 };
	int licznik = 31; //licznik s³u¿¹cy do zapisani liczby w sposób binarny w tablicy
	int i, wyswietlanie, wysw_wartosci, bit = 31;
	int l_zmiany = 0; //aktualnie przenoszony bit
	int dodatkowy_licznik = 0; //licznik s³u¿¹cy do przechodzenia miêdzy elementami ci¹gu znakowego
	unsigned int n_liczba_dziesietna = 0;
	while (liczba != 0)
	{
		l_przed_zmiana[licznik] = liczba % 2;
		liczba = liczba / 2;
		licznik--; //zamiana liczby na binarn¹ i zapisanie jej w tablicy
	}
	for (i = 3; i >= 0; i--)
	{
		if (ciag[dodatkowy_licznik] == '4')
		{
			while (l_zmiany < 8) //ustawienie n-tego bajtu na pozycji czwartej
			{
				l_po_zmianie[l_zmiany] = l_przed_zmiana[(8 * i) + l_zmiany];
				l_zmiany++;
			}
			l_zmiany = 0;
		}
		if (ciag[dodatkowy_licznik] == '3') //ustawienie n-tego bajtu na pozycji trzeciej
		{
			while (l_zmiany < 8)
			{
				l_po_zmianie[8 + l_zmiany] = l_przed_zmiana[(8 * i) + l_zmiany];
				l_zmiany++;
			}
			l_zmiany = 0;
		}
		if (ciag[dodatkowy_licznik] == '2') //ustawienie n-tego bajtu na pozycji drugiej
		{
			while (l_zmiany < 8)
			{
				l_po_zmianie[16 + l_zmiany] = l_przed_zmiana[(8 * i) + l_zmiany];
				l_zmiany++;
			}
			l_zmiany = 0;
		}
		if (ciag[dodatkowy_licznik] == '1') //ustawienie n-tego bajtu na pozycji pierwszej
		{
			while (l_zmiany < 8)
			{
				l_po_zmianie[24 + l_zmiany] = l_przed_zmiana[(8 * i) + l_zmiany];
				l_zmiany++;
			}
			l_zmiany = 0;
		}
		dodatkowy_licznik++;
	}
	printf("Liczba przed zmiana: "); //+pêtle - wyœwietlenie liczby przed zmian¹ binarnie
	for (wyswietlanie = 0; wyswietlanie < 8; wyswietlanie++)
		printf("%d", l_przed_zmiana[wyswietlanie]);
	printf(" ");
	for (wyswietlanie = 8; wyswietlanie < 16; wyswietlanie++)
		printf("%d", l_przed_zmiana[wyswietlanie]);
	printf(" ");
	for (wyswietlanie = 16; wyswietlanie < 24; wyswietlanie++)
		printf("%d", l_przed_zmiana[wyswietlanie]);
	printf(" ");
	for (wyswietlanie = 24; wyswietlanie < 32; wyswietlanie++)
		printf("%d", l_przed_zmiana[wyswietlanie]);
	printf("\n");
	printf("Liczba po zmianie:   "); //+pêtle - wyœwietlenie liczby po zmianie binarnie
	for (wyswietlanie = 0; wyswietlanie < 8; wyswietlanie++)
		printf("%d", l_po_zmianie[wyswietlanie]);
	printf(" ");
	for (wyswietlanie = 8; wyswietlanie < 16; wyswietlanie++)
		printf("%d", l_po_zmianie[wyswietlanie]);
	printf(" ");
	for (wyswietlanie = 16; wyswietlanie < 24; wyswietlanie++)
		printf("%d", l_po_zmianie[wyswietlanie]);
	printf(" ");
	for (wyswietlanie = 24; wyswietlanie < 32; wyswietlanie++)
		printf("%d", l_po_zmianie[wyswietlanie]);
	printf("\n");
	for (wysw_wartosci = 0; wysw_wartosci < 32; wysw_wartosci++)
	{
		n_liczba_dziesietna = n_liczba_dziesietna + l_po_zmianie[wysw_wartosci] * pow(2, bit);
		bit--;
	}
	printf("Liczba ta w zapisie dziesietnym: %u\n", n_liczba_dziesietna); //wyœwietlenie nowej wartoœci zmienionej liczby
}
int main(void)
{
	unsigned int liczba;
	char ciag[5];
	printf("Podaj liczbe\n");
	scanf_s("%u", &liczba);
	printf("Podaj nowa kolejnosc bajtow\n");
	scanf_s("%s", ciag, 5);
	zamiana_bajtow(liczba, ciag);
	system("Pause");
	return 0;
}