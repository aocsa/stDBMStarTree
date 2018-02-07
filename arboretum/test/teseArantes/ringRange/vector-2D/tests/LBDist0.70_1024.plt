set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.70"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	102.728000
0.002000	122.788000
0.005000	180.480000
0.010000	277.246000
0.020000	497.826000
0.050000	1307.894000
0.100000	2973.808000
end
# SlimTree-RingRange Intersection
0.001000	199.852000
0.002000	233.874000
0.005000	333.632000
0.010000	501.420000
0.020000	890.810000
0.050000	2567.882000
0.100000	6807.672000
end
# SlimTree-Range
0.001000	100.178000
0.002000	117.316000
0.005000	167.786000
0.010000	251.962000
0.020000	447.792000
0.050000	1286.064000
0.100000	3409.846000
end
# SeqScan-RingRange
0.001000	36048.000000
0.002000	36048.000000
0.005000	36048.000000
0.010000	36048.000000
0.020000	36048.000000
0.050000	36048.000000
0.100000	36048.000000
end
# SeqScan-RingRange Intersection
0.001000	72096.000000
0.002000	72096.000000
0.005000	72096.000000
0.010000	72096.000000
0.020000	72096.000000
0.050000	72096.000000
0.100000	72096.000000
end
# SeqScan-Range
0.001000	36048.000000
0.002000	36048.000000
0.005000	36048.000000
0.010000	36048.000000
0.020000	36048.000000
0.050000	36048.000000
0.100000	36048.000000
end

pause -1