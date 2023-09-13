#include <stdio.h>
#include <math.h>
#include <xlsxwriter.h>

#define t0 0.0
#define T 90.0
#define dt 0.01
#define num_steps ((int) ((T - t0) / dt))

double a = 1.0;

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

double c() {
    return 1.0 + c_isol * ((1.0 - 2.0 / 5.0) * a);
}

double dSdt(double S, double E, double I, double R, double N) {
    return -c() * (alpha_I * S * I / N + alpha_E * S * E / N) + _gamma * R;
}

double dEdt(double S, double E, double I, double N) {
    return c() * (alpha_I * S * I / N + alpha_E * S * E / N) - (kappa + rho) * E;
}

double dIdt(double E, double I) {
    return kappa * E - beta * I - mu * I;
}

double dRdt(double E, double I, double R) {
    return beta * I + rho * E - _gamma * R;
}

double dDdt(double I) {
    return mu * I;
}

int eler(double *S, double* E, double* I, double* R, double* D, double *t){
    S[0] = N0 - E0 - R0;
    E[0] = E0;
    I[0] = I0;
    R[0] = R0;
    D[0] = D0;
    t[0] = t0;

    for (int i = 0; i < num_steps; i++) {
        double N = S[i] + E[i] + I[i] + R[i] + D[i];
        double dS = dSdt(S[i], E[i], I[i], R[i], N);
        double dE = dEdt(S[i], E[i], I[i], N);
        double dI = dIdt(E[i], I[i]);
        double dR = dRdt(E[i], I[i], R[i]);
        double dD = dDdt(I[i]);

        S[i + 1] = S[i] + dt * dS;
        E[i + 1] = E[i] + dt * dE;
        I[i + 1] = I[i] + dt * dI;
        R[i + 1] = R[i] + dt * dR;
        D[i + 1] = D[i] + dt * dD;
        t[i + 1] = t[i] + dt;

        double dS1 = dSdt(S[i+1], E[i+1], I[i+1], R[i+1], N);
        double dE1 = dEdt(S[i+1], E[i+1], I[i+1], N);
        double dI1 = dIdt(E[i+1], I[i+1]);
        double dR1 = dRdt(E[i+1], I[i+1], R[i+1]);
        double dD1 = dDdt(I[i+1]);

        double deltaS = 0.5 * dt * (dS + dS1);
        double deltaE = 0.5 * dt * (dE + dE1);
        double deltaI = 0.5 * dt * (dI + dI1);
        double deltaR = 0.5 * dt * (dR + dR1);
        double deltaD = 0.5 * dt * (dD + dD1);
        S[i] += deltaS;
        E[i] += deltaE;
        I[i] += deltaI;
        R[i] += deltaR;
        D[i] += deltaD;
    }

    return 0;
}

int print_res(double *S, double* E, double* I, double* R, double* D, double *t, lxw_worksheet *worksheet){
    int o = 0;
    printf("t,S,E,I,R,D\n");

    for (int i = 0; i < num_steps + 1; i++) {
        if(i % 100 == 0){
            o++;
            worksheet_write_number(worksheet, o, 0, t[i], NULL);
            worksheet_write_number(worksheet, o, 1, S[i], NULL);
            worksheet_write_number(worksheet, o, 2, E[i], NULL);
            worksheet_write_number(worksheet, o, 3, I[i], NULL);
            worksheet_write_number(worksheet, o, 4, R[i], NULL);
            worksheet_write_number(worksheet, o, 5, D[i], NULL);
        }
        printf("%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", t[i], S[i], E[i], I[i], R[i], D[i]);
    }

    return 0;
}

int main() {
    double S[num_steps + 1], E[num_steps + 1], I[num_steps + 1], R[num_steps + 1], D[num_steps + 1];
    double t[num_steps + 1]; 

    // Создаем новый файл Excel
    lxw_workbook *workbook = workbook_new("table.xlsx");

    // Создаем новый лист
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);

    // Задаем заголовки столбцов
    worksheet_write_string(worksheet, 0, 0, "t", NULL);
    worksheet_write_string(worksheet, 0, 1, "S", NULL);
    worksheet_write_string(worksheet, 0, 2, "E", NULL);
    worksheet_write_string(worksheet, 0, 3, "I", NULL);
    worksheet_write_string(worksheet, 0, 4, "R", NULL);
    worksheet_write_string(worksheet, 0, 5, "D", NULL);

    eler(S, E, I, R, D, t);
    print_res(S, E, I, R, D, t, worksheet);
    // Сохраняем файл Excel
    workbook_close(workbook);

    return 0;
}