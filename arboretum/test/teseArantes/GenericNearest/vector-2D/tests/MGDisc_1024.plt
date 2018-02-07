set title "Conjunto de Dados: Cidades  page=1024"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	32.220000
0.002000	37.720000
0.005000	51.020000
0.010000	68.280000
0.020000	97.120000
end
# SlimTree-RangeIntersection
0.001000	1618.140000
0.002000	1623.560000
0.005000	1636.240000
0.010000	1651.560000
0.020000	1675.420000
end
# SeqScan-Nearest
0.001000	644.000000
0.002000	644.000000
0.005000	644.000000
0.010000	644.000000
0.020000	644.000000
end
# SeqScan-IntersectionNearest
0.001000	1288.000000
0.002000	1288.000000
0.005000	1288.000000
0.010000	1288.000000
0.020000	1288.000000
end

pause -1