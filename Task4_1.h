#ifndef C__LEARNING_TASK4_1_H
#define C__LEARNING_TASK4_1_H

class Task4_1 {
public:
    void run();
};

class Cargo {
private:
    double weight;

public:
    Cargo();                  // default constructor
    Cargo(double w);           // parameterized constructor
    Cargo(const Cargo& other); // copy constructor
    Cargo(Cargo&& other) noexcept; // move constructor
    Cargo& operator=(const Cargo& other); // copy assignment
    Cargo& operator=(Cargo&& other) noexcept; // move assignment
    ~Cargo();                  // destructor

    double getWeight() const;  // только для чтения
};

#endif //C__LEARNING_TASK4_1_H
