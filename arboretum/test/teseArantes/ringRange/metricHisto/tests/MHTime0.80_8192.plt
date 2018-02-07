set title "Conjunto de Dados: metricHisto  page=8192, ratio (outer/inner) =0.80"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	1.125000
0.002000	1.203000
0.005000	1.500000
0.010000	1.890000
0.020000	2.813000
0.050000	5.813000
0.100000	12.266000
end
# SlimTree-RingRange Intersection
0.001000	2.250000
0.002000	2.391000
0.005000	2.922000
0.010000	3.672000
0.020000	5.484000
0.050000	11.875000
0.100000	30.890000
end
# SlimTree-Range
0.001000	1.156000
0.002000	1.235000
0.005000	1.500000
0.010000	1.954000
0.020000	2.875000
0.050000	6.375000
0.100000	15.344000
end
# SeqScan-RingRange
0.001000	23.891000
0.002000	23.891000
0.005000	23.922000
0.010000	23.969000
0.020000	23.937000
0.050000	24.062000
0.100000	25.031000
end
# SeqScan-RingRange Intersection
0.001000	50.422000
0.002000	50.375000
0.005000	50.390000
0.010000	50.469000
0.020000	50.454000
0.050000	51.875000
0.100000	61.094000
end
# SeqScan-Range
0.001000	25.172000
0.002000	25.234000
0.005000	25.234000
0.010000	25.203000
0.020000	25.281000
0.050000	25.672000
0.100000	29.062000
end

pause -1