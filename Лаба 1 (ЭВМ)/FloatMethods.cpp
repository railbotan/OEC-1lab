#include "pch.h"
#include <iostream>
#include <bitset>
#include <limits>
#include "À‡·‡ 1 (›¬Ã).h"

using namespace std;

int GetTrueLenght(bool* value, int lenght)
{
	for (int i = 0; i < FLOAT_LENGHT; i++) {
		lenght--;
		if (value[i]) break;
	}
	return lenght;
}

bool* IntegerPartToBinary(float value, int lenght)
{
	bool* result = new bool[lenght];
	float temp = value;
	for (int i = lenght - 1; i >= 0; i--) {
		result[i] = remainder(temp, 2);
		temp = trunc(temp / 2);
	}
	return result;
}

bool* ParseFraction(float fract)
{
	bool* result = new bool[FLOAT_LENGHT];
	for (int i = 0; i < FLOAT_LENGHT; i++) {
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
	if (x > 0) {
		characteristic = 127 + intengerLenght;
	} else {
		characteristic = fractLenght - 1;
	}
	if (value == 0) {
		characteristic = 0;
	}
	bool* characteristicBoolean = IntegerPartToBinary(characteristic, 8);
	bool* result = new bool[32];
	result[0] = value < 0;
	memcpy(result + 1, characteristicBoolean, 8 * sizeof(bool));
	bool* number = new bool[2 * FLOAT_LENGHT];
	memcpy(number, intenger, FLOAT_LENGHT * sizeof(bool));
	memcpy(number + FLOAT_LENGHT, fraction, FLOAT_LENGHT * sizeof(bool));
	int startPosition = x > 0
		? FLOAT_LENGHT - intengerLenght
		: fractLenght > 23 
			? 2 * FLOAT_LENGHT - fractLenght
			: 2 * FLOAT_LENGHT - 23;
	memcpy(result + 9, number + startPosition, 23 * sizeof(bool));
	return result;
}

void CompareFloats(bool * &a, bool * &b)
{
	for (int i = 1; i < INT_LENGHT; i++) {
		if (a[i] != b[i] && a[i]) break;
		if (a[i] != b[i] && b[i]) {
			bool* temp = a;
			a = b;
			b = temp;
			break;
		}
	}
}

int GetShift(bool * a, bool * b)
{
	bool* a_exponent = new bool[8];
	bool* b_exponent = new bool[8];
	memcpy(a_exponent, a + 1, 8 * sizeof(bool));
	memcpy(b_exponent, b + 1, 8 * sizeof(bool));
	ConvertToSecondaryCode(b_exponent, 8);
	return BinaryToInt(SumInMultiplication(a_exponent, b_exponent, 8), 8);
}

void ShiftMantissa(int shift, bool * mantissa)
{
	for (int i = 0; i < shift; i++) {
		for (int j = 24; j > 0; j--) {
			mantissa[j] = mantissa[j - 1];
		}
		mantissa[0] = false;
	}
}

void UnshiftMantissa(bool * mantissa)
{
	for (int j = 0; j < 24; j++) {
		mantissa[j] = mantissa[j + 1];
	}
	mantissa[24] = false;
}

bool* SumMantisses(bool * a, bool * b)
{
	int shift = GetShift(a, b);
	bool* a_mantissa = new bool[25];
	bool* b_mantissa = new bool[25];
	a_mantissa[0] = false;
	b_mantissa[0] = false;
	a_mantissa[1] = true;
	b_mantissa[1] = true;
	memcpy(a_mantissa + 2, a + 9, 23 * sizeof(bool));
	memcpy(b_mantissa + 2, b + 9, 23 * sizeof(bool));
	ShiftMantissa(shift, b_mantissa);
	if (XOR(a[0], b[0])) {
		
		ConvertToSecondaryCode(b_mantissa, 25);
	}
	return SumInMultiplication(a_mantissa, b_mantissa, 25);
}

bool IsNull(bool* a, int lenght)
{
	for (int i = 0; i < lenght; i++)
	{
		if (a[i]) {
			return false;
		}
	}
	return true;
}

bool* SumFloat(bool* a, bool* b)
{
	bool* result = new bool[INT_LENGHT];
	CompareFloats(a, b);
	if (BinaryToInt(a, INT_LENGHT) == 0 || BinaryToInt(b, INT_LENGHT) == 0) {
		return a;
	}
	bool* result_exponent = new bool[8];
	memcpy(result_exponent, a + 1, 8 * sizeof(bool));
	bool* result_mantissa = SumMantisses(a, b);
	int start = 2;
	if (result_mantissa[0] && !XOR(a[0], b[0])) {
		bool* temp = new bool[8];
		for (int i = 0; i < 7; i++) {
			temp[i] = false;
		}
		temp[7] = true;
		result_exponent = SumInMultiplication(result_exponent, temp, 8);
		ShiftMantissa(1, result_mantissa);
	}
	else {
		while (result_mantissa[0] == result_mantissa[1]) {
			bool* temp = new bool[8];
			for (int i = 0; i < 8; i++) {
				temp[i] = true;
			}
			result_exponent = SumInMultiplication(result_exponent, temp, 8);
			if (BinaryToInt(result_exponent, 8) == 0) break;
			UnshiftMantissa(result_mantissa);
		}
	}
	result[0] = a[0];
	memcpy(result + 1, result_exponent, 8 * sizeof(bool));
	memcpy(result + 9, result_mantissa + start, 23 * sizeof(bool));
	return result;
}

bool* SumExponent(bool * a, bool * b)
{
	bool* a_exponent = new bool[8];
	bool* b_exponent = new bool[8];
	memcpy(a_exponent, a + 1, 8 * sizeof(bool));
	memcpy(b_exponent, b + 1, 8 * sizeof(bool));
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
	memcpy(a_mantissa + 1, a + 9, 23 * sizeof(bool));
	memcpy(b_mantissa + 1, b + 9, 23 * sizeof(bool));

	for (int i = 0; i < 24; i++) {
		if (b_mantissa[i]) {
			bool* temp = new bool[48];
			for (int k = 0; k < 48; k++) {
				temp[k] = false;
			}

			for (int j = 0; j < 24; j++) {
				temp[i + j + 1] = a_mantissa[j];
			}
			mantissa = SumInMultiplication(mantissa, temp, 48);
		}
	}
	return mantissa;
}

bool* MultiplicationFloat(bool* a, bool* b)
{
	if (IsNull(a, INT_LENGHT) || IsNull(b, INT_LENGHT)) {
		bool* null = new bool[INT_LENGHT];
		for (int i = 0; i < INT_LENGHT; i++)
		{
			null[i] = false;
		}
		return null;
	}
	bool* result = new bool[INT_LENGHT];
	result[0] = a[0] && b[0] ? false : a[0] || b[0];
	bool* result_exponent = SumExponent(a, b);
	bool* result_mantissa = MultiplicationMantisses(a, b);
	int start = 2;
	if (result_mantissa[0]) {
		bool* shift = new bool[8];
		for (int i = 0; i < 7; i++) {
			shift[i] = false;
		}
		shift[7] = true;
		result_exponent = SumInMultiplication(result_exponent, shift, 8);
		start = 1;
	}
	memcpy(result + 1, result_exponent, 8 * sizeof(bool));
	memcpy(result + 9, result_mantissa + start, 23 * sizeof(bool));
	return result;
}