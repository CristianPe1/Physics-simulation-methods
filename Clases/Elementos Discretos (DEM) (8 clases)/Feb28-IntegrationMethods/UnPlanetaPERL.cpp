#include <iostream>
#include <cmath>
#include "../vector.h"
using namespace std;

const double GM=1.0;

const float Xi = 0.1786178958448091;
const float Lambda = -0.2123418310626054;
const float Chi = -0.06626458266981849;


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
  void Mueva_r(double dt, double Theta);
  void Mueva_V(double dt, double Theta);
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

//Algoritmo de Forest-Ruth

void Cuerpo::Mueva_r(double dt, double Theta){
  r += V*(Theta*dt);
}

void Cuerpo::Mueva_V(double dt, double Theta){
  V += F*(Theta*dt/m);
}


//----------- Funciones Globales -----------

  
int main(){

  double GM = 1.0;
  double t,dt=0.001,ttotal=300;
  int Ncuadros=500;
  double tdibujo,tcuadro=ttotal/Ncuadros;
  Cuerpo Planeta;

  double r0=10;
  double omega=sqrt(GM/pow(r0,3));
  double T=2/omega;
  double V0=omega*r0;


  //----------(x0,y0,z0,Vx0,Vy0,Vz0,m0 ,R0)
  Planeta.Inicie(r0,0,0,0,0.5*V0,0,0.453,1);
  
  
   for(t=tdibujo=0;t<ttotal;t+=dt,tdibujo+=dt){
    if(tdibujo>tcuadro){
      cout<<Planeta.Getx()<<" "<<Planeta.Gety()<<endl;
      tdibujo=0;
    }
    
    Planeta.Mueva_r(dt,Xi);
    Planeta.CalculeFuerza();
    Planeta.Mueva_V(dt,1.0-2*Lambda);
    
    Planeta.Mueva_r(dt,Chi);
    Planeta.CalculeFuerza();
    Planeta.Mueva_V(dt,Lambda);

    Planeta.Mueva_r(dt,Chi);
    Planeta.CalculeFuerza();
    Planeta.Mueva_V(dt,1.0 - 2.0*Lambda);

    Planeta.Mueva_r(dt,Xi);

  }
  return 0;
}
