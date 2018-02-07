set title "Conjunto de Dados: metricHisto  page=8192, ratio (outer/inner) =0.40"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	1.609000
0.002000	1.860000
0.005000	2.250000
0.010000	2.906000
0.020000	4.297000
0.050000	9.281000
0.100000	21.875000
end
# SlimTree-RingRange Intersection
0.001000	3.281000
0.002000	3.484000
0.005000	4.110000
0.010000	4.922000
0.020000	7.016000
0.050000	13.984000
0.100000	31.312000
end
# SlimTree-Range
0.001000	1.688000
0.002000	1.797000
0.005000	2.250000
0.010000	2.907000
0.020000	4.312000
0.050000	9.547000
0.100000	22.968000
end
# SeqScan-RingRange
0.001000	35.906000
0.002000	35.828000
0.005000	35.891000
0.010000	35.937000
0.020000	35.860000
0.050000	36.531000
0.100000	40.656000
end
# SeqScan-RingRange Intersection
0.001000	75.563000
0.002000	75.562000
0.005000	75.578000
0.010000	75.703000
0.020000	75.750000
0.050000	76.766000
0.100000	82.781000
end
# SeqScan-Range
0.001000	37.906000
0.002000	37.875000
0.005000	37.859000
0.010000	37.875000
0.020000	37.891000
0.050000	38.625000
0.100000	43.594000
end

pause -1