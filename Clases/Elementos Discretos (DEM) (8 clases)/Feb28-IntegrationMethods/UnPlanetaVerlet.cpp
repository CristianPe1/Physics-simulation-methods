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
  vector3D r_new,r_old,r,V,F; double m,R;
public:
  void Inicie(double x0,double y0,double z0,double Vx0,double Vy0,double Vz0,
	      double m0,double R0);
  void CalculeFuerza(void);
  void Arranque(double dt);
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
  double aux = -GM * m *pow(r.norm2(),-1.5);
  F= aux*r;
}

//Algoritmo de Verlet
void Cuerpo::Arranque(double dt){
  r_old = r - V*dt + (F/2*m)*pow(dt,2);
}

void Cuerpo::Muevase(double dt){
  r_new = 2*r - r_old + (F/m)*pow(dt,2);
  V = (r_new - r_old)/(2*dt);
  r_old = r;
  r = r_new;

}

//----------- Funciones Globales -----------


int main(){

  double t,dt=0.01,ttotal=100;
  int Ncuadros=1000;
  double tdibujo,tcuadro=ttotal/Ncuadros;
  Cuerpo Planeta;

  double r0=10;
  double omega=sqrt(GM/pow(r0,3));
  double T=2/omega;
  double V0=omega*r0;

  Planeta.Arranque(dt);

  //----------(x0,y0,z0,Vx0,Vy0,Vz0,m0 ,R0)
  Planeta.Inicie(r0,0,0,0,0.5*V0,0,0.453,1);
  
  
   for(t=tdibujo=0;t<ttotal;t+=dt,tdibujo+=dt){
    if(tdibujo>tcuadro){
      cout<<Planeta.Getx()<<" "<<Planeta.Gety()<<endl;
      tdibujo=0;
    }
    
    Planeta.CalculeFuerza();
    Planeta.Muevase(dt);

  }
  return 0;
}
