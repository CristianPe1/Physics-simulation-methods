#include <iostream>
#include <cmath>
#include "../vector.h"
#include "../Random64.h"
using namespace std;

//Constantes del problema físico
const double G=1.0;
//Número de moleculass
const int Nx=5; 
const int Ny=5; 
const int N = Nx*Ny;

const double A = Lx*Ly;
const double K=1.0e4; //Elasticidad de la colisión

//Constantes del algoritmo de integración
const double xi=0.1786178958448091;
const double lambda=-0.2123418310626054;
const double chi=-0.06626458266981849;
const double Um2lambdau2=(1-2*lambda)/2;
const double Um2chiplusxi=1-2*(chi+xi);

//--------------- Declarar las clases-----------
class Cuerpo;
class Colisionador;

//--------- Declarar las interfases de las clases---------
class Cuerpo{
private:
  vector3D r,V,F; double m,R;
public:
  void Inicie(double x0,double y0,double z0,
	      double Vx0,double Vy0,double Vz0,double m0,double R0);
  void BorreFuerza(void){F.load(0,0,0);};// Inline
  void SumeFuerza(vector3D dF){F+=dF;};// Inline
  void Mueva_r(double dt,double coeficiente);
  void Mueva_V(double dt,double coeficiente);
  void Dibujese(void);
  double Getx(void){return r.x();}; // Inline
  double Gety(void){return r.y();}; // Inline
  friend class Colisionador;
};
class Colisionador{
private:
public:
  void CalculeTodasLasFuerzas(Cuerpo * moleculas);
  void CalculeFuerzaEntre(Cuerpo & moleculas1,Cuerpo & moleculas2);
};

//-------Implementar las funciones de las clases------
//------- Funciones de la clase cuerpo --------
void Cuerpo::Inicie(double x0,double y0,double z0,
	      double Vx0,double Vy0,double Vz0,double m0,double R0){
  r.load(x0,y0,z0);  V.load(Vx0,Vy0,Vz0); m=m0; R=R0;
}
void Cuerpo::Mueva_r(double dt,double coeficiente){
  r+=V*(coeficiente*dt);
}
void Cuerpo::Mueva_V(double dt,double coeficiente){
  V+=F*(coeficiente*dt/m);
}
void Cuerpo::Dibujese(void){
  cout<<" , "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t)";
}
//------- Funciones de la clase Colisionador --------
void Colisionador::CalculeTodasLasFuerzas(Cuerpo * moleculas){
  int i,j;
  //Borro las fuerzas de todos los moleculass
  for(i=0;i<N;i++)
    moleculas[i]. BorreFuerza();
  //Recorro por parejas, calculo la fuerza de cada pareja y se la sumo a los dos
  for(i=0;i<N;i++)
    for(j=0;j<i;j++)
      CalculeFuerzaEntre(moleculas[i],moleculas[j]);
}
void Colisionador::CalculeFuerzaEntre(Cuerpo & moleculas1, Cuerpo & moleculas2){
  
  //Calcular el vector normal
  vector3D r21=moleculas2.r-moleculas1.r; 
  double r=r21.norm2();


  //Determinar si hay colisión
  double R1=moleculas1.R, R2=moleculas2.R;
  double s= R1 + R2 - r;
  
  if(s>0){
    double aux= K*pow(s,1.5);

    //Calcular vector normal
    vector3D n = r21*(1.0/sqrt(r));

    //Calcular la fuerza
    vector3D F1=n*aux;

    //Sumar las fuerzas
    moleculas1.SumeFuerza(F1);  moleculas2.SumeFuerza(F1*(-1));

  }
    
}
//----------- Funciones Globales -----------
//---Funciones de Animacion---
void InicieAnimacion(void){
  cout<<"set terminal gif animate"<<endl; 
  cout<<"set output 'moleculas.gif'"<<endl;
  cout<<"unset key"<<endl;
  cout<<"set xrange[-11:11]"<<endl;
  cout<<"set yrange[-11:11]"<<endl;
  cout<<"set size ratio -1"<<endl;
  cout<<"set parametric"<<endl;
  cout<<"set trange [0:7]"<<endl;
  cout<<"set isosamples 12"<<endl;  
}
void InicieCuadro(void){
    cout<<"plot 0,0 ";
}
void TermineCuadro(void){
    cout<<endl;
}

int main(){
  
  //Numero de pasos y de frames en la simulación 
  //double t,dt=0.01,ttotal=T;
  int Ncuadros=300; 
  double tdibujo,tcuadro=ttotal/Ncuadros;
  Cuerpo moleculas[N];
  Colisionador Newton;
  Crandom ran64(1);
  int i;

  //Parametros de la simulación
  //Dimesiones de la caja
  double Lx=60, Ly=60; 
  double dx = Lx/(Nx + 1), dy = Ly/(Ny + 1);
  double m0=1.0, R0=2.0;
  double theta;

  //Teorema de equipartición de la energía
  double kT = 10.0, V0 = sqrt(kT/m0);
  int Ncuadrados = 1000;
  double t,dt=1.0e-3,tmax=10*Lx/V0; tdibujo = tmax/Ncuadros;
  

  InicieAnimacion();
  
  //INICIO
  for(int i=0; i<Nx; i++){
    for(int j=0; j<Ny; j++){
      theta = 2*M_PI*ran64.r();
      double x0 = (i+1)*dx, y0 = (j+1)*dy;
      double V0x = V0*cos(theta), V0y = V0*sin(theta);
      moleculas[i*Ny + j].Inicie(x0, y0, 0, V0x, V0y, 0, m0, R0);
    }
  }


  //---------------(x0,y0,z0,Vx0,   Vy0,Vz0,m0,R0)
  // moleculas[0].Inicie(x0, 0, 0,  0, 0.5*V0,  0,m0,1.0);
  // moleculas[1].Inicie(x1, 0, 0,  0, 0.5*V1,  0,m1,0.5);
  //CORRO
  for(t=tdibujo=0;t<ttotal;t+=dt,tdibujo+=dt){

    if(tdibujo>=tcuadro){
      
      InicieCuadro();
      for(i=0;i<N;i++) moleculas[i].Dibujese();
      TermineCuadro();
      
      tdibujo=0;
    }
    // cout<<moleculas[1].Getx()<<" "<<moleculas[1].Gety()<<endl;
    
    for(i=0;i<N;i++) moleculas[i].Mueva_r(dt,xi);    
    Newton.CalculeTodasLasFuerzas(moleculas); 
    for(i=0;i<N;i++) moleculas[i].Mueva_V(dt,Um2lambdau2);

    for(i=0;i<N;i++) moleculas[i].Mueva_r(dt,chi);
    Newton.CalculeTodasLasFuerzas(moleculas); 
    for(i=0;i<N;i++) moleculas[i].Mueva_V(dt,lambda);
    
    for(i=0;i<N;i++) moleculas[i].Mueva_r(dt,Um2chiplusxi);
    Newton.CalculeTodasLasFuerzas(moleculas); 
    for(i=0;i<N;i++)moleculas[i].Mueva_V(dt,lambda);

    for(i=0;i<N;i++) moleculas[i].Mueva_r(dt,chi);
    Newton.CalculeTodasLasFuerzas(moleculas); 
    for(i=0;i<N;i++)moleculas[i].Mueva_V(dt,Um2lambdau2);

    for(i=0;i<N;i++) moleculas[i].Mueva_r(dt,xi);
    
  }
  return 0;

}
