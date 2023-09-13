#include <stdio.h>

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

double c_t(double t, double a, double c_isol) {
    return 1.0 + c_isol * ((1.0 - 2.0 / 5.0) * a);
}

double f(double t, double S, double E, double I, double R, double D, double alpha_E, double alpha_I, double kappa, double rho, double beta, double mu, double a, double c_isol) {
    double N = S + E + I + R + D;
    double dSdt = -c_t(t, a, c_isol) * (alpha_I * S * I / N + alpha_E * S * E / N) + (1.0 - _gamma) * R;
    double dEdt = c_t(t, a, c_isol) * (alpha_I * S * I / N + alpha_E * S * E / N) - (kappa + rho) * E;
    double dIdt = kappa * E - beta * I - mu * I;
    double dRdt = beta * I + rho * E - (1.0 - _gamma) * R;
    double dDdt = mu * I;
    return dSdt, dEdt, dIdt, dRdt, dDdt;
}

int main() {
    double t0 = 0.0, T = 90.0, h = 0.1, a = 0.0, c_isol = 0.0;
    double S = S0, E = E0, I = I0, R = R0, D = D0;
    double S_new, E_new, I_new, R_new, D_new;
    double k1_S, k1_E, k1_I, k1_R, k1_D;
    double k2_S, k2_E, k2_I, k2_R, k2_D;
    double t;

    for (t = t0; t <= T; t += h) {
        k1_S, k1_E, k1_I, k1_R, k1_D = f(t, S, E, I, R, D, alpha_E, alpha_I, kappa, rho, beta, mu, a, c_isol);
        k2_S, k2_E, k2_I, k2_R, k2_D = f(t + h / 2.0, S + h / 2.0 * k1_S, E + h / 2.0 * k1_E, I + h / 2.0 * k1_I, R + h / 2.0 * k1_R, D + h / 2.0 * k1_D, alpha_E, alpha_I, kappa, rho, beta, mu, a, c_isol);
        S_new = S + h * k2_S;
        E_new = E + h * k2_E;
        I_new = I + h * k2_I;
        R_new = R + h * k2_R;
        D_new = D + h * k2_D;
        S, E, I, R, D = S_new, E_new, I_new, R_new, D_new;
    }

    printf("S = %.2f\n", S);
    printf("E = %.2f\n", E);
    printf("I = %.2f\n", I);
    printf("R = %.2f\n", R);
    printf("D = %.2f\n", D);

    return 0;
}