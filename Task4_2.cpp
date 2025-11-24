#include "Task4_2.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Инициализация статического поля
int IntArrayClass::count = 0;

// Конструктор по умолчанию
IntArrayClass::IntArrayClass() {
    IntArray = {};
    count++;
    cout << "Конструктор по умолчанию. Количество объектов: " << count << endl;
}

// Конструктор инициализации
IntArrayClass::IntArrayClass(const std::vector<int> &arr) : IntArray(arr) {
    count++;
    cout << "Конструктор инициализации. Количество объектов: " << count << endl;
}

// Деструктор
IntArrayClass::~IntArrayClass() {
    cout << "Деструктор объекта!" << endl;
    count--;
}

// Ввод элементов
void IntArrayClass::input() {
    int n, value;
    cout << "Введите количество элементов: ";
    cin >> n;
    IntArray.resize(n);
    for (int i = 0; i < n; i++) {
        cout << "Элемент " << i << ": ";
        cin >> value;
        IntArray[i] = value;
    }
}

// Вывод элементов
void IntArrayClass::output() const {
    cout << "Массив: ";
    for (int val: IntArray) cout << val << " ";
    cout << endl;
}

// Сортировка
void IntArrayClass::sortArray() {
    sort(IntArray.begin(), IntArray.end());
}

// Размер массива
size_t IntArrayClass::size() const {
    return IntArray.size();
}

// Сумма элементов
int IntArrayClass::sum() const {
    int s = 0;
    for (int val: IntArray) s += val;
    return s;
}

// Перегрузка ++ (префикс)
IntArrayClass &IntArrayClass::operator++() {
    for (int &val: IntArray) val++;
    return *this;
}

// Перегрузка -- (префикс)
IntArrayClass &IntArrayClass::operator--() {
    for (int &val: IntArray) val--;
    return *this;
}

// Перегрузка * для умножения на скаляр
IntArrayClass IntArrayClass::operator*(int scalar) const {
    IntArrayClass result(*this);
    for (int &val: result.IntArray) val *= scalar;
    return result;
}

// Статический метод
int IntArrayClass::getCount() {
    return count;
}


void Task4_2::run() {
    cout << "Задание 4.2 Класс, Вариант 8\n\n";
    cout << "8. Создать класс для работы с одномерным массивом целых чисел.\n"
            "Разработать следующие члены класса:\n"
            "1) поле int [] IntArray;\n"
            "2) функции, позволяющие: \n"
            "- ввести элементы массива с клавиатуры;\n"
            "- вывести элементы массива на экран;\n"
            " - отсортировать элементы массива в порядке возрастания;\n"
            " - узнать размерность массива;- вычислить сумму элементов в массиве.\n"
            "Кроме того, необходимо реализовать перегрузку:\n"
            " - операции ++ (--), которая позволяет одновременно увеличить (уменьшить) значение всех элементов массива на 1;\n"
            " - операции *, которая позволяет домножить все элементы массива на скаляр.\n";


    cout << "\n" << endl;

    IntArrayClass arr1; // конструктор по умолчанию
    cout << arr1.size() << endl; // Элементов 0

    arr1.input();
    arr1.output();


    IntArrayClass arr2({5, 2, 8, 1}); // конструктор инициализации
    arr2.output();

    arr2.sortArray();
    cout << "После сортировки: ";
    arr2.output();

    ++arr2;
    cout << "После ++: ";
    arr2.output();

    arr2 = arr2 * 3;
    cout << "После умножения на 3: ";
    arr2.output();

    cout << "Сумма элементов: " << arr2.sum() << endl;
    cout << "Размер массива: " << arr2.size() << endl;

    cout << "Количество объектов: " << IntArrayClass::getCount() << endl;
    IntArrayClass arr5;
    IntArrayClass arr6;
    IntArrayClass arr7;
    cout << "Количество объектов: " << IntArrayClass::getCount() << endl; // Всего объектов, а не размер массива
}
