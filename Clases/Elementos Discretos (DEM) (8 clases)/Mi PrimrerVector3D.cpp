#include <iostream>
#include <cmath>
#include "vector.h"

using namespace std;

int main(void){

    vector3D a, b;
    a.load(1,2,3);
    b.load(2,4,6);
    c.load(0,0,1);

    cout<<a*b<<endl;

    cout << "a: " << a.x << " " << a.y << " " << a.z << endl;

    //c=a^b;
    //c=a+b;
    //c.show();
    d = a^b + c;
    d.show();
    
    cout << "c=a+b: " << c.x << " " << c.y << " " << c.z << endl;

return 0;

}