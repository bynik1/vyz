#include <stdio.h>
#include <math.h>

double alpha_E = 0.999;
double alpha_I = 0.999;
double kappa = 0.042;
double rho = 0.952;
double beta = 0.999;
double mu = 0.0188;
double c_isol = 0;
const double E0 = 99;
const double R0 = 24;

const double N0 = 2798170.0;
double S0 = N0 - E0 - R0;
double I0 = 0.0;
double D0 = 0.0;

double _gamma = 0.0;

double c_t(double t)
{
    double a = 0.0;
    if (t >= 0 && t <= 30)
    {
        a = 0.4;
    }
    else if (t > 30 && t <= 60)
    {
        a = 0.2;
    }
    else if (t > 60 && t <= 90)
    {
        a = 0.1;
    }
    return 1 + c_isol * ((1 - 2 / 5) * a);
}

void euler_cromer(double h)
{
    double t = 0.0, tf = 90.0;

    double S = S0, E = E0, I = I0, R = R0, D = D0;
    double dSdt, dEdt, dIdt, dRdt, dDdt;

    FILE *fp = fopen("seird.csv", "w+");
    fprintf(fp, "t,S,E,I,R,Dn");

    while (t <= tf)
    {
        dSdt = -c_t(t) * (alpha_I * S * I / N0 + alpha_E * S * E / N0) + _gamma * R;
        dEdt = c_t(t) * (alpha_I * S * I / N0 + alpha_E * S * E / N0) - (kappa + rho) * E;
        dIdt = kappa * E - beta * I - mu * I;
        dRdt = beta * I + rho * E - _gamma * R;
        dDdt = mu * I;

        S = S + h * dSdt;
        E = E + h * dEdt;
        I = I + h * dIdt;
        R = R + h * dRdt;
        D = D + h * dDdt;

        printf("%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", t, S, E, I, R, D);
        t += h;
    }
    fclose(fp);
}

int main()
{
    double h = 0.01;
    euler_cromer(h);
    return 0;
}