#include <iostream>
#include <cmath>
#include <vector>

double f(double t, double x, int n) {
    return cos(n * t - x * sin(t));
}

double IntegralPorSimpson(double a, double b, int nsteps, double x, int n) {
    nsteps *= 2;
    double h = (b - a) / nsteps;
    double suma = 0;

    for (int i = 0; i <= nsteps; ++i) {
        double t = a + i * h;
        if (i == 0 || i == nsteps) {
            suma += f(t, x, n);
        } else if (i % 2 == 0) {
            suma += 2 * f(t, x, n);
        } else {
            suma += 4 * f(t, x, n);
        }
    }

    return suma * h / 3;
}

double Bessel(int n, double x) {
    return (1 / M_PI) * IntegralPorSimpson(0, M_PI, 100, x, n);
}

int main() {
    int n = 3;
    double a = 0;
    double b = 10;
    int Nsteps = 100;
    double dx = (b - a) / Nsteps;

    std::vector<double> xdata(Nsteps);
    std::vector<double> ydata(Nsteps);

    for (int i = 0; i < Nsteps; ++i) {
        double x = a + i * dx;
        xdata[i] = x;
        ydata[i] = Bessel(n, x);
    }

    for (int i = 0; i < Nsteps; ++i) {
        std::cout << xdata[i] << "\t" << ydata[i] << std::endl;
    }

    return 0;
}
