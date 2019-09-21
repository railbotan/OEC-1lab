#pragma once

const int INT_LENGHT = sizeof(int) * CHAR_BIT;

void example();

void PrintBinary(bool * value);

void PrintLongBinary(bool * value);

int BinaryToInt(bool* value);

int LongBinaryToInt(bool* value);

void ConvertToSecondaryCode(bool * result);

bool* IntToBinary(int value);

bool XOR(bool a, bool b);

bool* SumIntegerBinary(bool* a_binary, bool* b_binary);

bool* SumInMultiplication(bool* a_binary, bool* b_binary);