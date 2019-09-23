#pragma once

const int INT_LENGHT = sizeof(int) * CHAR_BIT;

const int FLOAT_LENGHT = 128;

void example();

void PrintBinary(bool * value, int lenght);

void PrintBinary(bool * value, int start, int end);

int ConvertBinaryToInt(bool* value, int lenght);

int ConvertBinaryToInt(bool* value, int start, int end);

void GetSecondaryCode(bool * result, int lenght);

bool* ParseIntToBinary(int value);

bool XOR(bool a, bool b);

bool* SumInteger(bool* a_binary, bool* b_binary);

bool* Summator(bool* a_binary, bool* b_binary, int lenght);

bool* MultiplicationInteger(bool* a, bool* b);

int GetTrueLenght(bool* value, int lenght);

bool* ParseIntegerPart(float value, int lenght);

bool* ParseFractionPart(float fract);

bool* ParseFloatToBinary(float value);

void CompareFloats(bool * &a, bool * &b);

int GetShift(bool * a, bool * b);

void ShiftMantissa(int shift, bool * mantissa);

void UnshiftMantissa(bool * mantissa);

bool* SumMantisses(bool * a, bool * b);

bool IsZero(bool* a, int lenght);

bool* SumFloat(bool* a, bool* b);

bool* SumExponent(bool * a, bool * b);

bool * MultiplicationMantisses(bool * a, bool * b);

bool* MultiplicationFloat(bool* a, bool* b);