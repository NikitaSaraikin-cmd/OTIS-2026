#ifndef MODEL1_1_H
#define MODEL1_1_H

#include "Model.h"

// Model 1.1: Standard First-Order Inertial System: y(t+1) = a * y(t) + b * u(t)
class Model1_1 : public Model {
private:
    double a;
    double b;

public:
    Model1_1(double a_val, double b_val, double initial_y = 0.0);
    double step(double u) override;
};

#endif