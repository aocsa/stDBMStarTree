set title "Conjunto de Dados: Cidades  page=4096"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	74.280000
0.002000	87.420000
0.005000	112.660000
0.010000	140.720000
0.020000	182.040000
end
# SlimTree-RangeIntersection
0.001000	1333.260000
0.002000	1346.400000
0.005000	1371.580000
0.010000	1399.440000
0.020000	1440.140000
end
# SeqScan-Nearest
0.001000	682.000000
0.002000	682.000000
0.005000	682.000000
0.010000	682.000000
0.020000	682.000000
end
# SeqScan-IntersectionNearest
0.001000	1364.000000
0.002000	1364.000000
0.005000	1364.000000
0.010000	1364.000000
0.020000	1364.000000
end

pause -1