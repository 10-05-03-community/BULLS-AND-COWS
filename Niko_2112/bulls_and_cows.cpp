#include "bulls_and_cows.h"

void BULLS_AND_COWS::play() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	std::cout << "Загадайте число и введите его: ";
	size_t number_user;
	std::cin >> number_user;

	while (!check_user_number(number_user)) {
		std::cin >> number_user;
	}

	std::vector<short> table_user_number = digits_number(number_user);

	size_t computer_number = 0;
	while (!check_computer_number(computer_number)) {
		computer_number = rand() % 9000 + 1000;
	}
	std::vector<short> table_computer_number = digits_number(computer_number);

	std::vector<BULLS_COWS>vector_bulls_cows;
	size_t guessed_number = 0;
	size_t guessed_user_number = 0;
	size_t num_of_attempts = 0;

	while (!check_computer_number(guessed_number)) {
		guessed_number = rand() % 9000 + 1000;
	}

	std::vector< short> table_computer_digits = digits_number(guessed_number);
	std::pair < short, short> p1 = check_bulls_cows(table_computer_digits, table_user_number);
	BULLS_COWS struct_1;
	struct_1.bulls = p1.first;
	struct_1.cows = p1.second;
	struct_1.digits = table_computer_digits;
	vector_bulls_cows.push_back(struct_1);
	num_of_attempts++;
	std::cout << "Угадайте число компьютера: ";
	std::cin >> guessed_user_number;
	std::vector< short> table_user_digits = digits_number(guessed_user_number);
	std::pair < short, short> p2 = check_bulls_cows(table_user_digits, table_computer_number);
	std::cout << "Ваше число: " << guessed_user_number << "\t\tЧисло компьютера: " << guessed_number;
	std::cout << "\nКоличество быков: " << p2.first << "\t\tКоличество быков: " << p1.first;
	std::cout << "\nКоличество коров: " << p2.second << "\t\tКоличество коров: " << p1.second << "\n";
	

	while (!(guessed_number == number_user or guessed_user_number == computer_number)) {
		guessed_number = algoritm(vector_bulls_cows, vector_bulls_cows.size());
		std::vector< short> table_digits = digits_number(guessed_number);
		std::pair < short, short> p1 = check_bulls_cows(table_digits, table_user_number);
		BULLS_COWS struct_1;
		struct_1.bulls = p1.first;
		struct_1.cows = p1.second;
		struct_1.digits = table_digits;
		vector_bulls_cows.push_back(struct_1);
		num_of_attempts++;
		std::cout << "Угадайте число компьютера: ";
		std::cin >> guessed_user_number;
		std::vector< short> table_user_digits = digits_number(guessed_user_number);
		std::pair < short, short> p2 = check_bulls_cows(table_user_digits, table_computer_number);
		std::cout << "Ваше число: " << guessed_user_number << "\t\tЧисло компьютера: " << guessed_number;
		std::cout << "\nКоличество быков: " << p2.first << "\t\tКоличество быков: " << p1.first;
		std::cout << "\nКоличество коров: " << p2.second << "\t\tКоличество коров: " << p1.second << "\n";
	}

	if (guessed_number == number_user and guessed_user_number == computer_number) {
		std::cout << ":::::::::::::::::::::::::НИЧЬЯ:::::::::::::::::::::::::" << std::endl;
		std::cout << ":::::::::::::::::::::::::Компьютер загадал: " << computer_number << std::endl;
		std::cout << ":::::::::::::::::::::::::Вы загадали: " << number_user << std::endl;
		std::cout << ":::::::::::::::::::::::::Количество попыток: " << num_of_attempts << std::endl;
	}
	else if (guessed_number == number_user) {
		std::cout << ":::::::::::::::::::::::::ВЫ ПРОИГРАЛИ:::::::::::::::::::::::::" << std::endl;
		std::cout << ":::::::::::::::::::::::::Компьютер загадал: " << computer_number << std::endl;
		std::cout << ":::::::::::::::::::::::::Вы загадали: " << number_user << std::endl;
		std::cout << ":::::::::::::::::::::::::Количество попыток: " << num_of_attempts << std::endl;
	}
	else if (guessed_user_number == computer_number) {
		std::cout << ":::::::::::::::::::::::::ВЫ ПОБЕДИЛИ:::::::::::::::::::::::::" << std::endl;
		std::cout << ":::::::::::::::::::::::::Компьютер загадал: " << computer_number << std::endl;
		std::cout << ":::::::::::::::::::::::::Вы загадали: " << number_user << std::endl;
		std::cout << ":::::::::::::::::::::::::Количество попыток: " << num_of_attempts << std::endl;
	}
}

// проверка правильности ввода числа пользователем
bool BULLS_AND_COWS::check_user_number(size_t number) {
	std::vector< uint8_t > digits(10, 0);
	uint8_t number_signs = 0;
	while (number != 0) {
		uint8_t digit = number % 10;
		number /= 10;
		number_signs++;
		if (digits[digit] == 0) {
			digits[digit] = 1;
		}
		else {
			std::cout << "Число не может сожержать одинаковых цифр\n";
			return false;
		}
	}

	if (number_signs != 4) {
		std::cout << "Число должно быть четырехзначным \n";
		return false;
	}

	return true;
}

// проверка числа компьютера на правильность
bool BULLS_AND_COWS::check_computer_number(size_t number) {
	std::vector< uint8_t > digits(10, 0);
	uint8_t number_signs = 0;
	while (number != 0) {
		uint8_t digit = number % 10;
		number /= 10;
		number_signs++;
		if (digits[digit] == 0) {
			digits[digit] = 1;
		}
		else {
			return false;
		}
	}

	if (number_signs != 4) {
		return false;
	}

	return true;
}

// разделяем число на цифры по разрядам
std::vector< short> BULLS_AND_COWS::digits_number(size_t number) {
	std::vector<  short> table_digits(4, 0);

	table_digits[0] = number / 1000;
	table_digits[1] = (number % 1000) / 100;
	table_digits[2] = (number % 100) / 10;
	table_digits[3] = number % 10;

	return table_digits;
}

// считаем количество быков и количество коров, которые отгадал компьютер
std::pair < short, short> BULLS_AND_COWS::check_bulls_cows(std::vector< short>& table_guessed_number, std::vector< short>& table_user_number) {
	short bulls = 0;
	short cows = 0;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (table_guessed_number[i] == table_user_number[j]) {
				if (i == j) {
					bulls++;
				}
				else {
					cows++;
				}
				break;
			}
		}
	}
	
	std::pair < short, short> p1;
	p1.first = bulls;
	p1.second = cows;

	return p1;
}

// алгоритм поиска числа пользователя
size_t BULLS_AND_COWS::algoritm(std::vector<BULLS_COWS>& vector_bulls_cows, short count) {

	for (size_t guessed_number = 1000; guessed_number < 10000; guessed_number++) {
		if (!check_computer_number(guessed_number)) {
			continue;
		}
		short number_conditions = 0;
		for (size_t i = 0; i < count; i++) {
			std::vector< short> vector_digits = digits_number(guessed_number);
			std::pair<short, short> p1 = check_bulls_cows(vector_digits, vector_bulls_cows[i].digits);
			if (p1.first == vector_bulls_cows[i].bulls and p1.second == vector_bulls_cows[i].cows) {
				number_conditions++;
			}
		}

		if (number_conditions == count) {
			return guessed_number;
		}
	}
}