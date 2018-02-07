set title "Conjunto de Dados: Cidades  page=8192"
set logscale xy
set xlabel "k"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	3.812000
0.002000	4.468000
0.005000	8.922000
0.010000	9.281000
0.020000	11.453000
0.050000	15.797000
0.100000	22.454000
end
# SlimTree-RangeIntersection
0.001000	114.625000
0.002000	118.609000
0.005000	127.266000
0.010000	142.672000
0.020000	169.375000
0.050000	246.313000
0.100000	350.796000
end
# SeqScan-Nearest
0.001000	25.891000
0.002000	39.813000
0.005000	37.453000
0.010000	37.375000
0.020000	37.766000
0.050000	40.515000
0.100000	46.734000
end
# SeqScan-NearestIntersection
0.001000	226.032000
0.002000	228.734000
0.005000	236.922000
0.010000	251.437000
0.020000	278.578000
0.050000	356.141000
0.100000	466.219000
end

pause -1