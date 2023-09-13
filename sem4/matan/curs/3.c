#include <stdio.h>
#include <math.h>

#define dt 0.01 // шаг по времени
#define T 90 // конечное время
#define N (int)(T/dt) // количество шагов по времени
const double alpha_E = 0.999;
const double alpha_I = 0.999;
const double kappa = 0.042;
const double rho = 0.952;
const double beta = 0.999;
const double mu = 0.0188;
const double c_isol = 0;
const double E0 = 99;
const double R0 = 24;

const double N0 = 2798170.0;
const double S0 = N0 - E0 - R0;
const double I0 = 0.0;
const double D0 = 0.0;

const double _gamma = 0.0;
double c_t(double t, double a) {
    return 1 + c_isol * ((1 - 2.0 / 5) * a);
}

double S(double t, double S0, double E0, double I0, double R0, double D0, double a) {
    return S0 - c_t(t, a) * (alpha_I * S0 * I0 / N0 + alpha_E * S0 * E0 / N0) * dt;
}

double E(double t, double S0, double E0, double I0, double R0, double D0, double a) {
    return E0 + c_t(t, a) * (alpha_I * S0 * I0 / N0 + alpha_E * S0 * E0 / N0) * dt - (kappa + rho) * E0 * dt;
}

double I(double t, double S0, double E0, double I0, double R0, double D0, double a) {
    return I0 + kappa * E0 * dt - beta * I0 * dt - mu * I0 * dt;
}

double R(double t, double S0, double E0, double I0, double R0, double D0, double a) {
    return R0 + beta * I0 * dt + rho * E0 * dt - _gamma * R0 * dt;
}

double D(double t, double S0, double E0, double I0, double R0, double D0, double a) {
    return D0 + mu * I0 * dt;
}

int main() {
    double a = 0.0;
    double S_t = S(0, S0, E0, I0, R0, D0, a);
    double E_t = E(0, S0, E0, I0, R0, D0, a);
    double I_t = I(0, S0, E0, I0, R0, D0, a);
    double R_t = R(0, S0, E0, I0, R0, D0, a);
    double D_t = D(0, S0, E0, I0, R0, D0, a);

    printf("t,S,E,I,R,Dn");
    printf("0.00,%.2f,%.2f,%.2f,%.2f,%.2f\n", S_t, E_t, I_t, R_t, D_t);

    for (int i = 1; i <= N; i++) {
        double t = i * dt;
        S_t = S(t, S_t, E_t, I_t, R_t, D_t, a);
        E_t = E(t, S_t, E_t, I_t, R_t, D_t, a);
        I_t = I(t, S_t, E_t, I_t, R_t, D_t, a);
        R_t = R(t, S_t, E_t, I_t, R_t, D_t, a);
        D_t = D(t, S_t, E_t, I_t, R_t, D_t, a);

        printf("%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", t, S_t, E_t, I_t, R_t, D_t);
    }

    return 0;
}