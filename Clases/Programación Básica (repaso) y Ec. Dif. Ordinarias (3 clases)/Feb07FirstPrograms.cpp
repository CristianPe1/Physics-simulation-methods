#include <iostream>
#include <cmath>

using namespace std;

double funcion(double x) {
    // La función para la cual buscamos la raíz
    return x * x - 16;
}

double metodoBiseccion(double a, double b, double tolerancia) {
    double c; // Punto medio del intervalo
    int iteraciones = 0;

    // Verificar si hay cambio de signo en los extremos
    if (funcion(a) * funcion(b) >= 0) {
        cout << "El método de la bisección no es aplicable en este intervalo." << endl;
        return 0.0;
    }

    // Iterar hasta alcanzar la tolerancia deseada
    do {
        // Calcular el punto medio del intervalo
        c = (a + b) / 2;

        // Verificar el cambio de signo en el intervalo izquierdo o derecho
        if (funcion(c) == 0.0) {
            break;
        } else if (funcion(c) * funcion(a) < 0) {
            b = c;
        } else {
            a = c;
        }

        // Incrementar el contador de iteraciones
        iteraciones++;

    } while (fabs(funcion(c)) > tolerancia && iteraciones < 1000);

    cout << "Número de iteraciones: " << iteraciones << endl;

    return c;
}

int main() {
    double a = 0.0;
    double b = 5.0;
    double tolerancia = 0.0001;

    double raizAproximada = metodoBiseccion(a, b, tolerancia);

    cout << "Aproximación de la raíz: " << raizAproximada << endl;

    return 0;
}