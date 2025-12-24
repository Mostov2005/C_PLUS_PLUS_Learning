#include <windows.h>

#include <iostream>
#include "Task1.cpp"
#include "Task1_1.cpp"
#include "Task1_2.h"
#include "Task5_3.cpp"
#include "Task5_4.cpp"
#include "Task5_5.cpp"
#include "Task5_6.cpp"



int main() {
    SetConsoleOutputCP(CP_UTF8);
    // Task1 t1;
    // t1.run();

    // Task4_5 t4_5;
    // t4_5.run();

    // Task5_2 t5_2;
    // t5_2.run();
    //
    // Task5_2_smart t5_2_smart;
    // t5_2_smart.run();
    //
    // Task5_3 t5_3;
    // return t5_3.run();

    Task5_4 t5_4;
    t5_4.run();

    Task5_5 t5_5;
    t5_5.run();

    Task5_6 t5_6;
    t5_6.run();

    return 0;
}
