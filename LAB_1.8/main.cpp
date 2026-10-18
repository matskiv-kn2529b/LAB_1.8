#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
#include "Account.h"
using namespace std;

// Money -- вкладений клас Account
typedef Account::Money Money;

static bool readInt(int& v)
{
    cin >> v;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

static bool readDouble(double& v)
{
    cin >> v;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

// ===== Демонстрація арифметики та порівнянь Money =====
void demonstrateMoney()
{
    Money a(100, 50), b(30, 25);
    cout << "\na = "; a.Display();
    cout << "b = "; b.Display();

    cout << "a + b = "; (a + b).Display();
    cout << "a - b = "; (a - b).Display();
    cout << "a / b = " << (a / b) << endl;
    cout << "a / 2.5 = "; (a / 2.5).Display();
    cout << "a * 1.5 = "; (a * 1.5).Display();

    cout << "a == b: " << (a == b) << ",  a != b: " << (a != b) << endl;
    cout << "a <  b: " << (a < b) << ",  a >  b: " << (a > b) << endl;
    cout << "a <= b: " << (a <= b) << ",  a >= b: " << (a >= b) << endl;

    cout << "\nb - a (від'ємний результат): ";
    (b - a).Display();
}

// ===== Різні способи створення об'єктів і масивів =====
void demonstrateCreation()
{
    cout << "\n1. Money: за замовчуванням, з параметрами, Init:" << endl;
    Money m1;
    Money m2(1992, 28);
    Money m3;
    m3.Init(5, 5);
    m1.Display(); m2.Display(); m3.Display();

    cout << "\n2. Account: статичний об'єкт з параметрами:" << endl;
    Account a1("Іваненко", "123456", 5, m2);
    a1.Display();

    cout << "\n3. Account: за замовчуванням і Init:" << endl;
    Account a2;
    a2.Display();
    a2.Init("Петренко", "9876543210", 3.5, Money(500, 0));
    a2.Display();

    cout << "\n4. Account: динамічний об'єкт (new):" << endl;
    Account* a3 = new Account("Коваль", "111222333", 10, Money(1000, 0));
    a3->Display();
    delete a3;

    cout << "\n5. Копіювання (Account a4 = a1):" << endl;
    Account a4 = a1;
    a4.changeOwner("Шевченко");
    a1.Display();
    a4.Display();

    cout << "\n6. Статичний масив Account arr[3]:" << endl;
    Account arr[3];
    for (int i = 0; i < 3; ++i) {
        arr[i].Init("Власник", "10000" + to_string(i + 1), i + 1, Money(100 * (i + 1), 0));
        arr[i].Display();
    }

    cout << "\n7. Динамічний масив new Account[2]:" << endl;
    Account* dyn = new Account[2];
    dyn[0].Init("Мельник", "200001", 2, Money(10, 10));
    dyn[1].Init("Бондар", "200002", 4, Money(20, 20));
    dyn[0].Display();
    dyn[1].Display();
    delete[] dyn;

    cout << "\n8. Масив Money:" << endl;
    Money ms[3] = { Money(1, 1), Money(2, 2), Money(3, 3) };
    for (int i = 0; i < 3; ++i) ms[i].Display();

    cout << "\n9. Некоректні значення в Init (замінюються на типові):" << endl;
    Account bad("123", "abc", 500, Money());
    bad.Display();
}

int main()
{
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    Account acc("Іваненко", "123456789", 5, Money(1992, 28));
    int choice = -1;

    while (choice != 0) {
        cout << "\n=============================================" << endl;
        cout << "  ЛАБ. 1.8 -- Варіант 21: Account + вкладений Money" << endl;
        cout << "=============================================" << endl;
        cout << " 1. Display / toString" << endl;
        cout << " 2. Read (ввести рахунок)" << endl;
        cout << " 3. Init (відкрити новий рахунок)" << endl;
        cout << " 4. Змінити власника" << endl;
        cout << " 5. Зняти гроші" << endl;
        cout << " 6. Покласти гроші" << endl;
        cout << " 7. Нарахувати відсотки" << endl;
        cout << " 8. Перевести в долари" << endl;
        cout << " 9. Перевести в євро" << endl;
        cout << "10. Сума прописом" << endl;
        cout << "11. Геттери і сеттери" << endl;
        cout << "12. Операції над Money" << endl;
        cout << "13. Способи створення об'єктів і масивів" << endl;
        cout << " 0. Вихід" << endl;
        cout << "Вибір: ";

        if (!readInt(choice)) {
            choice = -1;
            cout << "Невірний пункт меню!" << endl;
            continue;
        }

        string s;
        double rate;
        Money m;
        switch (choice) {
        case 1:
            acc.Display();
            cout << "toString(): " << acc.toString() << endl;
            break;
        case 2:
            acc.Read();
            break;
        case 3:
            acc.Init("Петренко", "987654321", 3.5, Money(500, 0));
            cout << "Відкрито: "; acc.Display();
            break;
        case 4:
            cout << "Нове прізвище: ";
            getline(cin >> ws, s);
            if (acc.changeOwner(s)) cout << "Власника змінено." << endl;
            break;
        case 5:
            cout << "Сума зняття:" << endl;
            m.Read();
            if (acc.withdraw(m)) { cout << "Знято. "; acc.Display(); }
            break;
        case 6:
            cout << "Сума поповнення:" << endl;
            m.Read();
            if (acc.deposit(m)) { cout << "Поповнено. "; acc.Display(); }
            break;
        case 7:
            m = acc.accrueInterest();
            cout << "Нараховано: "; m.Display();
            acc.Display();
            break;
        case 8:
            cout << "Курс (грн за 1 USD): ";
            if (readDouble(rate)) { cout << "У доларах: "; acc.toUSD(rate).Display(); }
            break;
        case 9:
            cout << "Курс (грн за 1 EUR): ";
            if (readDouble(rate)) { cout << "У євро: "; acc.toEUR(rate).Display(); }
            break;
        case 10:
            cout << acc.getBalance().toString() << " -> " << acc.amountInWords() << endl;
            break;
        case 11:
            cout << "getSurname(): " << acc.getSurname() << endl;
            cout << "getAccountNumber(): " << acc.getAccountNumber() << endl;
            cout << "getInterestRate(): " << acc.getInterestRate() << endl;
            cout << "getBalance(): " << acc.getBalance().toString() << endl;
            cout << "\nТест setSurname(\"A1\"): ";
            acc.setSurname("A1");
            cout << "Тест setAccountNumber(\"12\"): ";
            acc.setAccountNumber("12");
            cout << "Тест setInterestRate(150): ";
            acc.setInterestRate(150);
            cout << "Тест setInterestRate(7): " << (acc.setInterestRate(7) ? "Успіх" : "Невдача") << endl;
            acc.setBalance(Money(2500, 75));
            cout << "setBalance(2500,75): "; acc.Display();
            break;
        case 12:
            demonstrateMoney();
            break;
        case 13:
            demonstrateCreation();
            break;
        case 0:
            cout << "Програму завершено!" << endl;
            break;
        default:
            cout << "Невірний пункт меню!" << endl;
        }
    }
    return 0;
}
