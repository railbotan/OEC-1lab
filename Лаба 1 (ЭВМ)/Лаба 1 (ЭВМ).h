#pragma once

const int INT_LENGHT = sizeof(int) * CHAR_BIT;

const int FLOAT_LENGHT = 128;

void example();

void PrintBinary(bool * value, int lenght);

void PrintBinary(bool * value, int start, int end);

int BinaryToInt(bool* value, int lenght);

int BinaryToInt(bool* value, int start, int end);

void ConvertToSecondaryCode(bool * result, int lenght);

bool* IntToBinary(int value);

bool XOR(bool a, bool b);

bool* SumIntegerBinary(bool* a_binary, bool* b_binary);

bool* SumInMultiplication(bool* a_binary, bool* b_binary, int lenght);

bool* MultiplicationInteger(bool* a, bool* b);

int GetTrueLenght(bool* value, int lenght);

bool* IntegerPartToBinary(float value, int lenght);

bool* ParseFraction(float fract);

bool* FloatToBinary(float value);

void CompareFloats(bool * &a, bool * &b);

int GetShift(bool * a, bool * b);

void ShiftMantissa(int shift, bool * mantissa);

void UnshiftMantissa(bool * mantissa);

bool* SumMantisses(bool * a, bool * b);

bool IsNull(bool* a, int lenght);

bool* SumFloat(bool* a, bool* b);

bool* SumExponent(bool * a, bool * b);

bool * MultiplicationMantisses(bool * a, bool * b);

bool* MultiplicationFloat(bool* a, bool* b);