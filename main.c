#include "HD44780.h"
#include "getkey.h"
#include "Kalkulator.h"

#define SCREEN_SIZE 16
#define TICK_RATE_MS 200

long Rejestr_A = 0;
long Rejestr_B = 0;

BOOL is_B_empty = TRUE;
uint8_t A_digitCount = 0;

BOOL dodajeCyfre = TRUE;
uint8_t Aktualna_Operacja = OPERACJA_ROWNASIE;

BOOL ScreenNeedsUpdate = TRUE;

void ProceedCyfra(int8_t cyfra);
void ProceedOperacja(int8_t operacja);
void ScreenUpdate();

int main()
{
	LCD_Initalize();
	KeyPad_init();

	while(1)
	{
		int8_t KeyPressed = getchar16_debounced();

		if(isCyfra(KeyPressed) != -1)
		{
			ProceedCyfra(isCyfra(KeyPressed));
		}
		else if(isOperacja(KeyPressed) != -1)
		{
			ProceedOperacja(isOperacja(KeyPressed));
		}

		if(ScreenNeedsUpdate) ScreenUpdate();
		_delay_ms(TICK_RATE_MS);
	}
}

void ProceedCyfra(int8_t cyfra)
{
	if(dodajeCyfre)
	{
		Rejestr_A = Rejestr_A * 10 + cyfra;
		A_digitCount++;
	}
	else
	{
		Rejestr_B = Rejestr_A;
		is_B_empty = FALSE;
		Rejestr_A = cyfra;
		A_digitCount = 1;
		dodajeCyfre = TRUE;
	}
	ScreenNeedsUpdate = TRUE;
}

void ProceedOperacja(int8_t operacja)
{
	ScreenNeedsUpdate = TRUE;
	if(operacja == OPERACJA_ROWNASIE && !is_B_empty)
	{
		Rejestr_A = WykonajOperacje(Rejestr_A, Rejestr_B, Aktualna_Operacja);
		A_digitCount = digit_count(Rejestr_A);
		is_B_empty = TRUE;
	}
	else if(operacja == OPERACJA_CLEAR)
	{
		Rejestr_A = 0;
		A_digitCount = 0;
		is_B_empty = TRUE;
		dodajeCyfre = TRUE;
		Aktualna_Operacja = OPERACJA_ROWNASIE;
		return;
	}
	Aktualna_Operacja = operacja;
	dodajeCyfre = FALSE;
}

void ScreenUpdate()
{
	LCD_Clear();
	char bufor[16];
	sprintf(bufor, "%ld" , Rejestr_A);

	uint8_t sign_frame = 1;
	if(Aktualna_Operacja != OPERACJA_ROWNASIE) sign_frame = 3;

	if(sign_frame == 3) LCD_WriteData('[');
	LCD_WriteData(ZnakOperacji(Aktualna_Operacja));
	if(sign_frame == 3) LCD_WriteData(']');

	for(int q = 0; q < SCREEN_SIZE - A_digitCount - sign_frame; q++)
	{
		LCD_WriteData(' ');
	}
	LCD_WriteText(bufor);
	ScreenNeedsUpdate = FALSE;
}



