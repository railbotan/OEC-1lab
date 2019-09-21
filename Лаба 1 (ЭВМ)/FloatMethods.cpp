#include "pch.h"
#include <iostream>
#include <bitset>
#include <limits>
#include "À‡·‡ 1 (›¬Ã).h"

using namespace std;

int GetTrueLenght(bool* value, int lenght)
{
	for (int i = 0; i < FLOAT_LENGHT; i++)
	{
		lenght--;
		if (value[i])
			break;
	}
	return lenght;
}

bool* IntegerPartToBinary(float value, int lenght)
{
	bool* result = new bool[lenght];
	float temp = value;
	for (int i = lenght - 1; i >= 0; i--)
	{
		result[i] = remainder(temp, 2);
		temp = trunc(temp / 2);
	}
	return result;
}

bool* ParseFraction(float fract)
{
	bool* result = new bool[FLOAT_LENGHT];
	for (int i = 0; i < FLOAT_LENGHT; i++)
	{
		float intenger;
		fract = modf(fract * 2, &intenger);
		result[i] = (int)intenger;
	}
	return result;
}

bool* FloatToBinary(float value)
{
	float x, y;
	int characteristic;
	y = modf(abs(value), &x);
	bool* intenger = IntegerPartToBinary(x, FLOAT_LENGHT);
	int intengerLenght = GetTrueLenght(intenger, FLOAT_LENGHT);
	bool* fraction = ParseFraction(y);
	int fractLenght = GetTrueLenght(fraction, FLOAT_LENGHT);
	if (x > 0)
	{
		characteristic = 127 + intengerLenght;
	}
	else
	{
		characteristic = fractLenght - 1;
	}
	bool* characteristicBolean = IntegerPartToBinary(characteristic, 8);
	bool* result = new bool[32];
	result[0] = value < 0;
	for (int i = 1; i < 9; i++)
	{
		result[i] = characteristicBolean[i - 1];
	}
	bool* number = new bool[2 * FLOAT_LENGHT];
	memcpy(number, intenger, FLOAT_LENGHT * sizeof(bool));
	memcpy(number + FLOAT_LENGHT, fraction, FLOAT_LENGHT * sizeof(bool));
	int startPosition = x > 0
		? FLOAT_LENGHT - intengerLenght
		: fractLenght > 23 
			? 2 * FLOAT_LENGHT - fractLenght
			: 2 * FLOAT_LENGHT - 23;
	for (int i = 9; i < 32; i++)
	{
		result[i] = number[i - 9 + startPosition];
	}
	return result;
}