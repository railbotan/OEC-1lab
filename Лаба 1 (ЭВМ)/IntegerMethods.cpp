#include "pch.h"
#include <iostream>
#include <bitset>
#include <limits>
#include "À‡·‡ 1 (›¬Ã).h"


using namespace std;

void PrintBinary(bool * value)
{
	for (int i = 0; i < INT_LENGHT; i++)
	{
		cout << value[i] ? 1 : 0;
	}
	cout << endl;
}

void PrintLongBinary(bool * value)
{
	for (int i = INT_LENGHT; i < 2 * INT_LENGHT; i++)
	{
		cout << value[i] ? 1 : 0;
	}
	cout << endl;
}

int BinaryToInt(bool* value)
{
	int result = 0;
	for (int i = 0; i < INT_LENGHT; i++)
	{
		if (value[i])
		{
			result += pow(2, 31 - i);
		}
	}
	return result;
}

int LongBinaryToInt(bool* value)
{
	int result = 0;
	for (int i = INT_LENGHT; i < 2 * INT_LENGHT; i++)
	{
		if (value[i])
		{
			result += pow(2, 63 - i);
		}
	}
	return result;
}

void ConvertToSecondaryCode(bool * result)
{
	bool flag = false;
	for (int i = INT_LENGHT - 1; i >= 0; i--)
	{
		if (!flag && result[i])
		{
			flag = true;
		}
		else if (flag)
		{
			result[i] = !result[i];
		}
	}
}

bool* IntToBinary(int value) 
{
	int temp = value;
	bool* result = new bool[INT_LENGHT];
	for (int i = INT_LENGHT - 1; i >= 0; i--)
	{
		result[i] = temp % 2;
		temp /= 2;
	}
	if (value < 0)
	{
		ConvertToSecondaryCode(result);
	}
	return result;
}

bool XOR(bool a, bool b)
{
	return a && !b || !a && b;
}

bool* SumIntegerBinary(bool* a_binary, bool* b_binary)
{
	bool* result = new bool[INT_LENGHT];
	bool carry = false;
	for (int i = INT_LENGHT - 1; i >= 0; i--)
	{
		result[i] = XOR(XOR(a_binary[i], b_binary[i]), carry);
		carry = a_binary[i] && b_binary[i] || carry && b_binary[i] || a_binary[i] && carry;
	}
	return result;
}

bool* SumInMultiplication(bool* a_binary, bool* b_binary)
{
	bool* result = new bool[2 * INT_LENGHT];
	bool carry = false;
	for (int i = 2 * INT_LENGHT - 1; i >= 0; i--)
	{
		result[i] = XOR(XOR(a_binary[i], b_binary[i]), carry);
		carry = a_binary[i] && b_binary[i] || carry && b_binary[i] || a_binary[i] && carry;
	}
	delete[] a_binary;
	delete[] b_binary;
	return result;
}