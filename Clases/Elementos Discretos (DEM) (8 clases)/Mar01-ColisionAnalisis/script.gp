reset
set term pdf
set out "graph.pdf"
set xtic auto 
set ytic auto
set logscale y
set xlabel 'x'
set ylabel 'Gamma function  '


plot 'data.txt' w lp lw 0.5 ps 0.5 pt 7 t 'data'




#Rangos para ejes x e y:

#Puedes especificar el rango para los ejes x e y 
#utilizando la sintaxis [xmin:xmax] para el eje x y 
#[ymin:ymax] para el eje y. Por ejemplo:

#plot [0:10] [0:20] 'data.txt' w lp


#Multiples conjuntos de datos:
#Puedes graficar varios conjuntos de datos en la misma 
#grafica separandolos por comas. Por ejemplo:

#plot 'data1.txt' w lp, 'data2.txt' w lp
