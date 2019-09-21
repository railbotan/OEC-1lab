#include "pch.h"
#include <iostream>
#include <bitset>
#include <limits>

using namespace std;

void example()
{
	int a = 25, b = -25;
	short int s = 78, ns = -78;

	cout << "Перевод в двоичный код целых чисел" << endl;
	cout << a << "  = " << bitset<32>(a) << endl;
	cout << b << " = " << bitset<32>(b) << endl;
	cout << s << "  = " << bitset<16>(s) << endl;
	cout << ns << " = " << bitset<16>(ns) << endl;

	cout << endl;
	cout << "-" << a << " = " << bitset<32>(~a + 1) << endl;
	cout << "-" << s << " = " << bitset<16>(~s + 1) << endl;

	cout << endl;
	cout << a << "  = " << bitset<sizeof(a) * CHAR_BIT>(a) << endl;
	cout << b << " = " << bitset<sizeof(b) * CHAR_BIT>(b) << endl;
	cout << s << "  = " << bitset<sizeof(s) * CHAR_BIT>(s) << endl;
	cout << ns << " = " << bitset<sizeof(ns) * CHAR_BIT>(ns) << endl;

	cout << endl;
	cout << "Перевод в двоичный код чисел с плавающей запятой" << endl;
	float g = 0.99;
	int* rf = reinterpret_cast<int *>(&g);
	cout << g << " = " << bitset<32>(*rf) << endl;

	cout << endl;
	float f = 0.01, nf = -0.01;
	g = 0.99;
	float sum = f + g;
	float ff = numeric_limits<float>::quiet_NaN();
	float fff = numeric_limits<float>::infinity();

	rf = reinterpret_cast<int *>(&f);
	cout << f << "  = " << bitset<32>(*rf) << endl;
	rf = reinterpret_cast<int *>(&nf);
	cout << nf << " = " << bitset<32>(*rf) << endl;
	rf = reinterpret_cast<int *>(&ff);
	cout << "NaN\t" << " = " << bitset<32>(*rf) << endl;
	rf = reinterpret_cast<int *>(&fff);
	cout << "Infinity" << " = " << bitset<32>(*rf) << endl;

	cout << endl;
	rf = reinterpret_cast<int *>(&f);
	cout << f << " = " << bitset<32>(*rf) << endl;
	rf = reinterpret_cast<int *>(&g);
	cout << g << " = " << bitset<32>(*rf) << endl;
	rf = reinterpret_cast<int *>(&sum);
	cout << f << " + " << g << " = " << bitset<32>(*rf) << endl;
}