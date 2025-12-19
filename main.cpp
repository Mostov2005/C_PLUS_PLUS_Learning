#include <windows.h>

#include <iostream>
#include "Task1.cpp"
#include "Task1_1.cpp"
#include "Task1_2.h"
#include "Task2_1.h"
#include "Task2_3.h"
#include "Task2_4.h"
#include "Task3_3.h"
#include "Task4_1.h"
#include "Task4_2.h"
#include "Task4_3.cpp"
#include "Task4_4.cpp"
#include "Task4_5.cpp"
#include "Task5_2.cpp"
#include "Task5_2_smart.cpp"
#include "Task5_3.cpp"



int main() {
    SetConsoleOutputCP(CP_UTF8);
    // Task1 t1;
    // t1.run();


    // Task4_5 t4_5;
    // t4_5.run();

    Task5_2 t5_2;
    t5_2.run();

    Task5_2_smart t5_2_smart;
    t5_2_smart.run();

    Task5_3 t5_3;
    return t5_3.run();

    return 0;
}
