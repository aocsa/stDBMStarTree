set title "Conjunto de Dados: metricHisto  page=8192, ratio (outer/inner) =0.50"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	1.687000
0.002000	1.797000
0.005000	2.265000
0.010000	2.906000
0.020000	4.313000
0.050000	6.125000
0.100000	14.188000
end
# SlimTree-RingRange Intersection
0.001000	2.188000
0.002000	2.359000
0.005000	2.797000
0.010000	3.484000
0.020000	4.797000
0.050000	9.922000
0.100000	22.578000
end
# SlimTree-Range
0.001000	1.125000
0.002000	1.204000
0.005000	1.547000
0.010000	1.938000
0.020000	2.922000
0.050000	6.406000
0.100000	15.297000
end
# SeqScan-RingRange
0.001000	35.922000
0.002000	35.844000
0.005000	35.860000
0.010000	35.828000
0.020000	30.265000
0.050000	24.328000
0.100000	26.672000
end
# SeqScan-RingRange Intersection
0.001000	50.375000
0.002000	50.328000
0.005000	50.328000
0.010000	50.375000
0.020000	50.422000
0.050000	51.250000
0.100000	55.813000
end
# SeqScan-Range
0.001000	25.187000
0.002000	25.156000
0.005000	25.218000
0.010000	25.172000
0.020000	25.203000
0.050000	25.734000
0.100000	29.078000
end

pause -1