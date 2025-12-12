#include <iostream>

using namespace std;

// ================= Односвязный список =================
template<typename T>
class List {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& val) : value(val), next(nullptr) {}
    };
    Node* head;

public:
    List() : head(nullptr) {}
    ~List() {
        clear();
    }

    // Добавление в конец
    void push_back(const T& val) {
        Node* node = new Node(val);
        if (!head) {
            head = node;
        } else {
            Node* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = node;
        }
    }

    // Очистка
    void clear() {
        Node* cur = head;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head = nullptr;
    }

    // Пройтись и показать
    void print() const {
        Node* cur = head;
        while (cur) {
            cout << cur->value << " ";
            cur = cur->next;
        }
        cout << "\n";
    }

    // Вставить элемент x после каждого y
    void insertAfterEach(const T& y, const T& x) {
        Node* cur = head;
        while (cur) {
            if (cur->value == y) {
                Node* node = new Node(x);
                node->next = cur->next;
                cur->next = node;
                cur = node->next; // пропустить вставленный
            } else {
                cur = cur->next;
            }
        }
    }

    // Доступ к голове
    Node* getHead() { return head; }
};

// ================= Стек на основе списка =================
template<typename T>
class Stack {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& val, Node* nxt) : value(val), next(nxt) {}
    };
    Node* topNode;

public:
    Stack() : topNode(nullptr) {}
    ~Stack() {
        while (!empty()) pop();
    }

    void push(const T& val) {
        topNode = new Node(val, topNode);
    }

    void pop() {
        if (!topNode) return;
        Node* tmp = topNode;
        topNode = topNode->next;
        delete tmp;
    }

    T& top() { return topNode->value; }
    bool empty() const { return topNode == nullptr; }

    // Вставить x после каждого y (внешняя функция)
    void insertAfterEach(const T& y, const T& x) {
        Stack<T> tmpStack;

        // Переносим элементы во временный стек
        while (!empty()) {
            T val = top();
            pop();
            tmpStack.push(val);
        }

        // Восстанавливаем стек с вставкой
        while (!tmpStack.empty()) {
            T val = tmpStack.top();
            tmpStack.pop();
            push(val);
            if (val == y) push(x);
        }
    }

    // Печать (для демонстрации)
    void print() {
        Stack<T> tmpStack;
        while (!empty()) {
            T val = top();
            pop();
            tmpStack.push(val);
        }

        while (!tmpStack.empty()) {
            T val = tmpStack.top();
            tmpStack.pop();
            cout << val << " ";
            push(val);
        }
        cout << "\n";
    }
};

class Task5_3 {
public:
    int run() {
        cout << "Задание 5.3 — Список + Стек/Очередь\n\n";

        // --- Демонстрация списка ---
        List<int> lst;
        lst.push_back(1);
        lst.push_back(2);
        lst.push_back(3);
        lst.push_back(2);

        cout << "Список до вставки: ";
        lst.print();

        lst.insertAfterEach(2, 99);

        cout << "Список после вставки 99 после каждого 2: ";
        lst.print();

        // --- Демонстрация стека ---
        Stack<int> st;
        st.push(1);
        st.push(2);
        st.push(3);
        st.push(2);

        cout << "\nСтек до вставки: ";
        st.print();

        st.insertAfterEach(2, 99);

        cout << "Стек после вставки 99 после каждого 2: ";
        st.print();

        return 0;
    }
};
