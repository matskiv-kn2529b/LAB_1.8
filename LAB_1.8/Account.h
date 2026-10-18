#pragma once
#pragma once
#include <string>

// Клас Account -- банківський рахунок.
// Клас Money вкладений в Account (public, бо Money потрібен і ззовні:
// суми передаються в методи рахунку і повертаються з них).
class Account
{
public:
    // ===== Вкладений клас Money =====
    class Money
    {
    private:
        long hryvnias;            // гривні (>= 0)
        unsigned char kopiyky;    // копійки (0..99)

        long long toKopiyky() const;                  // уся сума в копійках
        static Money fromKopiyky(long long total);    // сума з копійок (з перевіркою)

    public:
        Money();
        Money(long hryvnias, unsigned char kopiyky);

        // --- геттери ---
        long getHryvnias() const { return hryvnias; }
        unsigned char getKopiyky() const { return kopiyky; }

        // --- сеттери з перевіркою ---
        bool setHryvnias(long value);
        bool setKopiyky(unsigned char value);

        // --- Init / Read / Display / toString ---
        bool Init(long hryvnias, unsigned char kopiyky);
        void Read();
        void Display() const;
        std::string toString() const;      // формат "1992,28"
        double toDouble() const;

        // --- арифметика ---
        Money operator+(const Money& other) const;     // додавання
        Money operator-(const Money& other) const;     // віднімання
        double operator/(const Money& other) const;    // ділення сум (результат -- число)
        Money operator/(double divisor) const;         // ділення на дробове число
        Money operator*(double factor) const;          // множення на дробове число

        // --- порівняння ---
        bool operator==(const Money& other) const;
        bool operator!=(const Money& other) const;
        bool operator<(const Money& other) const;
        bool operator>(const Money& other) const;
        bool operator<=(const Money& other) const;
        bool operator>=(const Money& other) const;
    };

private:
    // ===== Поля Account =====
    std::string surname;         // прізвище власника
    std::string accountNumber;   // номер рахунку (цифри)
    double interestRate;         // відсоток нарахування, %
    Money balance;               // сума на рахунку (композиція)

public:
    Account();
    Account(const std::string& surname, const std::string& accountNumber,
        double interestRate, const Money& balance);

    // --- геттери ---
    std::string getSurname() const { return surname; }
    std::string getAccountNumber() const { return accountNumber; }
    double getInterestRate() const { return interestRate; }
    Money getBalance() const { return balance; }

    // --- сеттери з перевіркою ---
    bool setSurname(const std::string& value);
    bool setAccountNumber(const std::string& value);
    bool setInterestRate(double value);
    void setBalance(const Money& value);

    // --- Init / Read / Display / toString ---
    bool Init(const std::string& surname, const std::string& accountNumber,
        double interestRate, const Money& balance);   // відкриття рахунку
    void Read();
    void Display() const;
    std::string toString() const;

    // --- операції зі списку завдання ---
    bool changeOwner(const std::string& newSurname);   // змінити власника
    bool withdraw(const Money& amount);                // зняти гроші
    bool deposit(const Money& amount);                 // покласти гроші
    Money accrueInterest();                            // нарахувати відсотки
    Money toUSD(double rate) const;                    // у долари (rate -- грн за 1 USD)
    Money toEUR(double rate) const;                    // у євро (rate -- грн за 1 EUR)
    std::string amountInWords() const;                 // сума прописом
};
