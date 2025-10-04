#include <iostream>
#include <cmath>
#include <string>

//Задаём структуру для замены чисел на буквы в сс >= 11
struct Data {
    std::string number, representation;
};

//Чтобы каждый раз не бегать по массиву со значениями написана отдельная функция
std::string toSystemMoreTen (int number) {
    Data fromTentoSystem[26] = { //инициализируем массив
        {"10", "A"},
        {"11", "B"},
        {"12", "C"},
        {"13", "D"},
        {"14", "E"},
        {"15", "F"},
        {"16", "G"},
        {"17", "H"},
        {"18", "I"},
        {"19", "J"},
        {"20", "K"},
        {"21", "L"},
        {"22", "M"},
        {"23", "N"},
        {"24", "O"},
        {"25", "P"},
        {"26", "Q"},
        {"27", "R"},
        {"28", "S"},
        {"29", "T"},
        {"30", "U"},
        {"31", "V"},
        {"32", "W"},
        {"33", "X"},
        {"34", "Y"},
        {"35", "Z"}
    };

//и самый простой прогон даст нужный результат
    for (int i = 0; i < 26; i++)
        if(std::to_string(number) == fromTentoSystem[i].number)
            return fromTentoSystem[i].representation;
}

//Функция для перевода в p-ю систему счисления (2 <= p <= 36)
std::string toSystemFromTen (int integer, int fraction, int p) {

    int length_fractPart = std::to_string(fraction).length(), length_intPart = std::to_string(integer).length(), number_decimalPlaces;
    std::string representation_inNumbSyst_intPart, representation_inNumbSyst_fractPart;
    bool fl_forDetermineMark = false, carry = true;

//ставим флажок на отрицательные числа
    if (integer < 0) {
        fl_forDetermineMark = true;
        integer*=-1;
    }

//в следующих 27 строках обработка вещественной части
    if(p >= 4 && p < 10) {
        number_decimalPlaces=2;
    } else {
        switch (p) {
            case 2:
                number_decimalPlaces=4;
                break;
            case 3:
                number_decimalPlaces=3;
                break;
            defult:
                number_decimalPlaces=1;
                break;
        }
    }

    for (int i = 0; i < number_decimalPlaces * length_fractPart; i++) {
        fraction *= p;
        
        if (fraction/pow(10,length_fractPart) >= 10) {
            representation_inNumbSyst_fractPart.append(toSystemMoreTen(int(fraction/pow(10,length_fractPart))));
        } else {
            representation_inNumbSyst_fractPart.append(std::to_string(int(fraction/pow(10,length_fractPart))));
        }
        
        fraction %= int(pow(10,length_fractPart));
        
        if (fraction == 0) break;
    }
//обработка целой части
    do {
        if (integer % p >= 10) { //используем функцию на тот случай когда число больше 10
            representation_inNumbSyst_intPart.insert(0, toSystemMoreTen(integer % p));
        } else { //иначе просто вставляем число
            representation_inNumbSyst_intPart.insert(0, std::to_string(integer % p));
        }

        integer /= p;
    } while (integer > 0);
    if (p == 2 && fl_forDetermineMark) {
//обрабатываем целую часть
        representation_inNumbSyst_intPart.insert(0, "0");

        while (representation_inNumbSyst_intPart.size() < 4 * length_intPart) {
            representation_inNumbSyst_intPart.insert(0, "0");
        }

        for (char &bit : representation_inNumbSyst_intPart) {
            bit = (bit == '1') ? '0' : '1';
        }

        carry = true;
        for (int i = 4 * length_intPart - 1; i >= 0; --i) {
            if (representation_inNumbSyst_intPart[i] == '1' && carry) {
                representation_inNumbSyst_intPart[i] = '0';
            } else if (representation_inNumbSyst_intPart[i] == '0' && carry) {
                representation_inNumbSyst_intPart[i] = '1';
                carry = false;
            }
        }
//обрабатываем вещественную часть
        representation_inNumbSyst_fractPart.insert(0, "0");
 
        for (char &bit : representation_inNumbSyst_fractPart) {
            bit = (bit == '1') ? '0' : '1';
        }

        carry = true;
        for (int i = number_decimalPlaces * length_intPart - 1; i >= 0; --i) {
            if (representation_inNumbSyst_fractPart[i] == '1' && carry) {
                representation_inNumbSyst_fractPart[i] = '0';
            } else if (representation_inNumbSyst_fractPart[i] == '0' && carry) {
                representation_inNumbSyst_fractPart[i] = '1';
                carry = false;
            }
        }       

        representation_inNumbSyst_intPart.append(".");
        
        return representation_inNumbSyst_intPart + representation_inNumbSyst_fractPart;
    }

    representation_inNumbSyst_intPart.append(".");

    if (fl_forDetermineMark) {
        representation_inNumbSyst_intPart.insert(0,"-");
    }

    return representation_inNumbSyst_intPart + representation_inNumbSyst_fractPart;
}

int main() {
    int integer, fraction, p;
    std::string representation_inNumbSyst_intPartem;

    std::cout << "Введите целую часть числа: ";
    std::cin >> integer;
    std::cout << "Введите дробную часть числа: ";
    std::cin >> fraction;

    std::cout << "Введите системy счисления (2 <= p <= 36): ";
    std::cin >> p;

    if (p >= 2 || p <= 36) {
        representation_inNumbSyst_intPartem = toSystemFromTen(integer, fraction ,p);
        std::cout << "Число " << integer << "." << fraction << " в " << p << "-й системе счисления: " << representation_inNumbSyst_intPartem << std::endl;
        return 0;
    } else {
        std::cout << "Введите другую систему счисления\n";
        return -1;
    }
}
