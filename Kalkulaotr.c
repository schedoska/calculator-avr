#include "Kalkulator.h"

int8_t KeyPadSlownik[] =
		{7,8,9,OPERACJA_DZIELENIE,
		4,5,6,OPERACJA_MNOZENIE,
		1,2,3,OPERACJA_ODEJMOWANIE,
		0,OPERACJA_CLEAR,OPERACJA_ROWNASIE,OPERACJA_DODAWANIE};

int8_t isCyfra(int KeyPad_numer)
{
	if(KeyPad_numer < 1 || KeyPad_numer > 16) return -1;
	uint8_t KeyTranslated = KeyPadSlownik[KeyPad_numer-1];
	if(KeyTranslated > 9) return -1;
	return KeyTranslated;
}

int8_t isOperacja(int KeyPad_numer)
{
	if(KeyPad_numer < 1 || KeyPad_numer > 16) return -1;
	uint8_t KeyTranslated = KeyPadSlownik[KeyPad_numer - 1];
	if(KeyTranslated < 10) return -1;
	return KeyTranslated;
}

char ZnakOperacji(uint8_t Operacja_code)
{
	switch(Operacja_code)
	{
	case OPERACJA_ROWNASIE:
		return ' ';
	case OPERACJA_DODAWANIE:
		return '+';
	case OPERACJA_DZIELENIE:
		return ':';
	case OPERACJA_MNOZENIE:
		return 'x';
	case OPERACJA_ODEJMOWANIE:
		return '-';
	case OPERACJA_CLEAR:
		return 'C';
	}
	return 'E';
}

long WykonajOperacje(long A, long B, uint8_t Operacja)
{
	switch(Operacja)
	{
	case OPERACJA_ROWNASIE:
		return A;
	case OPERACJA_DODAWANIE:
		return A + B;
	case OPERACJA_DZIELENIE:
		if(A == 0) return 0;
		return B / A;
	case OPERACJA_MNOZENIE:
		return B * A;
	case OPERACJA_ODEJMOWANIE:
		return B - A;
	default:
		return A;
	}
}

uint8_t digit_count(long Liczba)
{
	uint8_t answer = 0;
	if(Liczba < 0) answer++;
	if(Liczba == 0) return 1;
	while(Liczba != 0)
	{
		Liczba /= 10;
		answer++;
	}
	return answer;
}


