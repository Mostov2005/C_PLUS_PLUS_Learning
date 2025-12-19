#include <iostream>
#include <stdexcept>

using namespace std;

// Односвязный список
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
    ~List() { clear(); }

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

    void pop_back() {
        if (!head) return;
        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }
        Node* cur = head;
        while (cur->next->next) cur = cur->next;
        delete cur->next;
        cur->next = nullptr;
    }

    T& back() {
        if (!head) throw runtime_error("List пуст");
        Node* cur = head;
        while (cur->next) cur = cur->next;
        return cur->value;
    }

    bool empty() const { return head == nullptr; }

    void clear() {
        Node* cur = head;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head = nullptr;
    }

    void print() const {
        Node* cur = head;
        while (cur) {
            cout << cur->value << " ";
            cur = cur->next;
        }
        cout << "\n";
    }

    Node* getHead() { return head; }
};

// Стек на основе списка
template<typename T>
class Stack {
private:
    List<T> list;

public:
    void push(const T& val) { list.push_back(val); }

    void pop() {
        if (!list.empty()) list.pop_back();
    }

    T& top() {
        return list.back();
    }

    bool empty() const {
        return list.empty();
    }

    void print() const {
        list.print();
    }

    // Вставить x после каждого y
    void insertAfterEach(const T& y, const T& x) {
        List<T> tmp;
        // переносим элементы из стека во временный список в обратном порядке
        while (!empty()) {
            tmp.push_back(top());
            pop();
        }

        // восстанавливаем стек, вставляя x после каждого y
        while (!tmp.empty()) {
            T val = tmp.back();
            tmp.pop_back();
            push(val);
            if (val == y) push(x);
        }
    }
};

class Task5_3 {
public:
    int run() {
        cout << "\n\nЗадание 5.3 Список + Стек/Очередь\n\n";
        // СТЕК
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
