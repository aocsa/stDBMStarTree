set title "Conjunto de Dados: Cidades  page=1024"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	35.160000
0.002000	40.880000
0.005000	55.440000
0.010000	75.720000
0.020000	110.080000
end
# SlimTree-RangeIntersection
0.001000	2125.020000
0.002000	2130.600000
0.005000	2144.100000
0.010000	2161.620000
0.020000	2189.260000
end
# SeqScan-Nearest
0.001000	859.000000
0.002000	859.000000
0.005000	859.000000
0.010000	859.000000
0.020000	859.000000
end
# SeqScan-IntersectionNearest
0.001000	1718.000000
0.002000	1718.000000
0.005000	1718.000000
0.010000	1718.000000
0.020000	1718.000000
end

pause -1