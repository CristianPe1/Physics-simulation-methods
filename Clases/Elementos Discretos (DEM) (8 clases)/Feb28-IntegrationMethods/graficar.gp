# Asumir que 'datafile' será definido externamente
set output sprintf("%s.pdf", datafile)
set terminal pdf
set xlabel "Eje X"
set ylabel "Eje Y"
plot datafile using 1:2 with lines title "Titulo"