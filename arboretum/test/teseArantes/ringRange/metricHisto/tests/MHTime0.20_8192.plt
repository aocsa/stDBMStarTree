set title "Conjunto de Dados: metricHisto  page=8192, ratio (outer/inner) =0.20"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	0.641000
0.002000	0.656000
0.005000	0.813000
0.010000	1.047000
0.020000	1.516000
0.050000	6.828000
0.100000	27.063000
end
# SlimTree-RingRange Intersection
0.001000	3.468000
0.002000	3.469000
0.005000	3.937000
0.010000	4.813000
0.020000	6.547000
0.050000	12.578000
0.100000	27.484000
end
# SlimTree-Range
0.001000	1.765000
0.002000	1.875000
0.005000	2.250000
0.010000	2.985000
0.020000	4.328000
0.050000	9.563000
0.100000	22.719000
end
# SeqScan-RingRange
0.001000	12.969000
0.002000	17.109000
0.005000	12.812000
0.010000	12.672000
0.020000	24.437000
0.050000	30.125000
0.100000	37.656000
end
# SeqScan-RingRange Intersection
0.001000	76.313000
0.002000	75.703000
0.005000	75.828000
0.010000	75.750000
0.020000	75.734000
0.050000	76.485000
0.100000	81.344000
end
# SeqScan-Range
0.001000	37.891000
0.002000	37.969000
0.005000	37.968000
0.010000	37.969000
0.020000	37.968000
0.050000	38.609000
0.100000	43.266000
end

pause -1