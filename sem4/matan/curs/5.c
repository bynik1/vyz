#include <iostream>
#include <cmath>

using namespace std;

const double alpha_E = 0.999;
const double alpha_I = 0.999;
const double kappa = 0.042;
const double rho = 0.952;
const double beta1 = 0.999;
const double mu = 0.0188;
const double c_isol = 0;
const double E0 = 99;
const double R0 = 24;

const double N0 = 2798170.0;
const double S0 = N0 - E0 - R0;
const double I0 = 0.0;
const double D0 = 0.0;

const double _gamma = 0.0;

double c(double t) {
    return 1 + c_isol * ((1 - 2 / 5) * t);
}

int main() {
    double S = S0, E = E0, I = I0, R = R0, D = D0;
    double N = S + E + I + R + D;
    double t0 = 0.00, T = 90.0;
    double h = 0.01; // размер шага
    int steps = ceil((T - t0) / h); // количество шагов
    for (int i = 0; i < steps +1; i++) {
        double t = t0 + i * h;
        double c_t = c(t);
        double dSdt = -c_t * (alpha_I * S * I / N + alpha_E * S * E / N) + _gamma * R;
        double dEdt = c_t * (alpha_I * S * I / N + alpha_E * S * E / N) - (kappa + rho) * E;
        double dIdt = kappa * E - beta1 * I - mu * I;
        double dRdt = beta1 * I + rho * E - _gamma * R;
        double dDdt = mu * I;
        double S1 = S + h * dSdt;
        double E1 = E + h * dEdt;
        double I1 = I + h * dIdt;
        double R1 = R + h * dRdt;
        double D1 = D + h * dDdt;
        double dS1dt = -c_t * (alpha_I * S1 * I1 / N + alpha_E * S1 * E1 / N) + _gamma * R1;
        double dE1dt = c_t * (alpha_I * S1 * I1 / N + alpha_E * S1 * E1 / N) - (kappa + rho) * E1;
        double dI1dt = kappa * E1 - beta1 * I1 - mu * I1;
        double dR1dt = beta1 * I1 + rho * E1 - _gamma * R1;
        double dD1dt = mu * I1;
        double deltaS = 0.5 * h * (dSdt + dS1dt);
        double deltaE = 0.5 * h * (dEdt + dE1dt);
        double deltaI = 0.5 * h * (dIdt + dI1dt);
        double deltaR = 0.5 * h * (dRdt + dR1dt);
        double deltaD = 0.5 * h * (dDdt + dD1dt);
        S += deltaS;
        E += deltaE;
        I += deltaI;
        R += deltaR;
        D += deltaD;
        N = S + E + I + R + D;
        cout << "t = " << t << ", S = " << S << ", E = " << E << ", I = " << I << ", R = " << R << ", D = " << D << endl;
    }
    return 0;
}