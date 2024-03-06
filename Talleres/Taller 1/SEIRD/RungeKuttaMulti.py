# -*- coding: utf-8 -*-
"""
Created on Fri Feb  4 08:55:12 2022

@author: cterr
"""

import numpy as np
import matplotlib.pyplot as plt


def RungeKuttaSysArr4M(fns, ci, a, b, h):
    
    t = np.arange(a, b + h, h)
    nP = len(t)#Numero de pasos
    nF = len(fns)#Numero de funciones
    
    x = np.zeros((nF,nP))    
    k= np.zeros((nF,4))
    
    for i in range(nF):
        
        x[i][0] = ci[i]
        

    
    print("\tt \t\t S \t\t\t   Ia \t\t Is \t\t\tE \t\t\tR \t\t\tD ")
   
    for i in range(nP-1):
        
        #print("\n")
        #print(i)
        #print("\n")
        
        for j in range(nF):#Ciclo funciónes auxiliares 1
    
            k[j][0] = h*fns[j](t[i], x[0][i], x[1][i], x[2][i], x[3][i], x[4][i], x[5][i])
            #print(k[j][0])
            #print("\n")

        for j in range(nF):#Ciclo funciónes auxiliares 2
            
            k[j][1] = h*fns[j](t[i] + h/2, x[0][i] + k[0][0]/2, x[1][i] + k[1][0]/2, x[2][i] + k[2][0]/2,
                                 x[3][i] + k[3][0]/2 , x[4][i] + k[4][0]/2 , x[5][i] + k[5][0]/2)
            #print(k[j][     #print("\n")
            
        for j in range(nF):#Ciclo funciónes auxiliares 3
            
            k[j][2] = h*fns[j](t[i] + h/2, x[0][i] + k[0][1]/2, x[1][i] + k[1][1]/2, x[2][i] + k[2][1]/2,
                                 x[3][i] + k[3][1]/2, x[4][i] + k[4][1]/2, x[5][i] + k[5][1]/2)
            #print(k[j][2])
            #print("\n")
            
        for j in range(nF):#Ciclo funciónes auxiliares 4
            
            k[j][3] = h*fns[j](t[i] + h, x[0][i] + k[0][2], x[1][i] + k[1][2], x[2][i] + k[2][2],
                                 x[3][i] + k[3][2], x[4][i] + k[4][2], x[5][i] + k[5][2])
            #print(k[j][3])
            #print("\n")
            
        for j in range(nF):#Ciclo funciónes aproximadas
        
            x[j][i + 1] = x[j][i] + (1/6)*(k[j][0] + 2*k[j][1] + 2*k[j][2] + k[j][3])
            
            #print(x[j][i+1])   
            
        print("\n %4.2f \t %6.2f \t %6.2f \t %6.2f \t %6.2f \t %6.2f \t %6.2f"%(t[i], x[0][i], x[1][i], x[2][i], x[3][i], x[4][i],x[5][i]))
    
    

    
    for i in range(nF):
        
        plt.plot(t, x[i],linewidth=0.7,linestyle="-" )
        
    plt.show()

