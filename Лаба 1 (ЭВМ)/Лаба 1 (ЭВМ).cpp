// Лаба 1 (ЭВМ).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <bitset>
#include <limits>
#include "Лаба 1 (ЭВМ).h"


using namespace std;

bool* MultiplicationInteger(bool* a, bool* b)
{
	bool* result = new bool[2 * INT_LENGHT];
	for (int i = 0; i < 2 * INT_LENGHT; i++)
	{
		result[i] = false;
	}
	for (int i = 0; i < INT_LENGHT; i++)
	{
		if (b[i])
		{
			bool* temp = new bool[2 * INT_LENGHT];
			for (int k = 0; k < 2 * INT_LENGHT; k++)
			{
				temp[k] = false;
			}
			for (int j = 0; j < INT_LENGHT; j++)
			{
				temp[i + j + 1] = a[j];
			}
			result = SumInMultiplication(result, temp);
		}
	}
	return result;
}

void FirstTask()
{
	float num;
	cin >> num;
	float fractional_part, integer_part;
	fractional_part = modf(num, &integer_part);
	if (fractional_part == 0)
	{
		cout << bitset<32>(integer_part) << endl;
		bool* value = IntToBinary(integer_part);
		PrintBinary(value);
	}
	else
	{
		int* rf = reinterpret_cast<int*>(&num);
		cout << bitset<32>(*rf) << endl;
	}
	cout << endl;
}

void SecondTask() 
{
	int a, b;
	cin >> a >> b;
	bool* a_binary = IntToBinary(a);
	bool* b_binary = IntToBinary(b);
	//bool* result = SumBinary(a_binary, b_binary);
	bool* result = MultiplicationInteger(a_binary, b_binary);
}

int main()
{
	setlocale(0, "");

	//example();

	//FirstTask();

	//SecondTask();

	int a, b;
	cin >> a >> b;
	cout << bitset<32>(a) << endl;
	cout << bitset<32>(b) << endl;
	bool* r = MultiplicationInteger(IntToBinary(a), IntToBinary(b));
	PrintLongBinary(r);
	cout << LongBinaryToInt(r) << endl;
}