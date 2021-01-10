#ifndef BULLS_AND_COWS_HPP
#define BULLS_AND_COWS_HPP

#include <utility>
#include <vector>

class Bulls_and_Cows {
public:

    // по-умолчанию в игре человек угадывает число ИИ из 4 цифр, 0 не может быть первым, повторений нет
    // если mode == 2, то человек против ИИ
    // если mode == 3, то ИИ против ИИ
    Bulls_and_Cows(int mode = 1, unsigned len_of_number = 4, bool nill_may_be_first = false, bool repetition = false);

    // начало игры, главная функция
    void start();

private:

    // угадывать у компьютера
    void start_solo();

    // против ИИ
    void start_vs_AI();

    // ИИ против ИИ
    void start_AI_vs_AI();


    // показать параметры игры
    void show_global_params();

    // показать статус хода
    void show_status(const unsigned& step, const std::vector<unsigned>& input_number, const std::pair<unsigned, unsigned>& bulls_and_cows);

    // сгенерировать число для отгадывания
    std::vector<unsigned> generate_number();

    // получить число с консоли
    std::vector<unsigned> get_number_from_console();

    // проверка на правильность генерации или ввода числа
    bool is_good_number(unsigned number);

    // посчитать число быков и коров
    std::pair<unsigned, unsigned> get_bulls_and_cows(const std::vector<unsigned>& guessed_number, const std::vector<unsigned>& input_number);

    int mode_;
    unsigned len_of_number_;
    bool nill_may_be_first_;
    bool repetition_;

};

#endif // BULLS_AND_COWS_HPP
