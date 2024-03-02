#include <iostream>
#include <cmath>
#include "vector.h"

using namespace std;

int main(void){

    double n;
    vector3D a, b,c, d;

    a.load(1,2,3);
    b.load(2,4,6);
    c.load(0,0,1);

    cout<<a*b<<endl;

    a.show();
    b.show();

    //c=a^b;
    //c=a+b;
    //c.show();
    d = a^b + c;
    n = d.norm();
    d.show();
    
    cout<<n<<endl;
return 0;

}