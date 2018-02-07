set title "Conjunto de Dados: Cidades  page=4096, ratio (outer/inner) =0.60"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	34.572000
0.002000	34.696000
0.005000	35.110000
0.010000	35.802000
0.020000	37.218000
0.050000	41.794000
0.100000	51.164000
end
# SlimTree-RingRange Intersection
0.001000	69.078000
0.002000	69.286000
0.005000	69.930000
0.010000	71.058000
0.020000	73.324000
0.050000	80.530000
0.100000	94.656000
end
# SlimTree-Range
0.001000	34.572000
0.002000	34.696000
0.005000	35.110000
0.010000	35.802000
0.020000	37.218000
0.050000	41.794000
0.100000	51.164000
end
# SeqScan-RingRange
0.001000	682.000000
0.002000	682.000000
0.005000	682.000000
0.010000	682.000000
0.020000	682.000000
0.050000	682.000000
0.100000	682.000000
end
# SeqScan-RingRange Intersection
0.001000	1364.000000
0.002000	1364.000000
0.005000	1364.000000
0.010000	1364.000000
0.020000	1364.000000
0.050000	1364.000000
0.100000	1364.000000
end
# SeqScan-Range
0.001000	682.000000
0.002000	682.000000
0.005000	682.000000
0.010000	682.000000
0.020000	682.000000
0.050000	682.000000
0.100000	682.000000
end

pause -1