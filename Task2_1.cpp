#include "Task2_1.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void Task2_1::run() {
    cout << "Задание 2.1 Передача параметров и возврат значения\n\n";

    // 1. Функция, возвращающая значение
    string a = "hello";
    string b = "hallo";
    bool eq = hammingEqualsLevenshtein(a, b); // 1 и 1
    cout << (eq ? "true" : "false") << "\n\n";

    // 2. Функция, не возвращающая значение
    vector<vector<int> > matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "Матрица перед сдвигом:\n";
    printMatrix(matrix);
    shiftMiddleColumn(matrix);
    cout << "Матрица после сдвига:\n";
    printMatrix(matrix);

    // 3. Функция для проектирования
    int number = 12345;
    vector<int> digits;
    splitDigits(number, digits);
    cout << "\nЦифры: " << number << ": ";
    for (int d: digits) cout << d << " ";
    cout << "\n";
    cout << "Количество цифр: " << digits.size() << "\n";
}

// 1. Функции для сравнения расстояний
int Task2_1::hamming(const string &s1, const string &s2) {
    if (s1.size() != s2.size()) return -1;
    int dist = 0;
    for (size_t i = 0; i < s1.size(); i++)
        if (s1[i] != s2[i]) dist++;
    return dist;
}

int Task2_1::levenshtein(const string &s1, const string &s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int> > dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + (s1[i - 1] != s2[j - 1])});
    return dp[n][m];
}

bool Task2_1::hammingEqualsLevenshtein(const string &s1, const string &s2) {
    int h = hamming(s1, s2);
    return h != -1 && h == levenshtein(s1, s2);
}

void Task2_1::shiftMiddleColumn(vector<vector<int> > &mat) {
    int n = mat.size();
    int m = mat[0].size();

    if (m % 2 == 1) {
        int mid = m / 2;
        int temp = mat[0][mid];
        for (int i = 0; i < n - 1; i++) mat[i][mid] = mat[i + 1][mid];
        mat[n - 1][mid] = temp;
    } else {
        int mid1 = m / 2 - 1, mid2 = m / 2;
        int temp1 = mat[0][mid1], temp2 = mat[0][mid2];
        for (int i = 0; i < n - 1; i++) {
            mat[i][mid1] = mat[i + 1][mid1];
            mat[i][mid2] = mat[i + 1][mid2];
        }
        mat[n - 1][mid1] = temp1;
        mat[n - 1][mid2] = temp2;
    }
}


void Task2_1::printMatrix(const vector<vector<int> > &mat) {
    for (auto &row: mat) {
        for (int x: row) cout << x << " ";
        cout << "\n";
    }
}

// 3. Функции для проектирования
void Task2_1::splitDigits(int num, vector<int> &digits) {
    if (num == 0) {
        digits.push_back(0);
        return;
    }
    while (num > 0) {
        digits.push_back(num % 10);
        num /= 10;
    }
    reverse(digits.begin(), digits.end());
}
