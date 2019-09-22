#include "pch.h"
#include <iostream>
#include <bitset>
#include <limits>
#include "Лаба 1 (ЭВМ).h"

using namespace std;

void FirstTask()
{
	cout << "Введите число:" << endl;
	float num;
	cin >> num;
	float fractional_part, integer_part;
	fractional_part = modf(num, &integer_part);
	if (fractional_part == 0)
	{
		cout << "Вы ввели целое число: " << num << ", двоичный код которого:" << endl;
		cout << "bitset:	\t" << bitset<32>(integer_part) << endl;
		bool* value = IntToBinary(integer_part);
		cout << "Наш метод:\t";
		PrintBinary(value, INT_LENGHT);
	}
	else
	{
		cout << "Вы ввели дробное число: " << num << ", двоичный код которого:" << endl;
		int* rf = reinterpret_cast<int*>(&num);
		cout << "bitset:	\t" << bitset<32>(*rf) << endl;
		cout << "Наш метод:\t";
		PrintBinary(FloatToBinary(num), INT_LENGHT);
	}
	cout << endl;
}

void SecondTask() 
{
	cout << "Введите целые числа" << endl;
	int a, b;
	cin >> a >> b;
	bool* a_binary = IntToBinary(a);
	cout << "a = \t";
	PrintBinary(a_binary, INT_LENGHT);
	bool* b_binary = IntToBinary(b);
	cout << "b = \t";
	PrintBinary(b_binary, INT_LENGHT);
	bool* resultSum = SumIntegerBinary(a_binary, b_binary);
	cout << "a + b = ";
	PrintBinary(resultSum, INT_LENGHT);
	bool* resultMult = MultiplicationInteger(a_binary, b_binary);
	cout << "a * b = ";
	PrintBinary(resultMult, INT_LENGHT, 2 * INT_LENGHT);
	cout << "a + b = " << BinaryToInt(resultSum, INT_LENGHT) << endl;
	cout << "a * b = " << BinaryToInt(resultMult, INT_LENGHT, 2 * INT_LENGHT) << endl;
}

int main()
{
	setlocale(0, "");

	//example();

	//FirstTask();

	//SecondTask();

	float a, b;
	cin >> a >> b;
	bool* a_binary = FloatToBinary(a);
	cout << "a = \t";
	PrintBinary(a_binary, INT_LENGHT);
	bool* b_binary = FloatToBinary(b);
	cout << "b = \t";
	PrintBinary(b_binary, INT_LENGHT);

	cout << "\t";
	float c = a * b;
	int* rf = reinterpret_cast<int*>(&c);
	cout << bitset<32>(*rf) << endl;
	cout << "\t";
	PrintBinary(MultiplicationFloat(a_binary, b_binary), INT_LENGHT);
	

	/*float a;
	cin >> a;
	int* ra = reinterpret_cast<int*>(&a);
	cout << bitset<32>(*ra) << endl;
	PrintBinary(FloatToBinary(a), INT_LENGHT);*/
}