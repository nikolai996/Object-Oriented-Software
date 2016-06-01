#pragma once


/*
Класс, моделирующий рациональное число
*/
class CRational final
{
public:
    CRational(int numerator = 0, int denominator = 1);

    // Возвращает числитель
    int GetNumerator() const;

    // Возвращает знаменатель
    int GetDenominator() const;

    double ToDouble();

    //////////////////////////////////////////////////////////////////////////
    // TODO: 1. Реализовать метод ToDouble() согласно заданию
    // Возвращает отношение числителя и знаменателя в виде числа double
    // Пример использования:
    //	CRational r(3, 5)
    //	cout << r.ToDouble(); // Должно вывести 0.6
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // TODO: 2. Реализовать унарный + и унарный -
    // Указание: см. материалы к лекции
    // Пример использования:
    //	const CRational r1(3, 5);
    //	CRational r2 = -r1; // r2 должно стать -3/5
    //	assert(r2.GetNumerator(), -3);
    //	assert(r2.GetDenominator(), 5);
    //	CRational r3 = +r2; // r3 также равно -3/5
    //	assert(r3.GetNumerator(), -3);
    //	assert(r3.GetDenominator(), 5);
    // Унарный минус возвращает раицональное число без знака
    // Унарный плюс возвращает рациональное число, равное текущему
    // Реализация не должна допускать операции вроде:
    //  -someRational = someOtherRational;
    //	+someRational = someOtherRational;
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // TODO: 7. Реализовать оператор *
    // Возвращает результат произведения рациональных чисел,
    //	рационального и целого, либо целого и рационального :
    //	(1/2) * (2/3) = (1/3)
    //	(1/2) * (-3)  = (-3/2)
    //	(7*2) / 3     = (14/3)
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // TODO: 8. Реализовать оператор /
    // Возвращает частное двух рациональных чисел,
    //	рационального и целого, целого и рационального :
    //	(1/2) ⁄ (2/3) = (3/4)
    //	(1/2) ⁄ 5     = (1/10)
    //	7 ⁄ (2/3)     = (21/2)
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // TODO: 9. Реализовать оператор *=
    // Умножает значение первого рационального числа на другое рациональное,
    //	либо целое:
    //	(1/2) *= (2/3) → (1/3)
    //	(1/2) *= 3     → (3/2)
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // TODO: 10. Реализовать оператор /=
    // Делит первое рациональное число на другое рациональное,
    //	либо целое:
    //	(1/2) /= (2/3) → (3/4)
    //	(1/2) /= 3     → (1/6)
    //////////////////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////////////////
    // TODO: 13. Реализовать оператор вывода рационального числа в выходной поток
    //	std::ostream в формате <числитель>/<знаменатель>,
    //	например: 7/15
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // TODO: 14. Реализовать оператор ввода рационального числа из входного потока
    //	std::istream в формате <числитель>/<знаменатель>,
    //	например: 7/15
    //////////////////////////////////////////////////////////////////////////
    CRational &operator+=(CRational const &rational);
    CRational &operator-=(CRational const &rational);
    CRational &operator*=(CRational const &rational);
    CRational &operator/=(CRational const &rational);

private:
    int m_numerator;
    int m_denominator;

    // Нормализует рациональное число
    void Normalize();
};

inline bool const operator==(CRational const &rational1, CRational const &rational2)
{
    return ((rational1.GetNumerator() * rational2.GetDenominator()) ==
            (rational2.GetNumerator() * rational1.GetDenominator()));
}

inline bool const operator!=(CRational const &rational1, CRational const &rational2)
{
    return ((rational1.GetNumerator() * rational2.GetDenominator()) !=
            (rational2.GetNumerator() * rational1.GetDenominator()));
}

inline bool const operator<(CRational const &rational1, CRational const &rational2)
{
    return ((rational1.GetNumerator() * rational2.GetDenominator()) <
            (rational2.GetNumerator() * rational1.GetDenominator()));
}

inline bool const operator<=(CRational const &rational1, CRational const &rational2)
{
    return ((rational1.GetNumerator() * rational2.GetDenominator()) <=
            (rational2.GetNumerator() * rational1.GetDenominator()));
}

inline bool const operator>=(CRational const &rational1, CRational const &rational2)
{
    return ((rational1.GetNumerator() * rational2.GetDenominator()) >=
            (rational2.GetNumerator() * rational1.GetDenominator()));
}

inline bool const operator>(CRational const &rational1, CRational const &rational2)
{
    return ((rational1.GetNumerator() * rational2.GetDenominator()) >
            (rational2.GetNumerator() * rational1.GetDenominator()));
}

inline CRational const operator-(CRational const &rational1, CRational const &rational2)
{
    return (CRational((rational1.GetNumerator() * rational2.GetDenominator()) -
                      (rational2.GetNumerator() * rational1.GetDenominator()),
                      rational1.GetDenominator() * rational2.GetDenominator()));
}

inline CRational const operator+(CRational const &rational1, CRational const &rational2)
{
    return (CRational((rational1.GetNumerator() * rational2.GetDenominator()) +
                      (rational2.GetNumerator() * rational1.GetDenominator()),
                      rational1.GetDenominator() * rational2.GetDenominator()));
}

inline CRational const operator*(CRational const &rational1, CRational const &rational2)
{
    return (CRational(rational1.GetNumerator() * rational2.GetNumerator(), rational1.GetDenominator() * rational2.GetDenominator()));
}

inline CRational const operator/(CRational const &rational1, CRational const &rational2)
{
    return (CRational(rational1.GetNumerator() * rational2.GetDenominator(), rational1.GetDenominator() * rational2.GetNumerator()));
}

// Вычисляет наибольший общий знаменатель чисел a и b
unsigned GCD(unsigned a, unsigned b);

