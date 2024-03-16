set title "Theta vs. Time"
set xlabel "Time (s)"
set ylabel "Theta (rad)"
set term pdf
set output "TrompoCuaterniones.pdf"
#lc: line color, lw: line width, lt: line type
set grid xtics ytics lc rgb "#bbbbbb" lw 1 lt 0


# lp: linepoint, lw: line width, ps: point size, pt: point type
plot "TrompoCuaterniones.txt" w lp lw 4 ps 0.1 pt 7 t "Theta vs. Time"