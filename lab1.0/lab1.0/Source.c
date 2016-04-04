#include <stdio.h>
#include <math.h>
float procent_skladany(float kwota, float roczna_stopa, int kapitalizacja, int lata)
{
	float wynik_koncowy;
	wynik_koncowy = kwota*(powf(1 + (roczna_stopa / kapitalizacja), (kapitalizacja*lata)));
	return wynik_koncowy;
}
void wyswietl_ps()
{
	float wynik_koncowy, kwota, roczna_stopa;
	int dokladnosc, kapitalizacja, lata, znak;
	char imie[100];
	int a, b, c, d, e; //zmienne s³u¿ace do zabezpieczenia wczytywania
	printf("Podaj kwote\n");
	a = scanf_s("%f", &kwota);
	while (a != 1) //sprawdzenie czy zamiast liczby nie wprowadzono znaku
	{
		printf("Kwota musi byc liczba, podaj ponownie!\n");
		while ((znak = getchar()) != '\n' && znak != EOF); //czyszczenie bufora
		a = scanf_s("%f", &kwota);
	}
	while ((znak = getchar()) != '\n' && znak != EOF); //dodatkowe czyszczenie bufora
	printf("Podaj roczna stope\n");
	b = scanf_s("%f", &roczna_stopa);
	while (b != 1) //sprawdzenie czy zamiast liczby nie wprowadzono znaku
	{
		printf("Roczna stopa musi byc liczba, podaj ponownie!\n");
		while ((znak = getchar()) != '\n' && znak != EOF); //czyszczenie bufora
		b = scanf_s("%f", &roczna_stopa);
	}
	while ((znak = getchar()) != '\n' && znak != EOF); //dodatkowe czyszczenie bufora
	printf("Podaj kapitalizacje\n");
	c = scanf_s("%d", &kapitalizacja);
	while (c != 1) //sprawdzenie czy zamiast liczby nie wprowadzono znaku
	{
		printf("Kapitalizacja musi byc liczba, podaj ponownie!\n");
		while ((znak = getchar()) != '\n' && znak != EOF); //czyszczenie bufora
		c = scanf_s("%d", &kapitalizacja);
	}
	while ((znak = getchar()) != '\n' && znak != EOF); //dodatkowe czyszczenie bufora
	printf("Podaj lata\n");
	d = scanf_s("%d", &lata);
	while (d != 1) //sprawdzenie czy zamiast liczby nie wprowadzono znaku
	{
		printf("Lata musza byc liczba, podaj ponownie!\n");
		while ((znak = getchar()) != '\n' && znak != EOF); //czyszczenie bufora
		d = scanf_s("%d", &lata);
	}
	while ((znak = getchar()) != '\n' && znak != EOF); //dodatkowe czyszczenie bufora
	printf("Podaj imie\n");
	scanf_s("%s", imie, 50);
	if (roczna_stopa < 0) //sprawdzenie poprawnoœci stopy procentowej
	{
		printf("Roczna stopa nie moze byc ujemna!\n");
	}
	else
		if ((kwota<0) || (kapitalizacja <= 0) || (lata <= 0)) //sprawdzenie poprawnoœci pozosta³ych danych
		{
			printf("Bledne dane wejsciowe\n");
		}
		else
		{
			printf("Podaj dokladnosc\n");
			e = scanf_s("%d", &dokladnosc);
			while (e != 1) //sprawdzenie czy zamiast liczby nie wprowadzono znaku
			{
				printf("Dokladnosc musi byc liczba, podaj ponownie!\n");
				while ((znak = getchar()) != '\n' && znak != EOF); //czyszczenie bufora
				e = scanf_s("%d", &dokladnosc);
			}
			while ((znak = getchar()) != '\n' && znak != EOF); //dodatkowe czyszczenie bufora
			wynik_koncowy = procent_skladany(kwota, roczna_stopa, kapitalizacja, lata);
			printf("nazwa uzytkownika: %s\n", imie, 50);
			printf("Wynik wynosi: %.*f\n", dokladnosc, wynik_koncowy); //wyœwietlenie wyniku
		}
}
int main()
{
	wyswietl_ps();
	system("Pause");
	return 0;
}