#include <iostream>
#include <cmath>

//using namespace std;
using std::cout;
using std::endl;


const double g=9.8;

//Declaracion de la clase
class Objeto;

//Declaracion de la interfase
class Objeto{
private: 
  double x, y, Vx, Vy, Fx, Fy, m, R;
public:
  void Inicie(double x0, double y0, double Vx0, double Vy0, double m0, double R0);
  void CalculeFuerza(void);
  void Muevase(double dt);
  void Dibujese(void);
  double Getx(void){return x;};//In line -- Macro -- Search and replace
  double Gety(void){return y;};//In line -- Macro -- Search and replace
};

//Implementacion de las funciones
void Objeto::Inicie(double x0, double y0, double Vx0, double Vy0, double m0, double R0){
      x=x0; y=y0; Vx=Vx0; Vy=Vy0; m=m0; R=R0;
}

void Objeto::CalculeFuerza(void){
  Fx=0; Fy=-m*g;
}

void Objeto::Muevase(double dt){
  x+=Vx*dt; y+=Vy*dt;
  Vx+=Fx/m*dt; Vy+=Fy/m*dt;
}


void Objeto::Dibujese(void){
  cout<<" , "<<Getx()<<"+"<<R<<"*cos(t),"<<Gety()<<"+"<<R<<"*sin(t)";
  //cout<<" , "<<x0<<"+"<<l/7<<"*t*sin("<<theta<<"),-"<<l/7<<"*t*cos("<<theta<<")";
}


//-----------------------Funcion Globales-----------------------
//-----------------------Funcion animacion-----------------------
    void InicieAnimacion(void){
      //  cout<<"set terminal gif animate"<<endl; 
      //  cout<<"set output 'DosPendulos.gif'"<<endl;
      cout<<"unset key"<<endl;
      cout<<"set xrange[-1:41]"<<endl;
      cout<<"set yrange[-10:8]"<<endl;
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


    //-----------------------Funcion Principal-----------------------
    int main(){
      double t,dt=0.001,ttotal=2.5;
      int Ncuadros=200; double tdibujo,tcuadro=ttotal/Ncuadros;
      Objeto Balon;

      InicieAnimacion();
      
      //----------(x0,y0,Vx0,Vy0,m0   ,R0)
      Balon.Inicie( 0, 0, 16,  9,0.453,1.0);
      for(t=tdibujo=0;t<ttotal;t+=dt,tdibujo+=dt){
        if(tdibujo>tcuadro){
          InicieCuadro();
          Balon.Dibujese();
          TermineCuadro();
          tdibujo=0;
        }
        //cout<<Balon.Getx()<<" "<<Balon.Gety()<<endl;
        Balon.CalculeFuerza();
        Balon.Muevase(dt);
        
      }
    }