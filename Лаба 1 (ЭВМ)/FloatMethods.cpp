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
	if (value == 0)
	{
		characteristic = 0;
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

bool* SumExponent(bool * a, bool * b)
{
	bool* a_exponent = new bool[8];
	bool* b_exponent = new bool[8];
	for (int i = 0; i < 8; i++)
	{
		a_exponent[i] = a[i + 1];
		b_exponent[i] = b[i + 1];
	}
	bool* temp = SumInMultiplication(a_exponent, b_exponent, 8);
	bool* shift = new bool[8];
	for (int i = 1; i < 7; i++)
	{
		shift[i] = false;
	}
	shift[0] = true;
	shift[7] = true;
	return SumInMultiplication(temp, shift, 8);
}

bool * MultiplicationMantisses(bool * a, bool * b)
{
	bool* mantissa = new bool[48];
	for (int i = 0; i < 48; i++)
	{
		mantissa[i] = false;
		
	}

	bool* a_mantissa = new bool[24];
	bool* b_mantissa = new bool[24];
	a_mantissa[0] = 1;
	b_mantissa[0] = 1;
	for (int i = 1; i < 24; i++)
	{
		a_mantissa[i] = a[i + 8];
		b_mantissa[i] = b[i + 8];
	}

	for (int i = 0; i < 24; i++)
	{
		if (b_mantissa[i])
		{
			bool* temp = new bool[48];
			for (int k = 0; k < 48; k++)
			{
				temp[k] = false;
			}

			for (int j = 0; j < 24; j++)
			{
				temp[i + j + 1] = a_mantissa[j];
			}
			mantissa = SumInMultiplication(mantissa, temp, 48);
		}
	}
	return mantissa;
}

bool* MultiplicationFloat(bool* a, bool* b)
{
	bool* result = new bool[INT_LENGHT];
	result[0] = a[0] && b[0] ? false : a[0] || b[0];
	bool* result_exponent = SumExponent(a, b);
	bool* result_mantissa = MultiplicationMantisses(a, b);
	int start = 2;
	if (result_mantissa[0])
	{
		bool* shift = new bool[8];
		for (int i = 0; i < 7; i++)
		{
			shift[i] = false;
		}
		shift[7] = true;
		result_exponent = SumInMultiplication(result_exponent, shift, 8);
		start = 1;
	}
	for (int i = 0; i < 8; i++)
	{
		result[i + 1] = result_exponent[i];
	}
	for (int i = 9; i < INT_LENGHT; i++)
	{
		result[i] = result_mantissa[i - 9 + start];
	}
	return result;
}