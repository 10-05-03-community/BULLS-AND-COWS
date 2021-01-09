#ifndef BULLS_AND_COWS_HPP
#define BULLS_AND_COWS_HPP
#include <iostream>
#include <vector>
#include <ctime>

class BULLS_AND_COWS {
private:
	bool check_user_number(size_t);
	bool check_computer_number(size_t);
	std::vector<short> digits_number(size_t);
	std::pair <short, short> check_bulls_cows(std::vector<short>&, std::vector<short>&);
	struct BULLS_COWS
	{
		short bulls;
		short cows;
		std::vector<short> digits;
	};
	size_t algoritm(std::vector<BULLS_COWS>&, short);
public:
	void play();
};


#endif // !BULLS_AND_COWS_HPP