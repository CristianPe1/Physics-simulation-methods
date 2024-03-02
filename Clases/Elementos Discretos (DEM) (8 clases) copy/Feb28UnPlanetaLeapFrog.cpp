#include <iostream>
#include <cmath>
#include "vector.h"
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
  void Muevase(double dt);
  double Getx(void){return r.x();}; // Inline
  double Gety(void){return r.y();}; // Inline
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
void Cuerpo::Muevase(double dt){
  //Algoritmo de Euler
  r+=V*dt;  V+=F*(dt/m);
}

//----------- Funciones Globales -----------


int main(){
  vector3D r;
  double GM = 1.0;
  int Nsteps = 1000;  // Ajusta según sea necesario
  double dt = 0.1;  // Suponiendo que T está definido
  int StepsPerFrame = 10;  // Ajusta según sea necesario
  int Nframes = Nsteps / StepsPerFrame;
  Cuerpo Planeta;

  double r0=10;
  double omega=sqrt(GM/pow(r0,3));
  double T=2/omega;
  double V0=omega*r0;

  r.load(1,1,1);

  //----------(x0,y0,z0,Vx0,Vy0,Vz0,m0 ,R0)
  Planeta.Inicie(r0,0,0,0,0.5*V0,0,0.453,1);
  
  
  for (int t = 0; t < Nsteps; t+=dt) {
    
        if (t % StepsPerFrame == 0) {
            int k = t / StepsPerFrame;
            cout<<Planeta.Getx()<<" "<<Planeta.Gety()<<endl;
        }
    
    Planeta.CalculeFuerza();
    Planeta.Muevase(dt);

  }
  return 0;
}
