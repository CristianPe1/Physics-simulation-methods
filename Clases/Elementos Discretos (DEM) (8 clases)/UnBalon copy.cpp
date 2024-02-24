
#include <iostream>
#include "vector.h"
using namespace std;

const double g=9.8;

//Deaclaración de la clase
class Objeto;

//Deaclaración de la interfase
class Objeto{
private:
  vector3D r,V,F double m,R;
public:
  void Inicie(double x0,double y0, double z0,double Vx0,double Vy0, double Vz0
  double m0,double R0);
  void CalculeFuerza(void);
  void Muevase(double dt);
  void Dibujese(void);
  double Getx(void){return r.x();}; // Inline
  double Gety(void){return r.y();}; // Inline
};
//Implementación de las funciones
void Objeto::Inicie(double x0,double y0,double Vx0,double Vy0,double m0,double R0){
  r.load(x0,y0,z0); V.laod(Vx0,Vy0,Vz0); m=m0; R=R0;
}
void Objeto::CalculeFuerza(void){
  F.load(0,-m*g,0);
}
void Objeto::Muevase(double dt){
  //Algoritmo de Euler
  r+=V*dt;      V+=F*dt/m;
}
void Objeto::Dibujese(void){
  cout<<" , "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t)";
  //cout<<" , "<<x0<<"+"<<l/7<<"*t*sin("<<theta<<"),-"<<l/7<<"*t*cos("<<theta<<")";
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
