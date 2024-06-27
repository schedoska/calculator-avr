#ifndef KALKULATOR_H_
#define KALKULATOR_H_

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>

#define BOOL uint8_t
#define TRUE 1
#define FALSE 0

#define OPERACJA_DZIELENIE 11
#define OPERACJA_MNOZENIE 12
#define OPERACJA_ODEJMOWANIE 13
#define OPERACJA_DODAWANIE 14
#define OPERACJA_ROWNASIE 15
#define OPERACJA_CLEAR 16

int8_t isCyfra(int KeyPad_numer);
int8_t isOperacja(int KeyPad_numer);

char ZnakOperacji(uint8_t Operacja_code);
long WykonajOperacje(long A, long B, uint8_t Operacja);
uint8_t digit_count(long Liczba);

#endif
