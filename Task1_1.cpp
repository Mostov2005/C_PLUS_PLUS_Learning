#include <iostream>
#include <limits>
#include <string>
using namespace std;

class Task1_1 {
public:
    void run() {
        cout << "Задание 1.1 - Изучите внутреннее устройство и характеристики базовых типов данных\n" << endl;

        // 1. Целочисленные типы
        cout << "1. Целочисленные типы:\n";
        cout << "char: size = " << sizeof(char)
                << ", min = " << int(numeric_limits<char>::min())
                << ", max = " << int(numeric_limits<char>::max()) << "\n";

        cout << "unsigned char: size = " << sizeof(unsigned char)
                << ", min = " << int(numeric_limits<unsigned char>::min())
                << ", max = " << int(numeric_limits<unsigned char>::max()) << "\n";

        cout << "int: size = " << sizeof(int)
                << ", min = " << numeric_limits<int>::min()
                << ", max = " << numeric_limits<int>::max() << "\n";

        cout << "unsigned int: size = " << sizeof(unsigned int)
                << ", min = " << numeric_limits<unsigned int>::min()
                << ", max = " << numeric_limits<unsigned int>::max() << "\n";

        cout << "\n" << endl;

        // Переполнение
        unsigned int u = numeric_limits<unsigned int>::max();
        cout << "unsigned int переполнение: " << u << " + 1 = " << (u + 1) << "\n";

        int s = numeric_limits<int>::max();
        cout << "int переполнение: " << s << " + 1 = " << (s + 1) << "\n\n";

        // 2. Вещественные типы
        cout << "2. Вещественные типы:\n";
        cout << "float: size = " << sizeof(float)
                << ", min = " << numeric_limits<float>::min()
                << ", max = " << numeric_limits<float>::max()
                << ", точность = " << numeric_limits<float>::digits10 << " цифр\n";
        cout << "double: size = " << sizeof(double)
                << ", min = " << numeric_limits<double>::min()
                << ", max = " << numeric_limits<double>::max()
                << ", точность = " << numeric_limits<double>::digits10 << " цифр\n\n";

        // 3. Булев тип
        cout << "bool: size = " << sizeof(bool)
                << ", значения = {false, true}\n\n";

        // 4. Символы и строки
        char c = 'A';
        unsigned char uc = 255;
        cout << "char: '" << c << "' -> unt = " << int(c) << "\n";
        cout << "unsigned char: " << int(uc) << "\n";

        string str = "Hello";
        cout << "std::string: \"" << str << "\", длина = " << str.size()
                << ", capacity = " << str.capacity()
                << ", адрес в памяти = " << static_cast<const void *>(str.c_str()) << "\n";
    }
};
