#include <iostream>
#include <cmath>
#include "../vector.h"
#include "../Random64.h"
using namespace std;

//--------------- Constantes globales ------------
const double g=9.8, l=1, m=1;

//--------------- Declarar las clases-----------
class Cuerpo;
class Colisionador;

//--------- Declarar las interfases de las clases---------
class CuerpoRigido{
private:
  //Torques y omegas en el sistema del cuerpo
  double I1,I2,I3,q0,q1,q2,q3,wx,wy,wz,Nx,Ny,Nz;
public:
  void Inicie(double Ix,double Iy, double Iz,
              double theta0, double phi0, double psi0,
              double w0x, double w0y, double w0z);
  void CalculeTorque(void);
  void Rote(double dt);
  void CalcularXYZ(double &x, double &y, double &z);
  double getWY(void){return wy;};
  double getWX(void){return wx;};
  double getWZ(void){return wz;};
  double getTheta(void){return acos((q0*q0 - q1*q1 - q2*q2 + q3*q3)/(q0*q0 + q1*q1 + q2*q2 + q3*q3));};
};

void CuerpoRigido::Inicie(double Ix,double Iy, double Iz,
              double theta0, double phi0, double psi0,
              double w0x, double w0y, double w0z){

              //Momentos de inercia
              I1=Ix; I2=Iy; I3=Iz;  

              //Velocidades angulares
              wx=w0x; wy=w0y; wz=w0z;

              //Cuaterniones
              q0=cos((theta0/2.0))*(cos(phi0/2.0))*(cos(psi0 + phi0)/2.0);
              q1=sin((theta0/2.0))*(cos(phi0/2.0))*(cos(psi0 - phi0)/2.0);
              q2=sin((theta0/2.0))*(sin(phi0/2.0))*(cos(psi0 - phi0)/2.0);
              q3=cos((theta0/2.0))*(sin(phi0/2.0))*(cos(psi0 + phi0)/2.0);

              
}

//-------Implementar las funciones de las clases------
//------- Funciones de la clase cuerpo rigido --------

//Torque en el sistema del cuerpo
void CuerpoRigido::CalculeTorque(void){
  Nx = 2.0*(q2*q3 + q0*q1)*m*g*l;
  Ny = 2.0*(q3*q1 - q0*q2)*m*g*l;
  Nz = 0;// q0*q0 - q1*q1 - q2*q2 + q3*q3;

}
//Rota el cuerpo
void CuerpoRigido::Rote(double dt){
  double q0_old=q0, q1_old=q1, q2_old=q2, q3_old=q3;
  double wx_old=wx, wy_old=wy, wz_old=wz;

  //Actualizar los cuaterniones
  q0 += dt*(-(q1_old*wx_old - q2_old*wy_old - q3_old*wz_old)/2.0);
  q1 += dt*((q0_old*wx_old - q3_old*wy_old + q2_old*wz_old)/2.0);
  q2 += dt*((q0_old*wy_old + q3_old*wx_old - q1_old*wz_old)/2.0);
  q3 += dt*((q0_old*wz_old - q2_old*wx_old + q1_old*wy_old)/2.0);
  
  //Actualizar las velocidades angulares
  wx += dt*((I2 - I3)*wy_old*wz_old/I1 + Nx/I1);
  wy += dt*((I3 - I1)*wz_old*wx_old/I2 + Ny/I2);
  wz += dt*((I1 - I2)*wx_old*wy_old/I3 + Nz/I3);


}

//Calcular las coordenadas del centro de masa
void CuerpoRigido::CalcularXYZ(double &x, double &y, double &z){
  double xi = x, yi = y, zi = z;
  x = (q0*q0 + q1*q1 - q2*q2 - q3*q3)*xi + 2.0*(q1*q2 - q0*q3)*yi/2.0 + 2.0*(q1*q3 - q0*q2)*zi;
  y = 2.0*(q1*q2 + q0*q3)*xi + (q0*q0 - q1*q1 + q2*q2 - q3*q3)*yi + 2.0*(q2*q3 - q0*q1)*zi;
  z = 2.0*(q1*q3 + q0*q2)*xi + 2.0*(q2*q3 + q0*q1)*yi + (q0*q0 - q1*q1 - q2*q2 + q3*q3)*zi;
  
}



//----------- Funciones Globales -----------
//---Funciones de Animacion---
void InicieAnimacion(void){
  cout<<"set terminal gif animate"<<endl; 
  cout<<"set output 'Granos.gif'"<<endl;
  cout<<"unset key"<<endl;
  cout<<"set xrange[-20:"<<Lx + 20<<"]"<<endl;
  cout<<"set yrange[-20:"<<Ly + 20<<"]"<<endl;
  cout<<"set size ratio -1"<<endl;
  cout<<"set parametric"<<endl;
  cout<<"set trange [0:7]"<<endl;
  cout<<"set isosamples 12"<<endl;  
}
void InicieCuadro(void){
    cout<<"plot 0,0 ";
    cout<<" , "<<Lx/7<<"*t,0";        //pared de abajo
    cout<<" , "<<Lx/7<<"*t,"<<Ly;     //pared de arriba
    cout<<" , 0,"<<Ly/7<<"*t";        //pared de la izquierda
    cout<<" , "<<Lx<<","<<Ly/7<<"*t"; //pared de la derecha
    
}
void TermineCuadro(void){
    cout<<endl;
}

int main(){
  
  CuerpoRigido Trompo;
  double t,tdibujo,dt=1e-3;
  double theta0=0, phi0=0, psi0=0, w0x=0, w0y=0, w0z=0;
  double Ix=1.0/12.0*m*l*l, Iy=1.0/12.0*m*l*l, Iz=1.0/12.0*m*l*l;
  double x=0, y=0, z=0;

  //Inicie el trompo
  Trompo.Inicie(Ix,Iy,Iz,theta0,phi0,psi0,w0x,w0y,w0z);

  //Inicie la animacion
  InicieAnimacion();

  //Integracion de las ecuaciones de movimiento
  for(t=tdibujo=0;t<10;t+=dt,tdibujo+=dt){
    //Animacion
    if(tdibujo>1e-2){
      InicieCuadro();
      Trompo.CalcularXYZ(x,y,z);
      cout<<x<<"+"<<l/2.0<<"*cos(t),"<<y<<"+"<<l/2.0<<"*sin(t)";
      TermineCuadro();
      tdibujo=0;
    
    Trompo.CalculeTorque();
    Trompo.Rote(dt);

  }
  return 0;
  }
}
