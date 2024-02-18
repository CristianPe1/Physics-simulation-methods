#include <iostream>
#include <cmath>
using namespace std;

double f(double t, double x){
    return x/2;
}

void UnPasoEuler(double & t, double & x, double dt){
    double dx;
    dx = dt*f(t,x);
    x+=dx; t+=dt;
}

int main (void){
    double t,x;
    double dt=0.01;

    for(t=0,x=0.1;t<=10;){
        //cout<<t<<""<<x<<endl;
        UnPasoEuler(t,x,dt);
    }

    cout<<x(<<""<<)x<<endl;
    cout<<x(<<""<<)<<x<<endl;

    return 0;

}
