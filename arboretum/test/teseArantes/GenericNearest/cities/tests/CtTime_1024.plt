set title "Conjunto de Dados: Cidades  page=1024"
set logscale xy
set xlabel "k"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	0.062000
0.002000	0.078000
0.005000	0.125000
0.010000	0.172000
0.020000	0.282000
0.050000	0.688000
0.100000	1.688000
end
# SlimTree-RangeIntersection
0.001000	24.813000
0.002000	25.031000
0.005000	25.828000
0.010000	27.141000
0.020000	29.500000
0.050000	35.703000
0.100000	45.329000
end
# SeqScan-Nearest
0.001000	0.922000
0.002000	0.969000
0.005000	1.047000
0.010000	1.187000
0.020000	1.437000
0.050000	2.343000
0.100000	4.531000
end
# SeqScan-NearestIntersection
0.001000	63.234000
0.002000	63.532000
0.005000	64.593000
0.010000	66.266000
0.020000	69.203000
0.050000	76.687000
0.100000	88.437000
end

pause -1