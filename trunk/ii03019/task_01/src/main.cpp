#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include "InputSignal.h"
#include "Model1_1.h"
#include "Model2_5.h"
#include "Model3_9.h"

int getSafeSteps(int raw_steps) {
    constexpr int min_steps = 1;
    constexpr int max_steps = 1000;
    constexpr int default_steps = 30;

    if (raw_steps < min_steps || raw_steps > max_steps) {
        return default_steps;
    }
    return raw_steps;
}

int main(int argc, char* argv[]) {
    int parsed_steps = 30;

    if (argc > 1) {
        try {
            parsed_steps = getSafeSteps(std::stoi(argv[1]));
        } catch (...) {
            parsed_steps = 30;
        }
    } else {
        std::cout << "Enter simulation steps (default 30): ";
        std::string input;
        if (std::getline(std::cin, input) && !input.empty()) {
            std::stringstream ss(input);
            int val = 0;
            if (ss >> val) {
                parsed_steps = getSafeSteps(val);
            }
        }
    }

    const int steps = parsed_steps;

    Model1_1 model1(0.8, 0.5);
    Model2_5 model2(0.7, 0.6);
    Model3_9 model3(0.8, 0.2);

    std::ofstream out("results.csv");
    if (!out.is_open()) {
        std::cerr << "Failed to open results.csv\n";
        return 1;
    }

    out << "step,signal,u,model1,model2,model3\n";

    const std::vector signals = {
        SignalType::STEP,
        SignalType::IMPULSE,
        SignalType::HARMONIC
    };

    std::cout << "Simulation started.\n";

    for (const auto sigType : signals) {
        const std::string sigName = InputSignal::getSignalName(sigType);
        std::cout << "\n--- Signal: " << sigName << " ---\n";
        std::cout << std::setw(6) << "Step"
                  << std::setw(12) << "Input u"
                  << std::setw(14) << "Model 1.1"
                  << std::setw(14) << "Model 2.5"
                  << std::setw(14) << "Model 3.9" << "\n";

        model1.reset();
        model2.reset();
        model3.reset();

        for (int t = 0; t < steps; ++t) {
            const double u = InputSignal::getSignal(sigType, t);
            const double y1 = model1.step(u);
            const double y2 = model2.step(u);
            const double y3 = model3.step(u);

            std::cout << std::setw(6) << t
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
    std::cout << "\nResults saved to results.csv\n";
    return 0;
}