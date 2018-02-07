set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.20"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	0.047000
0.002000	0.047000
0.005000	0.062000
0.010000	0.094000
0.020000	0.250000
0.050000	2.235000
0.100000	25.625000
end
# SlimTree-RingRange Intersection
0.001000	0.063000
0.002000	0.079000
0.005000	0.094000
0.010000	0.156000
0.020000	0.282000
0.050000	2.250000
0.100000	23.641000
end
# SlimTree-Range
0.001000	0.437000
0.002000	0.047000
0.005000	0.078000
0.010000	0.078000
0.020000	0.188000
0.050000	1.344000
0.100000	13.484000
end
# SeqScan-RingRange
0.001000	4.375000
0.002000	4.360000
0.005000	4.875000
0.010000	4.484000
0.020000	4.625000
0.050000	6.640000
0.100000	25.688000
end
# SeqScan-RingRange Intersection
0.001000	8.515000
0.002000	8.515000
0.005000	8.516000
0.010000	8.562000
0.020000	8.687000
0.050000	10.547000
0.100000	33.093000
end
# SeqScan-Range
0.001000	4.203000
0.002000	4.125000
0.005000	4.141000
0.010000	4.156000
0.020000	4.203000
0.050000	5.281000
0.100000	17.532000
end

pause -1