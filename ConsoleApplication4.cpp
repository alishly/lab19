#include <iostream>
#include <windows.h>
#include "tasks.h"

using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int choice;
    do {
        cout << "\n1. Код Хемминга\n2. Код Хаффмана\n3. Шифр Цезаря\n0. Выход\nВаш выбор: ";
        cin >> choice;
        cin.ignore(1000, '\n');
        switch (choice) {
        case 1: Task1(); break;
        case 2: Task2(); break;
        case 3: Task3(); break;
        case 0: cout << "Выход.\n"; break;
        default: cout << "Ошибка выбора.\n"; break;
        }
    } while (choice != 0);
    return 0;
}