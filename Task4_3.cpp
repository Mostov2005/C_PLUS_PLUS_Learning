#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Edition {
protected:
    string title;
    string author;

public:
    Edition(const string &t, const string &a) : title(t), author(a) {
    }

    virtual ~Edition() {
    }

    virtual void print() const = 0;

    virtual bool matchAuthor(const string &a) const = 0;
};

class Book : public Edition {
    int year;
    string publisher;

public:
    Book(const string &t, const string &a, int y, const string &p)
        : Edition(t, a), year(y), publisher(p) {
    }

    void print() const override {
        cout << "Книга\n";
        cout << "  Название: " << title << "\n";
        cout << "  Автор: " << author << "\n";
        cout << "  Год: " << year << "\n";
        cout << "  Издательство: " << publisher << "\n\n";
    }

    bool matchAuthor(const string &a) const override {
        return author == a;
    }
};

class Article : public Edition {
    string journal;
    int number;
    int year;

public:
    Article(const string &t, const string &a, const string &j, int n, int y)
        : Edition(t, a), journal(j), number(n), year(y) {
    }

    void print() const override {
        cout << "Статья\n";
        cout << "  Название: " << title << "\n";
        cout << "  Автор: " << author << "\n";
        cout << "  Журнал: " << journal << "\n";
        cout << "  Номер: " << number << "\n";
        cout << "  Год: " << year << "\n\n";
    }

    bool matchAuthor(const string &a) const override {
        return author == a;
    }
};

class OnlineResource : public Edition {
    string link;
    string annotation;

public:
    OnlineResource(const string &t, const string &a, const string &l, const string &ann)
        : Edition(t, a), link(l), annotation(ann) {
    }

    void print() const override {
        cout << "Онлайн-ресурс\n";
        cout << "  Название: " << title << "\n";
        cout << "  Автор: " << author << "\n";
        cout << "  Ссылка: " << link << "\n";
        cout << "  Аннотация: " << annotation << "\n\n";
    }

    bool matchAuthor(const string &a) const override {
        return author == a;
    }
};

class Task4_3 {
public:
    int run() {
        cout << "Задание 4.3 — Каталог изданий\n";

        cout <<
                "3. Создать абстрактный класс Edition с функциями, позволяющими вывести на экран информацию об издании,\n"
                "а также определить соответствие изданию критерию поиска.\n"
                "Создать производные классы:"
                "Book (название, фамилия автора, год издания, издательство),\n"
                "OnlineResource (название, фамилия автора, ссылка,аннотация).\n"
                "Создать каталог (массив) из n изданий,\n"
                "вывести полную информацию из каталога, а также организовать поиск изданий по фамилии автора.\n" <<
                endl;

        vector<Edition *> catalog;

        // Создание объектов
        catalog.push_back(new Book("Война и мир", "Tolstoy", 1000, "Эксмо"));
        catalog.push_back(new Article("Искусственный интеллект", "Ivanov", "Наука", 5, 2020));
        catalog.push_back(new OnlineResource("Программирование на языке C++ (МОАИС)", "Petrov",
                                             "https://school.sgu.ru", "Учебный материал"));

        cout << "Полный каталог:\n";
        for (auto item: catalog) item->print();

        string searchName;
        cout << "Введите фамилию автора для поиска: ";
        cin >> searchName;

        cout << "\nРезультаты поиска:";
        bool found = false;
        for (auto item: catalog) {
            if (item->matchAuthor(searchName)) {
                item->print();
                found = true;
            }
        }

        if (!found) {
            cout << "Изданий данного автора не найдено.\n";
        }

        // Очистка памяти
        for (auto item: catalog) delete item;

        return 0;
    }
};
