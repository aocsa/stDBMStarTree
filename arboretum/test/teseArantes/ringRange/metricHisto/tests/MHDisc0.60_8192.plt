set title "Conjunto de Dados: metricHisto  page=8192, ratio (outer/inner) =0.60"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	37.004000
0.002000	37.604000
0.005000	39.560000
0.010000	42.926000
0.020000	50.268000
0.050000	76.698000
0.100000	123.670000
end
# SlimTree-RingRange Intersection
0.001000	73.780000
0.002000	74.740000
0.005000	77.846000
0.010000	83.172000
0.020000	94.742000
0.050000	135.856000
0.100000	213.486000
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