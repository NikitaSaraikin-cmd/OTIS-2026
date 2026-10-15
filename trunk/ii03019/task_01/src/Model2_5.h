#ifndef MODEL2_5_H
#define MODEL2_5_H

#include "Model.h"

// y(t+1) = a * y(t) + b * sign(u(t)) * (1 - e^(-|u(t)|))
class Model2_5 : public Model {
private:
    double a;
    double b;
    static double sign(double val);

public:
    Model2_5(double a_val, double b_val, double initial_y = 0.0);
    double step(double u) override;
};

#endif // MODEL2_5_H