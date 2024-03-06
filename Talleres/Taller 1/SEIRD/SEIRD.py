# -*- coding: utf-8 -*-
"""
Created on Fri Feb  4 08:37:48 2022

@author: cterr

"""

from RungeKuttaMulti import RungeKuttaSysArr4M

n=9000000.0#// Poblacion total
b=0.166#// 1/días 
rb=0.5# //
e = 1/5#//
pa = 0.8#;//
m = 1/21#;//
pd =0.03#//


#t,St,Ia,Is,Et
def fSt(t,St,Ia,Is,Et,Rt,Dt):
	
	return -1*(St/n)*(b*rb*Ia+Is)
	

def fEt(t,St,Ia,Is,Et,Rt,Dt):
	
	return (St/n)*(b*rb*Ia+b*Is)-e*(pa*Et+(1-pa)*Et)
	


def fIa(t,St,Ia,Is,Et,Rt,Dt):
	
	return e*pa*Et-m*Ia
	


def fIs(t,St,Ia,Is,Et,Rt,Dt):
	
	return  e*(1-pa)*Et-m*((1-pd)*Is-pd*Is)
	


def fRt(t,St,Ia,Is,Et,Rt,Dt):
	
	return  m*(1-pd)*Is + m*Ia
	

def fDt(t,St,Ia,Is,Et,Rt,Dt):
	
	return  m*pd*Is
	



if __name__ == "__main__":
    
    
    fns=(fSt,fIa,fIs,fEt,fRt,fDt)# Sistemas de ecuaciones diferenciales
    ci=(n,1400,140,5368.44,3.486,0)#Condiciones iniciales
    
   
    
    RungeKuttaSysArr4M(fns,ci,0,366,0.02)