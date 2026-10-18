#include "pch.h"
#include "CppUnitTest.h"

#include "C:\Users\Mackiv\source\repos\LAB_1.8\LAB_1.8\Account.h"
#include "C:\Users\Mackiv\source\repos\LAB_1.8\LAB_1.8\Account.cpp"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLAB18
{
	// Money -- вкладений клас Account
	typedef Account::Money Money;

	// ===================== Money =====================
	TEST_CLASS(MoneyTests)
	{
	public:

		// Тест 1: конструктор за замовчуванням і з параметрами
		TEST_METHOD(TestConstructors)
		{
			Money a;
			Assert::AreEqual(std::string("0,00"), a.toString());
			Money b(1992, 28);
			Assert::AreEqual(std::string("1992,28"), b.toString());
			Assert::AreEqual(1992, (int)b.getHryvnias());
			Assert::AreEqual(28, (int)b.getKopiyky());
		}

		// Тест 2: Init (коректні і некоректні значення)
		TEST_METHOD(TestInit)
		{
			Money m;
			Assert::IsTrue(m.Init(10, 5));
			Assert::AreEqual(std::string("10,05"), m.toString());

			Assert::IsFalse(m.Init(-1, 5));
			Assert::AreEqual(std::string("0,00"), m.toString());
			Assert::IsFalse(m.Init(5, 100));
			Assert::AreEqual(std::string("0,00"), m.toString());
		}

		// Тест 3: сеттери з перевіркою
		TEST_METHOD(TestSetters)
		{
			Money m(7, 7);
			Assert::IsFalse(m.setHryvnias(-5));
			Assert::IsFalse(m.setKopiyky(100));
			Assert::AreEqual(7, (int)m.getHryvnias());
			Assert::AreEqual(7, (int)m.getKopiyky());
			Assert::IsTrue(m.setHryvnias(50));
			Assert::IsTrue(m.setKopiyky(99));
			Assert::AreEqual(std::string("50,99"), m.toString());
		}

		// Тест 4: toString -- кома і дві цифри копійок
		TEST_METHOD(TestToString)
		{
			Assert::AreEqual(std::string("5,05"), Money(5, 5).toString());
			Assert::AreEqual(std::string("0,99"), Money(0, 99).toString());
			Assert::AreEqual(std::string("100,00"), Money(100, 0).toString());
		}

		// Тест 5: додавання (з переносом копійок у гривні)
		TEST_METHOD(TestAdd)
		{
			Assert::AreEqual(std::string("4,20"), (Money(1, 70) + Money(2, 50)).toString());
			Assert::AreEqual(std::string("10,00"), (Money(9, 99) + Money(0, 1)).toString());
		}

		// Тест 6: віднімання, у тому числі з "позичанням" гривні
		TEST_METHOD(TestSubtract)
		{
			Assert::AreEqual(std::string("0,75"), (Money(1, 25) - Money(0, 50)).toString());
			Assert::AreEqual(std::string("0,00"), (Money(5, 0) - Money(5, 0)).toString());
			// від'ємний результат неможливий -> 0,00
			Assert::AreEqual(std::string("0,00"), (Money(1, 0) - Money(2, 0)).toString());
		}

		// Тест 7: ділення сум
		TEST_METHOD(TestDivideMoney)
		{
			Assert::AreEqual(2.5, Money(10, 0) / Money(4, 0), 1e-9);
			Assert::AreEqual(0.0, Money(10, 0) / Money(0, 0), 1e-9);   // ділення на нуль
		}

		// Тест 8: ділення на дробове число
		TEST_METHOD(TestDivideDouble)
		{
			Assert::AreEqual(std::string("2,50"), (Money(10, 0) / 4.0).toString());
			Assert::AreEqual(std::string("4,00"), (Money(10, 0) / 2.5).toString());
			Assert::AreEqual(std::string("0,00"), (Money(10, 0) / 0.0).toString());
			Assert::AreEqual(std::string("0,00"), (Money(10, 0) / -2.0).toString());
		}

		// Тест 9: множення на дробове число
		TEST_METHOD(TestMultiply)
		{
			Assert::AreEqual(std::string("15,75"), (Money(10, 50) * 1.5).toString());
			Assert::AreEqual(std::string("0,00"), (Money(10, 50) * 0.0).toString());
			Assert::AreEqual(std::string("0,00"), (Money(10, 50) * -1.0).toString());
		}

		// Тест 10: порівняння
		TEST_METHOD(TestComparison)
		{
			Money a(10, 50), b(10, 51), c(10, 50);
			Assert::IsTrue(a == c);
			Assert::IsFalse(a == b);
			Assert::IsTrue(a != b);
			Assert::IsTrue(a < b);
			Assert::IsTrue(b > a);
			Assert::IsTrue(a <= c);
			Assert::IsTrue(a >= c);
			Assert::IsFalse(b <= a);
			Assert::IsTrue(Money(11, 0) > Money(10, 99));   // гривні важливіші за копійки
		}
	};

	// ===================== Account =====================
	TEST_CLASS(AccountTests)
	{
	public:

		// Тест 11: конструктор за замовчуванням і з параметрами
		TEST_METHOD(TestConstructors)
		{
			Account d;
			Assert::AreEqual(std::string("Unknown"), d.getSurname());
			Assert::AreEqual(std::string("0,00"), d.getBalance().toString());

			Account a("Ivanenko", "123456", 5, Money(1992, 28));
			Assert::AreEqual(std::string("Ivanenko"), a.getSurname());
			Assert::AreEqual(std::string("123456"), a.getAccountNumber());
			Assert::AreEqual(5.0, a.getInterestRate(), 1e-9);
			Assert::AreEqual(std::string("1992,28"), a.getBalance().toString());
		}

		// Тест 12: Init -- відкриття рахунку; некоректні дані замінюються типовими
		TEST_METHOD(TestInit)
		{
			Account a;
			Assert::IsTrue(a.Init("Petrenko", "9876543210", 3.5, Money(500, 0)));
			Assert::AreEqual(std::string("Petrenko"), a.getSurname());

			Assert::IsFalse(a.Init("123", "abc", 500, Money(1, 1)));
			Assert::AreEqual(std::string("Unknown"), a.getSurname());
			Assert::AreEqual(std::string("000000"), a.getAccountNumber());
			Assert::AreEqual(0.0, a.getInterestRate(), 1e-9);
		}

		// Тест 13: сеттери з перевіркою
		TEST_METHOD(TestSetters)
		{
			Account a("Koval", "123456", 5, Money(10, 0));

			Assert::IsFalse(a.setSurname(""));
			Assert::IsFalse(a.setSurname("A1"));
			Assert::IsTrue(a.setSurname("Melnyk"));

			Assert::IsFalse(a.setAccountNumber("12345"));      // закороткий
			Assert::IsFalse(a.setAccountNumber("12345a"));     // не цифри
			Assert::IsTrue(a.setAccountNumber("654321"));

			Assert::IsFalse(a.setInterestRate(-1));
			Assert::IsFalse(a.setInterestRate(101));
			Assert::AreEqual(5.0, a.getInterestRate(), 1e-9);
			Assert::IsTrue(a.setInterestRate(7.5));

			a.setBalance(Money(33, 3));
			Assert::AreEqual(std::string("33,03"), a.getBalance().toString());
		}

		// Тест 14: зміна власника
		TEST_METHOD(TestChangeOwner)
		{
			Account a("Koval", "123456", 5, Money(10, 0));
			Assert::IsTrue(a.changeOwner("Shevchenko"));
			Assert::AreEqual(std::string("Shevchenko"), a.getSurname());
			Assert::IsFalse(a.changeOwner("12"));
			Assert::AreEqual(std::string("Shevchenko"), a.getSurname());
		}

		// Тест 15: покласти гроші
		TEST_METHOD(TestDeposit)
		{
			Account a("Koval", "123456", 5, Money(100, 50));
			Assert::IsTrue(a.deposit(Money(50, 75)));
			Assert::AreEqual(std::string("151,25"), a.getBalance().toString());
			Assert::IsFalse(a.deposit(Money(0, 0)));           // нульова сума
			Assert::AreEqual(std::string("151,25"), a.getBalance().toString());
		}

		// Тест 16: зняти гроші
		TEST_METHOD(TestWithdraw)
		{
			Account a("Koval", "123456", 5, Money(100, 0));
			Assert::IsTrue(a.withdraw(Money(40, 50)));
			Assert::AreEqual(std::string("59,50"), a.getBalance().toString());

			Assert::IsFalse(a.withdraw(Money(1000, 0)));       // недостатньо коштів
			Assert::IsFalse(a.withdraw(Money(0, 0)));          // нульова сума
			Assert::AreEqual(std::string("59,50"), a.getBalance().toString());

			Assert::IsTrue(a.withdraw(Money(59, 50)));         // рівно весь залишок
			Assert::AreEqual(std::string("0,00"), a.getBalance().toString());
		}

		// Тест 17: нарахування відсотків
		TEST_METHOD(TestAccrueInterest)
		{
			Account a("Koval", "123456", 10, Money(1000, 0));
			Money interest = a.accrueInterest();
			Assert::AreEqual(std::string("100,00"), interest.toString());
			Assert::AreEqual(std::string("1100,00"), a.getBalance().toString());

			Account z("Koval", "123456", 0, Money(1000, 0));   // 0% -- нічого не нараховується
			Assert::AreEqual(std::string("0,00"), z.accrueInterest().toString());
			Assert::AreEqual(std::string("1000,00"), z.getBalance().toString());
		}

		// Тест 18: переведення в долари та євро
		TEST_METHOD(TestCurrencyConversion)
		{
			Account a("Koval", "123456", 5, Money(4150, 0));
			Assert::AreEqual(std::string("100,00"), a.toUSD(41.5).toString());

			Account b("Koval", "123456", 5, Money(4500, 0));
			Assert::AreEqual(std::string("100,00"), b.toEUR(45.0).toString());

			Assert::AreEqual(std::string("0,00"), a.toUSD(0).toString());    // некоректний курс
			Assert::AreEqual(std::string("0,00"), b.toEUR(-3).toString());
			// сума на рахунку при конвертації не змінюється
			Assert::AreEqual(std::string("4150,00"), a.getBalance().toString());
		}

		// Тест 19: сума прописом
		TEST_METHOD(TestAmountInWords)
		{
			Account a("Koval", "123456", 5, Money(1992, 28));
			Assert::AreEqual(std::string("одна тисяча дев'ятсот дев'яносто дві грн. 28 коп."),
				a.amountInWords());

			a.setBalance(Money(0, 5));
			Assert::AreEqual(std::string("нуль грн. 05 коп."), a.amountInWords());

			a.setBalance(Money(1, 0));
			Assert::AreEqual(std::string("одна грн. 00 коп."), a.amountInWords());

			a.setBalance(Money(21, 0));
			Assert::AreEqual(std::string("двадцять одна грн. 00 коп."), a.amountInWords());

			a.setBalance(Money(2000, 0));
			Assert::AreEqual(std::string("дві тисячі грн. 00 коп."), a.amountInWords());

			a.setBalance(Money(11000, 0));
			Assert::AreEqual(std::string("одинадцять тисяч грн. 00 коп."), a.amountInWords());

			a.setBalance(Money(1000000, 0));
			Assert::AreEqual(std::string("один мільйон грн. 00 коп."), a.amountInWords());

			a.setBalance(Money(2500000, 99));
			Assert::AreEqual(std::string("два мільйони п'ятсот тисяч грн. 99 коп."), a.amountInWords());
		}

		// Тест 20: toString рахунку
		TEST_METHOD(TestToString)
		{
			Account a("Koval", "123456", 5, Money(10, 5));
			std::string s = a.toString();
			Assert::IsTrue(s.find("Koval") != std::string::npos);
			Assert::IsTrue(s.find("123456") != std::string::npos);
			Assert::IsTrue(s.find("10,05") != std::string::npos);
		}

		// Тест 21: копіювання і масиви об'єктів
		TEST_METHOD(TestCopyAndArrays)
		{
			Account a("Koval", "123456", 5, Money(10, 0));
			Account b = a;
			b.changeOwner("Bondar");
			Assert::AreEqual(std::string("Koval"), a.getSurname());
			Assert::AreEqual(std::string("Bondar"), b.getSurname());

			Account arr[3];
			arr[1].Init("Melnyk", "222222", 2, Money(5, 5));
			Assert::AreEqual(std::string("Unknown"), arr[0].getSurname());
			Assert::AreEqual(std::string("Melnyk"), arr[1].getSurname());

			Account* dyn = new Account[2];
			dyn[0].Init("Hryhorenko", "333333", 1, Money(1, 1));
			Assert::AreEqual(std::string("Hryhorenko"), dyn[0].getSurname());
			delete[] dyn;
		}
	};
}
