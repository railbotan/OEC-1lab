#include "pch.h"
#include <iostream>
#include <bitset>
#include <limits>
#include "À‡·‡ 1 (›¬Ã).h"

using namespace std;

void PrintBinary(bool * value, int lenght)
{
	for (int i = 0; i < lenght; i++) {
		cout << value[i] ? 1 : 0;
	}
	cout << endl;
}

void PrintBinary(bool * value, int start, int end)
{
	for (int i = start; i < end; i++) {
		cout << value[i] ? 1 : 0;
	}
	cout << endl;
}

int ConvertBinaryToInt(bool* value, int lenght)
{
	int result = 0;
	for (int i = 0; i < lenght; i++) {
		if (value[i]) {
			result += pow(2, lenght - 1 - i);
		}
	}
	return result;
}

int ConvertBinaryToInt(bool * value, int start, int end)
{
	int result = 0;
	int count = 0;
	for (int i = start; i < end; i++) {
		if (value[i]) {
			result += pow(2, (end - start - 1) - count);
		}
		count++;
	}
	return result;
}

void GetSecondaryCode(bool * result, int lenght)
{
	bool flag = false;
	for (int i = lenght - 1; i >= 0; i--) {
		if (!flag && result[i]) {
			flag = true;
		}
		else if (flag) {
			result[i] = !result[i];
		}
	}
}

bool* ParseIntToBinary(int value)
{
	int temp = value;
	bool* result = new bool[INT_LENGHT];
	for (int i = INT_LENGHT - 1; i >= 0; i--) {
		result[i] = temp % 2;
		temp /= 2;
	}
	if (value < 0) {
		GetSecondaryCode(result, INT_LENGHT);
	}
	return result;
}

bool XOR(bool a, bool b)
{
	return a && !b || !a && b;
}

bool* SumInteger(bool* a_binary, bool* b_binary)
{
	bool* result = new bool[INT_LENGHT];
	bool carry = false;
	for (int i = INT_LENGHT - 1; i >= 0; i--) {
		result[i] = XOR(XOR(a_binary[i], b_binary[i]), carry);
		carry = a_binary[i] && b_binary[i] || carry && b_binary[i] || a_binary[i] && carry;
	}
	return result;
}

bool* Summator(bool* a_binary, bool* b_binary, int lenght)
{
	bool* result = new bool[lenght];
	bool carry = false;
	for (int i = lenght - 1; i >= 0; i--) {
		result[i] = XOR(XOR(a_binary[i], b_binary[i]), carry);
		carry = a_binary[i] && b_binary[i] || carry && b_binary[i] || a_binary[i] && carry;
	}
	delete[] a_binary;
	delete[] b_binary;
	return result;
}

bool* MultiplicationInteger(bool* a, bool* b)
{
	bool* result = new bool[2 * INT_LENGHT];
	for (int i = 0; i < 2 * INT_LENGHT; i++) {
		result[i] = false;
	}
	for (int i = 0; i < INT_LENGHT; i++) {
		if (b[i]) {
			bool* temp = new bool[2 * INT_LENGHT];
			for (int k = 0; k < 2 * INT_LENGHT; k++) {
				temp[k] = false;
			}
			for (int j = 0; j < INT_LENGHT; j++) {
				temp[i + j + 1] = a[j];
			}
			result = Summator(result, temp, 2 * INT_LENGHT);
		}
	}
	return result;
}