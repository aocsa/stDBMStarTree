set title "Conjunto de Dados: Cidades  page=8192"
set logscale xy
set xlabel "k"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	1.453000
0.002000	1.640000
0.005000	2.109000
0.010000	2.828000
0.020000	4.625000
end
# SlimTree-RangeIntersection
0.001000	1951.125000
0.002000	1978.953000
0.005000	2105.828000
0.010000	2314.344000
0.020000	2692.985000
end
# SeqScan-Nearest
0.001000	5.594000
0.002000	5.641000
0.005000	5.938000
0.010000	6.766000
0.020000	9.968000
end
# SeqScan-NearestIntersection
0.001000	3942.954000
0.002000	3990.515000
0.005000	4114.688000
0.010000	4362.765000
0.020000	4810.062000
end

pause -1