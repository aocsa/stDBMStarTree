set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.30"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	0.031000
0.002000	0.047000
0.005000	0.062000
0.010000	0.094000
0.020000	0.219000
0.050000	2.265000
0.100000	27.610000
end
# SlimTree-RingRange Intersection
0.001000	0.078000
0.002000	0.078000
0.005000	0.093000
0.010000	0.140000
0.020000	0.297000
0.050000	2.734000
0.100000	31.016000
end
# SlimTree-Range
0.001000	0.281000
0.002000	0.031000
0.005000	0.062000
0.010000	0.078000
0.020000	0.172000
0.050000	1.453000
0.100000	15.953000
end
# SeqScan-RingRange
0.001000	3.547000
0.002000	3.625000
0.005000	3.547000
0.010000	3.140000
0.020000	3.391000
0.050000	4.844000
0.100000	25.875000
end
# SeqScan-RingRange Intersection
0.001000	6.265000
0.002000	6.282000
0.005000	6.282000
0.010000	6.297000
0.020000	6.438000
0.050000	8.781000
0.100000	38.219000
end
# SeqScan-Range
0.001000	3.141000
0.002000	3.094000
0.005000	3.094000
0.010000	3.110000
0.020000	3.156000
0.050000	4.328000
0.100000	19.078000
end

pause -1