set title "Conjunto de Dados: Cidades  page=4096, ratio (outer/inner) =0.60"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Cálculo de Distância"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	264.426000
0.002000	269.370000
0.005000	284.056000
0.010000	308.914000
0.020000	358.990000
0.050000	512.032000
0.100000	790.626000
end
# SlimTree-RingRange Intersection
0.001000	526.914000
0.002000	534.792000
0.005000	558.196000
0.010000	597.936000
0.020000	677.934000
0.050000	921.274000
0.100000	1355.720000
end
# SlimTree-Range
0.001000	264.444000
0.002000	269.388000
0.005000	284.074000
0.010000	308.932000
0.020000	359.008000
0.050000	512.062000
0.100000	790.754000
end
# SeqScan-RingRange
0.001000	49750.000000
0.002000	49750.000000
0.005000	49750.000000
0.010000	49750.000000
0.020000	49750.000000
0.050000	49750.000000
0.100000	49750.000000
end
# SeqScan-RingRange Intersection
0.001000	99500.000000
0.002000	99500.000000
0.005000	99500.000000
0.010000	99500.000000
0.020000	99500.000000
0.050000	99500.000000
0.100000	99500.000000
end
# SeqScan-Range
0.001000	49750.000000
0.002000	49750.000000
0.005000	49750.000000
0.010000	49750.000000
0.020000	49750.000000
0.050000	49750.000000
0.100000	49750.000000
end

pause -1