set title "Conjunto de Dados: metricHisto  page=8192, ratio (outer/inner) =0.20"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	37.008000
0.002000	37.604000
0.005000	39.560000
0.010000	42.926000
0.020000	50.290000
0.050000	77.210000
0.100000	126.522000
end
# SlimTree-RingRange Intersection
0.001000	73.524000
0.002000	74.246000
0.005000	76.576000
0.010000	80.542000
0.020000	89.206000
0.050000	120.160000
0.100000	176.958000
end
# SlimTree-Range
0.001000	37.010000
0.002000	37.610000
0.005000	39.566000
0.010000	42.932000
0.020000	50.296000
0.050000	77.228000
0.100000	126.662000
end
# SeqScan-RingRange
0.001000	142.000000
0.002000	142.000000
0.005000	142.000000
0.010000	142.000000
0.020000	142.000000
0.050000	142.000000
0.100000	142.000000
end
# SeqScan-RingRange Intersection
0.001000	284.000000
0.002000	284.000000
0.005000	284.000000
0.010000	284.000000
0.020000	284.000000
0.050000	284.000000
0.100000	284.000000
end
# SeqScan-Range
0.001000	142.000000
0.002000	142.000000
0.005000	142.000000
0.010000	142.000000
0.020000	142.000000
0.050000	142.000000
0.100000	142.000000
end

pause -1