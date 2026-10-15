#ifndef MODEL3_9_H
#define MODEL3_9_H

#include "Model.h"

// Model 3.9: Bounded Saturation Rate: dy/dt = b * tanh(u)
// y(t+1) = y(t) + dt * b * tanh(u(t))
class Model3_9 : public Model {
private:
    double b;
    double dt;

public:
    Model3_9(double b_val, double dt_val = 0.1, double initial_y = 0.0);
    double step(double u) override;
};

#endif // MODEL3_9_H