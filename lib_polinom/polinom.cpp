#include "polinom.h"

Polynom::Polynom() {}

Polynom::Polynom(const Monom& m) {
    monoms.push_back(m);
    normalize();
}

Polynom::Polynom(const Polynom& other)
    : monoms(other.monoms) {
}

Polynom::Polynom(const std::string& str) {

    std::string s = str;

    // убираем пробелы
    s.erase(remove(s.begin(), s.end(), ' '), s.end());

    int i = 0;
    while (i < (int)s.size()) {

        // определяем знак
        int sign = 1;
        if (s[i] == '+') { sign = 1; i++; }
        else if (s[i] == '-') { sign = -1; i++; }

        double coef = 0;
        bool coefSet = false;
        int px = 0, py = 0, pz = 0;

        // читаем коэффициент
        while (i < (int)s.size() && (isdigit(s[i]) || s[i] == '.')) {
            coefSet = true;
			coef = coef * 10 + (s[i] - '0'); // (s[i] - '0') преобразует символ в число
            i++;
        }

        if (!coefSet) coef = 1;
        coef *= sign;

        // читаем переменные
        while (i < (int)s.size() && s[i] != '+' && s[i] != '-') {

            if (s[i] == 'x') {
                i++;
                if (s[i] == '^') { i++; px = s[i] - '0'; i++; }
                else px = 1;
            }
            else if (s[i] == 'y') {
                i++;
                if (s[i] == '^') { i++; py = s[i] - '0'; i++; }
                else py = 1;
            }
            else if (s[i] == 'z') {
                i++;
                if (s[i] == '^') { i++; pz = s[i] - '0'; i++; }
                else pz = 1;
            }
            else i++;
        }

        monoms.push_back(Monom(coef, px, py, pz));
    }

    normalize();
}

Polynom& Polynom::operator=(const Polynom& other) {
    if (this != &other)
        monoms = other.monoms;
    return *this;
}

Polynom Polynom::operator+(const Polynom& other) const {
    Polynom res = *this;
    for (auto it = other.monoms.begin(); it != other.monoms.end(); ++it)
        res.monoms.push_back(*it);
    res.normalize();
    return res;
}

Polynom Polynom::operator-(const Polynom& other) const {
    Polynom res = *this;
    for (auto it = other.monoms.begin(); it != other.monoms.end(); ++it)
        res.monoms.push_back(-(*it));
    res.normalize();
    return res;
}

Polynom Polynom::operator*(const Polynom& other) const {
    Polynom res;
    for (auto it1 = monoms.begin(); it1 != monoms.end(); ++it1)
        for (auto it2 = other.monoms.begin(); it2 != other.monoms.end(); ++it2)
            res.monoms.push_back((*it1) * (*it2));
    res.normalize();
    return res;
}

Polynom& Polynom::operator+=(const Polynom& other) {
    for (auto it = other.monoms.begin(); it != other.monoms.end(); ++it)
        monoms.push_back(*it);
    normalize();
    return *this;
}

Polynom& Polynom::operator-=(const Polynom& other) {
    for (auto it = other.monoms.begin(); it != other.monoms.end(); ++it)
        monoms.push_back(-(*it));
    normalize();
    return *this;
}

Polynom& Polynom::operator*=(const Polynom& other) {
    Polynom tmp;

    for (auto it1 = monoms.begin(); it1 != monoms.end(); ++it1)
        for (auto it2 = other.monoms.begin(); it2 != other.monoms.end(); ++it2)
            tmp.monoms.push_back((*it1) * (*it2));

    monoms = tmp.monoms;
    normalize();
    return *this;
}

double Polynom::Calculate(double x, double y, double z) const {
    double sum = 0;
    for (auto it = monoms.begin(); it != monoms.end(); ++it)
        sum += it->Calculate(x, y, z);
    return sum;
}

void Polynom::normalize() {

    if (monoms.empty())
        return;

    // сортировка выбором
    for (auto it1 = monoms.begin(); it1 != monoms.end(); ++it1) {
        for (auto it2 = it1; it2 != monoms.end(); ++it2) {

            if (*it2 < *it1) {
                Monom tmp = *it1;
                *it1 = *it2;
                *it2 = tmp;
            }
        }
    }

    // склейка одинаковых степеней
    auto it = monoms.begin();

    while (it != monoms.end()) {

        auto next = it;
        ++next;

        if (next != monoms.end() && (*it == *next)) {
            *it += *next;
            monoms.erase(next);
        }
        else {
            ++it;
        }
    }

    // удаление нулей
    it = monoms.begin();

    while (it != monoms.end()) {

        if (it->Calculate(1, 1, 1) == 0) {
            auto del = it;
            ++it;
            monoms.erase(del);
        }
        else {
            ++it;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Polynom& p) {

    if (p.monoms.empty()) {
        os << 0;
        return os;
    }

    auto it = p.monoms.begin();

    os << *it;
    ++it;

    for (; it != p.monoms.end(); ++it) {

        if (it->Calculate(1, 1, 1) < 0)
            os << " - " << (-(*it));
        else
            os << " + " << (*it);
    }

    return os;
}

void Polynom::addMonom(const Monom& m) {
    monoms.push_back(m);
    normalize();
}

bool Polynom::operator==(const Polynom& other) const {

    if (monoms.size() != other.monoms.size())
        return false;

    auto it1 = monoms.begin();
    auto it2 = other.monoms.begin();

    while (it1 != monoms.end()) {
        if (!(*it1 == *it2))
            return false;

        ++it1;
        ++it2;
    }

    return true;
}

bool Polynom::operator!=(const Polynom& other) const {
    return !(*this == other);
}