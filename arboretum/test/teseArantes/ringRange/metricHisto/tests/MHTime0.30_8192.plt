set title "Conjunto de Dados: metricHisto  page=8192, ratio (outer/inner) =0.30"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	1.750000
0.002000	1.860000
0.005000	2.250000
0.010000	2.906000
0.020000	4.313000
0.050000	9.375000
0.100000	22.484000
end
# SlimTree-RingRange Intersection
0.001000	3.360000
0.002000	3.484000
0.005000	4.031000
0.010000	4.890000
0.020000	6.750000
0.050000	13.219000
0.100000	29.172000
end
# SlimTree-Range
0.001000	1.657000
0.002000	1.797000
0.005000	2.250000
0.010000	2.922000
0.020000	4.328000
0.050000	9.547000
0.100000	23.000000
end
# SeqScan-RingRange
0.001000	35.906000
0.002000	35.921000
0.005000	35.907000
0.010000	35.984000
0.020000	35.922000
0.050000	36.656000
0.100000	41.172000
end
# SeqScan-RingRange Intersection
0.001000	75.562000
0.002000	75.563000
0.005000	75.641000
0.010000	75.563000
0.020000	75.734000
0.050000	76.594000
0.100000	82.031000
end
# SeqScan-Range
0.001000	37.812000
0.002000	37.766000
0.005000	37.843000
0.010000	37.797000
0.020000	37.938000
0.050000	38.562000
0.100000	43.500000
end

pause -1