
#include <iostream>
#include <cmath>
using namespace std;

const double g=9.8;

//Deaclaración de la clase
class Objeto;

//Deaclaración de la interfase
class Objeto{
private:
  double x,y,Vx,Vy,Fx,Fy,m,R;
public:
  void Inicie(double x0,double y0,double Vx0,double Vy0,double m0,double R0);
  void CalculeFuerza(void);
  void Muevase(double dt);
  double Getx(void){return x;}; // Inline
  double Gety(void){return y;}; // Inline
};
//Implementación de las funciones
void Objeto::Inicie(double x0,double y0,double Vx0,double Vy0,double m0,double R0){
  x=x0; y=y0; Vx=Vx0; Vy=Vy0; m=m0; R=R0;
}
void Objeto::CalculeFuerza(void){
  Fx=0; Fy=-m*g;
}
void Objeto::Muevase(double dt){
  //Algoritmo de Euler
  x+=Vx*dt;      y+=Vy*dt;
  Vx+=Fx*dt/m;  Vy+=Fy*dt/m;
}

//----------- Funciones Globales -----------

int main(){
  double t,dt=0.01,ttotal=2.5;
  Objeto Balon;


  //----------(x0,y0,Vx0,Vy0,m0   ,R0)
  Balon.Inicie( 0, 0, 16,  9,0.453,1.0);
  for(t=0;t<ttotal;t+=dt){
      //cout<<Balon.Getx()<<" "<<Balon.Gety()<<endl;
    Balon.CalculeFuerza();
    Balon.Muevase(dt);

  }
  return 0;
}
