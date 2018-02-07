set title "Conjunto de Dados: Cidades  page=1024"
set logscale xy
set xlabel "k"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	0.016000
0.002000	0.015000
0.005000	0.046000
0.010000	0.094000
0.020000	0.266000
end
# SlimTree-RangeIntersection
0.001000	130.719000
0.002000	137.000000
0.005000	155.390000
0.010000	188.109000
0.020000	249.859000
end
# SeqScan-Nearest
0.001000	0.453000
0.002000	0.454000
0.005000	0.516000
0.010000	0.687000
0.020000	1.234000
end
# SeqScan-NearestIntersection
0.001000	864.813000
0.002000	864.203000
0.005000	940.641000
0.010000	996.563000
0.020000	1032.610000
end

pause -1