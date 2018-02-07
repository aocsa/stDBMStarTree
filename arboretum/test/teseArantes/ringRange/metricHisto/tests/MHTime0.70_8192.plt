set title "Conjunto de Dados: metricHisto  page=8192, ratio (outer/inner) =0.70"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	1.125000
0.002000	1.203000
0.005000	1.500000
0.010000	1.937000
0.020000	2.828000
0.050000	5.937000
0.100000	12.922000
end
# SlimTree-RingRange Intersection
0.001000	2.203000
0.002000	2.422000
0.005000	2.828000
0.010000	3.625000
0.020000	5.203000
0.050000	11.188000
0.100000	27.562000
end
# SlimTree-Range
0.001000	1.125000
0.002000	1.250000
0.005000	1.500000
0.010000	1.938000
0.020000	2.922000
0.050000	6.360000
0.100000	15.250000
end
# SeqScan-RingRange
0.001000	23.922000
0.002000	23.922000
0.005000	23.891000
0.010000	23.922000
0.020000	23.938000
0.050000	24.125000
0.100000	25.625000
end
# SeqScan-RingRange Intersection
0.001000	50.375000
0.002000	50.344000
0.005000	50.375000
0.010000	50.422000
0.020000	50.500000
0.050000	51.625000
0.100000	58.610000
end
# SeqScan-Range
0.001000	25.188000
0.002000	25.203000
0.005000	25.234000
0.010000	25.203000
0.020000	25.265000
0.050000	25.750000
0.100000	29.062000
end

pause -1