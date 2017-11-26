// longGCD.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>

// проверка, является ли строка целым числом (состоит из одних цифр)
bool check(std::string s) {
	if (s.length() == 0)
		return false;

	for (size_t i = 0; i < s.length(); i++)
		if (s[i] < '0' || s[i] > '9')
			return false; // если какой-то символ не цифра - не число

	return true; // если не вышли раньше, значит число
}

// получение целого числа (точнее строки, состоящей только из цифр)
std::string getNumber(std::string msg) {
	std::cout << msg; // выводим сообщение
	
	std::string s; // строка для получения результата
	getline(std::cin, s); // считываем строку

	while (!check(s)) { // пока это не число просим повторить
		std::cout << "Incorrect number. Try again: ";
		getline(std::cin, s);
	}

	return s; // возвращаем строку
}

// проверка, что число a меньше числа b
bool less(const std::string &a, const std::string &b) {
	size_t len1 = a.length(); // запоминаем длину первого числа
	size_t len2 = b.length(); // запоминаем длину второго числа

	// если длины не равны
	if (len1 != len2)
		return (len1 < len2); // меньше число с меньшей длинной

	size_t i = 0;

	// ищем разряд, в котором значения отличаются
	while (i < len1 && a[i] == b[i])
		i++;

	// если разряд найден, то меньше число с меньшей цифрой
	return (i < len1) && (a[i] < b[i]);
}

std::string minus(const std::string &a, const std::string &b) {
	if (a == b)
		return "0"; // если числа равны, то какой смысл вычитать?

	size_t len1 = a.length(); // запоминаем длину первого числа
	size_t len2 = b.length(); // запоминаем длину второго числа
	size_t length = len1 > len2 ? len1 : len2; // длина результата не превысит максимума длин чисел

	// массивы аргументов
	int *x_a = new int[length];
	int *x_b = new int[length];
	x_a[0] = x_b[0] = 0; // обнуляем нулевые элементы массивов

	char *res = new char[length + 1]; // строковый массив для результата
	res[length - 1] = res[length] = '\0'; // устанавливаем символ окончания строки

	for (size_t i = 0; i < length - 1; i++) {
		x_a[i] += (i < len1) ? (a[len1 - 1 - i] - '0') : 0; // формируем разряды
		x_b[i] += (i < len2) ? (b[len2 - 1 - i] - '0') : 0; // из строк аргументов

		x_b[i + 1] = 0; // занимаем
		x_a[i + 1] = -1; // 10 у следующего разряда

		res[length - 1 - i] += x_a[i] - x_b[i] + 10;
		res[length - 1 - i - 1] = res[length - 1 - i] / 10;
		res[length - 1 - i] = res[length - 1 - i] % 10 + '0';
	}

	// выполняем операцию с последним разрядом
	x_a[length - 1] += (length - 1 < len1) * (a[0] - '0');
	x_b[length - 1] += (length - 1 < len2) * (b[0] - '0');

	// записываем в строку последний разряд
	res[0] += x_a[length - 1] - x_b[length - 1] + '0';

	std::string result(res);

	delete[] x_a;
	delete[] x_b;
	delete[] res;

	while (result[0] == '0' && result.length() > 1)
		result = result.substr(1);

	return result; // возвращаем результат
}

// отстаток от деления a на b
std::string mod(std::string a, std::string b) {
	if (a == "0" || b == "1")
		return "0"; // если а равно нулю или b равно 1, то остаток по определению равен 0

	std::string tmp = b;
	std::string mod2 = a;
	std::string v = "";

	size_t index = 0;

	// ищем такую часть исходного числа, чтобы можно было разделить (вспомним деление в столбик)
	while (less(v, tmp) && index < a.length())
		v += a[index++];

	do {
		if (!less(v, tmp)) {
			std::string mod = v;

			// подбираем текущий остаток от деления
			while (!less(mod, tmp))
				mod = minus(mod, tmp);

			v = mod;
		}

		if (index <= a.length()) {
			mod2 = v;
			v += a[index++];
		}
	} while (index <= a.length()); // пока не дойдём до конца числа, выполняем деление

	if (mod2 == "")
		mod2 = "0";

	// избавляемся от ведущих нулей
	while (mod2[0] == '0' && mod2.length() > 1)
		mod2 = mod2.substr(1);

	return mod2; // возвращаем остаток
}

// алгоритм Евклида :)
std::string gcd(std::string a, std::string b) {
	return b != "0" ? gcd(b, mod(a, b)) : a;
}

int main() {
	// вводим числа
	std::string m = getNumber("Enter m: ");
	std::string n = getNumber("Enter n: ");
	std::string p = getNumber("Enter p: ");

	// выводим то, что ввели для проверки ввода
	std::cout << std::endl << "You entered: " << std::endl;
	std::cout << "m: " << m << std::endl;
	std::cout << "n: " << n << std::endl;
	std::cout << "p: " << p << std::endl;

	// выводим результаты
	std::cout << std::endl << "GCD(m, n, p) = " << gcd(gcd(m, n), p) << std::endl;

	system("pause");
    return 0;
}

