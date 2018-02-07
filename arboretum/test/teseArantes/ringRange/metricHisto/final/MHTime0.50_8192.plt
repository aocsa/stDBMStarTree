set title "Conjunto de Dados: Cidades  page=8192, ratio (outer/inner) =0.50"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	0.453000
0.002000	0.485000
0.005000	0.625000
0.010000	0.829000
0.020000	1.265000
0.050000	2.797000
0.100000	6.484000
end
# SlimTree-RingRange Intersection
0.001000	0.844000
0.002000	0.922000
0.005000	1.094000
0.010000	1.421000
0.020000	2.063000
0.050000	4.469000
0.100000	10.406000
end
# SlimTree-Range
0.001000	0.469000
0.002000	0.516000
0.005000	0.656000
0.010000	0.875000
0.020000	1.344000
0.050000	3.047000
0.100000	7.297000
end
# SeqScan-RingRange
0.001000	11.406000
0.002000	11.406000
0.005000	11.390000
0.010000	11.406000
0.020000	11.407000
0.050000	11.531000
0.100000	12.453000
end
# SeqScan-RingRange Intersection
0.001000	24.266000
0.002000	24.265000
0.005000	24.266000
0.010000	24.297000
0.020000	24.328000
0.050000	24.625000
0.100000	26.687000
end
# SeqScan-Range
0.001000	11.344000
0.002000	11.328000
0.005000	11.344000
0.010000	11.328000
0.020000	11.359000
0.050000	11.547000
0.100000	12.906000
end

pause -1