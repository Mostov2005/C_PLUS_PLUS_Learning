#ifndef C__LEARNING_TASK2_1_H
#define C__LEARNING_TASK2_1_H
#include <vector>
#include <string>


class Task2_1 {
public:
    void run();

private:
    // 1. Функции для сравнения строк
    int hamming(const std::string &s1, const std::string &s2);

    int levenshtein(const std::string &s1, const std::string &s2);

    bool hammingEqualsLevenshtein(const std::string &s1, const std::string &s2);

    // 2. Функции для работы с массивами
    void shiftMiddleColumn(std::vector<std::vector<int> > &mat);

    void printMatrix(const std::vector<std::vector<int> > &mat);

    // 3. Функции для проектирования
    void splitDigits(int num, std::vector<int> &digits);
};

#endif //C__LEARNING_TASK2_1_H
