set title "Conjunto de Dados: Cidades  page=4096, ratio (outer/inner) =0.60"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(D) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6####################
# SlimTree-RingRange
0.001000	35.134000
0.002000	35.830000
0.005000	38.070000
0.010000	41.974000
0.020000	51.624000
0.050000	94.726000
0.100000	221.954000
end
# SlimTree-RingRange Intersection
0.001000	69.968000
0.002000	71.098000
0.005000	74.630000
0.010000	80.788000
0.020000	95.312000
0.050000	158.010000
0.100000	336.514000
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

pause -1