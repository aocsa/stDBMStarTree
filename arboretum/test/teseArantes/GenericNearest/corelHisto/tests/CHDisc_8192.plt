set title "Conjunto de Dados: Cidades  page=8192"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	1010.600000
0.002000	1132.000000
0.005000	1338.940000
0.010000	1530.960000
0.020000	1770.220000
end
# SlimTree-RangeIntersection
0.001000	4985.560000
0.002000	5106.880000
0.005000	5313.540000
0.010000	5504.760000
0.020000	5742.340000
end
# SeqScan-Nearest
0.001000	2187.000000
0.002000	2187.000000
0.005000	2187.000000
0.010000	2187.000000
0.020000	2187.000000
end
# SeqScan-IntersectionNearest
0.001000	4374.000000
0.002000	4374.000000
0.005000	4374.000000
0.010000	4374.000000
0.020000	4374.000000
end

pause -1