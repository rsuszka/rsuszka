#include <stdio.h>
typedef union Rejestr_
{
	unsigned char bajty[4];
	unsigned short int slowa[2]; //16 bitowe
	unsigned int rejestr; //32 bitowy rejestr

} Rejestr;
void przesuniecie_16bit_lewo_cyklicznie(Rejestr* liczba_wsk)
{
	int i, j, k, licznik; //liczniki pêtl
	unsigned char tab_pom[4];
	for (i = 0; i < 4; i++)
		tab_pom[i] = liczba_wsk->bajty[i]; //utworzenie tablicy pomocniczej
	for (j = 0; j < 4; j++)
	{
		if (j < 2)
			licznik = j + 2;
		else
			licznik = j - 2;
		liczba_wsk->bajty[licznik] = tab_pom[j]; //podmiana odpowiednich elementów
	}
	printf("przesuniecie o 16bit w lewo cyklicznie. ");
	printf("Wartosci kolejnych bajtow dziesietnie (od najstarszego): ");
	for (k = 0; k < 4; k++)
	{
		printf("%d ", liczba_wsk->bajty[k]);
	}
	printf("\n");

}
void przesuniecie_8bit_lewo_cyklicznie(Rejestr* liczba_wsk)
{
	int i, j, k, licznik; //liczniki pêtl
	unsigned char tab_pom[4];
	for (i = 0; i < 4; i++)
		tab_pom[i] = liczba_wsk->bajty[i]; //utworzenie tablicy pomocniczej
	for (j = 0; j < 4; j++)
	{
		if (j > 0)
			licznik = j - 1;
		else
			licznik = j + 3;
		liczba_wsk->bajty[licznik] = tab_pom[j]; //podmiana odpowiednich elementów
	}
	printf("przesuniecie o 8bit w lewo cyklicznie. ");
	printf("Wartosci kolejnych bajtow dziesietnie (od najstarszego): ");
	for (k = 0; k < 4; k++)
	{
		printf("%d ", liczba_wsk->bajty[k]);
	}
	printf("\n");
}
void przesuniecie_8bit_prawo_cyklicznie(Rejestr* liczba_wsk)
{
	int i, j, k, licznik; //liczniki pêtl
	unsigned char tab_pom[4];
	for (i = 0; i < 4; i++)
		tab_pom[i] = liczba_wsk->bajty[i]; //utworzenie tablicy pomocniczej
	for (j = 0; j < 4; j++)
	{
		if (j < 3)
			licznik = j + 1;
		else
			licznik = j - 3;
		liczba_wsk->bajty[licznik] = tab_pom[j]; //podmiana odpowiednich elementów
	}
	printf("przesuniecie o 8bit w prawo cyklicznie. ");
	printf("Wartosci kolejnych bajtow dziesietnie (od najstarszego): ");
	for (k = 0; k < 4; k++)
	{
		printf("%d ", liczba_wsk->bajty[k]);
	}
	printf("\n");
}
void przesuniecie_1bit_prawo(Rejestr* liczba_wsk)
{
	unsigned int liczba;
	liczba = liczba_wsk->rejestr;
	liczba = liczba >> 1;
	liczba_wsk->rejestr = liczba;
	printf("przesuniecie 1 bit w prawo: %d\n", liczba);
}
void przesuniecie_1bit_lewo(Rejestr* liczba_wsk)
{
	unsigned int liczba;
	liczba = liczba_wsk->rejestr;
	liczba = liczba << 1;
	liczba_wsk->rejestr = liczba;
	printf("przesuniecie 1 bit w lewo: %d\n", liczba);
}
void wyswietl_rejestr_hex(Rejestr* liczba_wsk)
{
	unsigned int liczba;
	liczba = liczba_wsk->rejestr;
	printf("rejestr w systemie szesnastkowym: %X\n", liczba);
}
void wyswietl_najmlodszybajt_rejestr_hex(Rejestr* liczba_wsk)
{
	unsigned int liczba;
	liczba = liczba_wsk->rejestr;
	liczba = liczba << 28; //przesuniêcie najm³odszego bajtu na najstarszy (na m³odszych pojawiaj¹ siê 0)
	liczba = liczba >> 28; //przesuniêcie najstarszego bajtu na najm³odszy (na starszych pojawiaj¹ siê 0)
	printf("najmlodszy bajt rejestru w systemie szesnastkowym: %X\n", liczba);
}
void wyswietl_starszeslowo_rejestr_hex(Rejestr* liczba_wsk)
{
	unsigned int liczba;
	liczba = liczba_wsk->rejestr;
	liczba = liczba >> 16; //przesuniêcie najstarszego s³owa na najm³odsze (na starszych pojawiaj¹ siê 0)
	printf("najstarsze slowo rejestru w systemie szesnastkowym: %X\n", liczba);
}
int main()
{
	int i;
	Rejestr liczba, liczba2;
	liczba.rejestr = 5000000;
	printf("Liczba=%d\n", liczba.rejestr);
	przesuniecie_1bit_lewo(&liczba);
	liczba.rejestr = 5000000;
	przesuniecie_1bit_prawo(&liczba);
	liczba.rejestr = 5000000;
	wyswietl_rejestr_hex(&liczba);
	wyswietl_najmlodszybajt_rejestr_hex(&liczba);
	wyswietl_starszeslowo_rejestr_hex(&liczba);
	liczba2.bajty[0] = 1;
	liczba2.bajty[1] = 0;
	liczba2.bajty[2] = 5;
	liczba2.bajty[3] = 15;
	printf("Kolejne bajty dziesietnie liczby2: ");
	for (i = 0; i < 4; i++)
		printf("%d ", liczba2.bajty[i]);
	printf("\n");
	przesuniecie_16bit_lewo_cyklicznie(&liczba2);
	liczba2.bajty[0] = 1;
	liczba2.bajty[1] = 0;
	liczba2.bajty[2] = 5;
	liczba2.bajty[3] = 15;
	przesuniecie_8bit_lewo_cyklicznie(&liczba2);
	liczba2.bajty[0] = 1;
	liczba2.bajty[1] = 0;
	liczba2.bajty[2] = 5;
	liczba2.bajty[3] = 15;
	przesuniecie_8bit_prawo_cyklicznie(&liczba2);
	system("Pause");
	return 0;
}