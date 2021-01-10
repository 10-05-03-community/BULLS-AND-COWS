#include "bulls_and_cows.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

Bulls_and_Cows::Bulls_and_Cows(int mode, unsigned len_of_number, bool nill_may_be_first, bool repetition)
    : mode_(mode), len_of_number_(len_of_number), nill_may_be_first_(nill_may_be_first), repetition_(repetition) {
}


void Bulls_and_Cows::start() {

    std::srand(std::time(0));

    switch (mode_) {
        case 1: start_solo(); break;
        case 2: start_vs_AI(); break;
        case 3: start_AI_vs_AI(); break;
        default: std::cout << "No this mode\n"; break;
    }
}

//// PRIVATE ////

void Bulls_and_Cows::show_global_params() {

    std::cout << "Bulls_and_Cows::Params" << std::endl;
    std::cout << "  len_of_number = " << len_of_number_ << std::endl;
    std::cout << "  nill_may_be_first = " << (nill_may_be_first_ ? "true" : "false") << std::endl;
    std::cout << "  digits_may_repeat = " << (repetition_ ? "true" : "false") << std::endl;

    std::cout << "  mode_ = ";
    if (mode_ == 1) {
        std::cout << " solo";
    } else if (mode_ == 2) {
        std::cout << " human_vs_AI";
    } else if (mode_ == 3) {
        std::cout << " AI_vs_AI";
    } else {
        std::cout << "No this mode";
    }
    std::cout << std::endl;
}


void Bulls_and_Cows::show_status(const unsigned& step, const std::vector<unsigned>& input_number, const std::pair<unsigned, unsigned>& bulls_and_cows) {

    std::cout << std::endl;
    std::cout << "Step: " << step << std::endl;
    std::cout << " input_number: ";
    for (auto x : input_number) {
        std::cout << x;
    }
    std::cout << std::endl;
    std::cout << " bulls: " << bulls_and_cows.first << " , cows: " << bulls_and_cows.second << std::endl;
}


void Bulls_and_Cows::start_solo() {

    show_global_params();

    std::vector<unsigned> guessed_number = generate_number();

    std::cout << "AI guessed number, try to find it\n";

    unsigned step = 0;
    std::vector<unsigned> input_number;
    std::pair<unsigned, unsigned> bulls_and_cows;

    do {
        ++step;
        input_number = get_number_from_console();
        bulls_and_cows = get_bulls_and_cows(guessed_number, input_number);
        show_status(step, input_number, bulls_and_cows);
    } while (bulls_and_cows.first != len_of_number_);

    std::cout << "Congratulates! You win!" << std::endl;
}


bool Bulls_and_Cows::is_good_number(unsigned number) {

    if (!nill_may_be_first_) {
        if (number < unsigned(std::pow(10, len_of_number_ -1))) {
            // nill can't be first
            return false;
        }
    }

    if (number >= unsigned(std::pow(10, len_of_number_))) {
        // a lot of digits
        return false;
    }

    std::vector<bool> has_digit(10, false);
    for (unsigned i = 0; i < len_of_number_; ++i) {

        unsigned digit = number % 10;

        if (has_digit[digit] && !repetition_) {
            // repetition shouldn't be
            return false;
         } else {
             has_digit[digit] = true;
             number /= 10;
         }
    }

    return true;
}


std::vector<unsigned>  Bulls_and_Cows::generate_number() {

    unsigned number = 0;
    unsigned max = unsigned(std::pow(10,len_of_number_ ));
    std::vector<unsigned> v_number(len_of_number_, 0);

    bool good = false;
    while (!good) {
        number = std::rand() % max;
        good = is_good_number(number);
    }

    for (unsigned i = 0; i < len_of_number_; ++i) {
        v_number[len_of_number_ - 1 - i] = number % 10;
        number /= 10;
    }

    return v_number;
}


std::vector<unsigned> Bulls_and_Cows::get_number_from_console() {

    unsigned number = 0;
    std::vector<unsigned> v_number(len_of_number_, 0);

    bool good_input = false;
    while (!good_input) {

        std::cout << "Input number: ";
        std::cin >> number;

        good_input = is_good_number(number);
        if (std::cin.fail() || (std::cin.peek() != '\n')) {
            std::cin.clear();
            good_input = false;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (!good_input) {
            std::cout << "Bad_value. Try again!" << std::endl;
        }
    }

    for (unsigned i = 0; i < len_of_number_; ++i) {
        v_number[len_of_number_ - 1 - i] = number % 10;
        number /= 10;
    }

    return v_number;
}


std::pair<unsigned, unsigned> Bulls_and_Cows::get_bulls_and_cows(const std::vector<unsigned>& guessed_number, const std::vector<unsigned>& input_number) {

    unsigned bulls = 0;
    unsigned cows = 0;

    std::vector<bool> digit_was_counted(len_of_number_, false);

    for (unsigned i = 0; i < len_of_number_; ++i) {
        if (guessed_number[i] == input_number[i]) {
            ++bulls;
            digit_was_counted[i] = true;
        }
    }

    for(unsigned i = 0; i < len_of_number_; ++i) {
        if (digit_was_counted[i]) {
            continue;
        }
        for (unsigned j = 0; j < len_of_number_; ++j) {
            if (!digit_was_counted[j] && (guessed_number[i] == input_number[j])) {
                ++cows;
                digit_was_counted[j] = true;
                break;
            }
        }
    }

    return std::make_pair(bulls, cows);
}


void Bulls_and_Cows::start_vs_AI() {
}


void Bulls_and_Cows::start_AI_vs_AI() {
}
