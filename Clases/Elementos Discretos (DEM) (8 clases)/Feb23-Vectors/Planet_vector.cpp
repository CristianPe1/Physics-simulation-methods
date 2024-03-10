#include <iostream>
#include <cmath>
#include "../vector.h"
using namespace std;

const double GM=1.0;

//Deaclaración de la clase
class Cuerpo;

//Deaclaración de la interfase
class Cuerpo{
private:
  vector3D r,V,F; double m,R;
public:
  void Inicie(double x0,double y0,double z0,double Vx0,double Vy0,double Vz0,
	      double m0,double R0);
  void CalculeFuerza(void);
  void Arranque(double dt);
  void Muevase(double dt);
  double Getx(void){return r.x();}; // Inline
  double Gety(void){return r.y();}; // Inline
  void Dibujese(void);
};
//Implementación de las funciones
void Cuerpo::Inicie(double x0,double y0,double z0,double Vx0,double Vy0,double Vz0,
	      double m0,double R0){
  r.load(x0,y0,z0); V.load(Vx0,Vy0,Vz0); m=m0; R=R0;
}
void Cuerpo::CalculeFuerza(void){
  double aux = -GM * m / pow(r.norm(),3);
  F= aux*r;
}
void Cuerpo::Arranque(double dt){
  //Algoritmo de Euler
  V=-(dt/(2*m))*F;
}

void Cuerpo::Muevase(double dt){
  //Algoritmo de Euler
  r+=V*dt;  V+=F*(dt/m);
}

void Cuerpo::Dibujese(void){
  cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t)";
}

//----------- Funciones Globales -----------

void InicieAnimacion(void){
  cout<<"set terminal gif animate"<<endl;
  cout<<"set output 'Planeta.gif'"<<endl;
  cout<<"unset key"<<endl;
  cout<<"set xrange [-15:15]"<<endl;
  cout<<"set yrange [-15:15]"<<endl;
  cout<<"set size ratio -1"<<endl;
  cout<<"set parametric"<<endl;
  cout<<"set trange [0:7]"<<endl;
}

void InicieCuadro(void){
  cout<<"plot 0,0 ";
}

void TermineCuadro(void){
  cout<<endl;
}

int main(){

  double r0=10, m0 = 1;
  double omega=sqrt(GM/pow(r0,3));
  double T=2/omega;
  double V0=omega*r0;
  double t, dt=0.1 , ttotal=1.1*T;
  int Ncuadros=500; double tdibujo,tcuadro=ttotal/Ncuadros;
  Cuerpo Planeta;
  
  InicieAnimacion();

  //----------(x0,y0,z0,Vx0,Vy0,Vz0,m0 ,R0)
  Planeta.Inicie(r0,0,0,0,0.5*V0,0,0.453,1);
  
  
  for ( t = tdibujo= 0; t < ttotal; t+=dt, tdibujo+=dt) {

      if(tdibujo>tcuadro){
      InicieCuadro();
      Planeta.Dibujese();
      TermineCuadro();
      tdibujo=0;
    }
    
    
    Planeta.CalculeFuerza();
    Planeta.Muevase(dt);

  }
  return 0;
}
