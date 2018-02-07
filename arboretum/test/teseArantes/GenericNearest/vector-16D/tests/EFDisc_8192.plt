set title "Conjunto de Dados: Cidades  page=8192"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	48.960000
0.002000	52.800000
0.005000	58.920000
0.010000	64.500000
0.020000	72.300000
end
# SlimTree-RangeIntersection
0.001000	371.960000
0.002000	375.800000
0.005000	381.920000
0.010000	387.500000
0.020000	395.280000
end
# SeqScan-Nearest
0.001000	195.000000
0.002000	195.000000
0.005000	195.000000
0.010000	195.000000
0.020000	195.000000
end
# SeqScan-IntersectionNearest
0.001000	390.000000
0.002000	390.000000
0.005000	390.000000
0.010000	390.000000
0.020000	390.000000
end

pause -1