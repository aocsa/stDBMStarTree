set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.50"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Cálculo de Distância"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	84.796000
0.002000	92.718000
0.005000	115.898000
0.010000	153.140000
0.020000	231.494000
0.050000	509.812000
0.100000	1150.314000
end
# SlimTree-RingRange Intersection
0.001000	165.736000
0.002000	177.612000
0.005000	212.798000
0.010000	269.840000
0.020000	387.446000
0.050000	803.580000
0.100000	1775.848000
end
# SlimTree-Range
0.001000	84.832000
0.002000	92.780000
0.005000	116.104000
0.010000	153.736000
0.020000	233.710000
0.050000	527.310000
0.100000	1248.538000
end
# SeqScan-RingRange
0.001000	27032.000000
0.002000	27032.000000
0.005000	27032.000000
0.010000	27032.000000
0.020000	27032.000000
0.050000	27032.000000
0.100000	27032.000000
end
# SeqScan-RingRange Intersection
0.001000	54064.000000
0.002000	54064.000000
0.005000	54064.000000
0.010000	54064.000000
0.020000	54064.000000
0.050000	54064.000000
0.100000	54064.000000
end
# SeqScan-Range
0.001000	27032.000000
0.002000	27032.000000
0.005000	27032.000000
0.010000	27032.000000
0.020000	27032.000000
0.050000	27032.000000
0.100000	27032.000000
end

pause -1