set title "Conjunto de Dados: Cidades  page=1024"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Cálculo de Distância"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	266.984000
0.002000	350.908000
0.005000	548.178000
0.010000	823.970000
0.020000	1303.880000
0.050000	2501.864000
0.100000	4322.612000
end
# SlimTree-NearestIntersection
0.001000	28883.096000
0.002000	28962.808000
0.005000	29138.474000
0.010000	29368.652000
0.020000	29741.616000
0.050000	30535.140000
0.100000	31618.582000
end
# SeqScan-Nearest
0.001000	27032.000000
0.002000	27032.000000
0.005000	27032.000000
0.010000	27032.000000
0.020000	27032.000000
0.050000	27032.000000
0.100000	27032.000000
end
# SeqScan-NearestIntersection
0.001000	54064.000000
0.002000	54064.000000
0.005000	54064.000000
0.010000	54064.000000
0.020000	54064.000000
0.050000	54064.000000
0.100000	54064.000000
end

pause -1