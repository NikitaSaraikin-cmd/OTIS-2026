#include <iostream>
#include <fstream>
#include <iomanip>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include "InputSignal.h"
#include "Model1_1.h"
#include "Model2_5.h"
#include "Model3_9.h"

int main(int argc, char* argv[]) {
    int steps = 30; // значение по умолчанию

    if (argc > 1) {
        // если передали аргумент командной строки
        steps = std::atoi(argv[1]);
        if (steps <= 0) steps = 30;
    } else {
        // интерактивный ввод с клавиатуры
        std::cout << "Введите количество шагов симуляции n [по умолчанию 30]: ";
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()) {
            std::stringstream ss(input);
            int parsed_steps = 0;
            if (ss >> parsed_steps && parsed_steps > 0) {
                steps = parsed_steps;
            } else {
                std::cout << "Некорректный ввод. Установлено значение по умолчанию: 30\n";
            }
        }
    }

    std::cout << "Выбрано количество шагов: " << steps << "\n";

    Model1_1 model1(0.8, 0.5);
    Model2_5 model2(0.7, 0.6);
    Model3_9 model3(0.8, 0.2);

    std::ofstream out("results.csv");
    if (!out.is_open()) {
        std::cerr << "Не удалось открыть results.csv для записи!\n";
        return 1;
    }

    out << "step,signal,u,model1,model2,model3\n";

    std::vector<SignalType> signals = {
        SignalType::STEP,
        SignalType::IMPULSE,
        SignalType::HARMONIC
    };

    std::cout << "Лабораторная работа #1. Вариант 11. Симуляция (N = " << steps << ")\n";

    for (auto sigType : signals) {
        std::string sigName = InputSignal::getSignalName(sigType);
        std::cout << "\n================ [ Вход: " << sigName << " ] ================\n";
        std::cout << std::setw(5) << "Шаг"
                  << std::setw(12) << "Вход u"
                  << std::setw(14) << "Model 1.1"
                  << std::setw(14) << "Model 2.5"
                  << std::setw(14) << "Model 3.9" << "\n";
        std::cout << std::string(59, '-') << "\n";

        model1.reset();
        model2.reset();
        model3.reset();

        for (int t = 0; t < steps; ++t) {
            double u = InputSignal::getSignal(sigType, t);
            double y1 = model1.step(u);
            double y2 = model2.step(u);
            double y3 = model3.step(u);

            std::cout << std::setw(5) << t
                      << std::fixed << std::setprecision(4)
                      << std::setw(12) << u
                      << std::setw(14) << y1
                      << std::setw(14) << y2
                      << std::setw(14) << y3 << "\n";

            out << t << "," << sigName << "," << u << ","
                << y1 << "," << y2 << "," << y3 << "\n";
        }
    }

    out.close();
    std::cout << "\n[OK] Результаты сохранены в results.csv\n";
    return 0;
}