set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.50"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	0.047000
0.002000	0.047000
0.005000	0.063000
0.010000	0.093000
0.020000	0.187000
0.050000	1.312000
0.100000	13.266000
end
# SlimTree-RingRange Intersection
0.001000	0.079000
0.002000	0.078000
0.005000	0.110000
0.010000	0.172000
0.020000	0.359000
0.050000	3.328000
0.100000	36.797000
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
0.001000	4.828000
0.002000	4.781000
0.005000	4.516000
0.010000	4.766000
0.020000	4.657000
0.050000	5.250000
0.100000	15.640000
end
# SeqScan-RingRange Intersection
0.001000	8.515000
0.002000	8.500000
0.005000	8.531000
0.010000	8.578000
0.020000	8.750000
0.050000	11.641000
0.100000	46.562000
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