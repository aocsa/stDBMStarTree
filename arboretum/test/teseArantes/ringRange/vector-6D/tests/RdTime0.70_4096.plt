set title "Conjunto de Dados: Cidades  page=4096, ratio (outer/inner) =0.70"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	0.157000
0.002000	0.157000
0.005000	0.172000
0.010000	0.219000
0.020000	0.297000
0.050000	0.719000
0.100000	5.265000
end
# SlimTree-RingRange Intersection
0.001000	0.266000
0.002000	0.266000
0.005000	0.297000
0.010000	0.359000
0.020000	0.500000
0.050000	1.235000
0.100000	13.172000
end
# SlimTree-Range
0.001000	0.156000
0.002000	0.141000
0.005000	0.140000
0.010000	0.141000
0.020000	0.156000
0.050000	0.203000
0.100000	0.297000
end
# SeqScan-RingRange
0.001000	10.593000
0.002000	10.671000
0.005000	10.641000
0.010000	10.656000
0.020000	10.656000
0.050000	10.750000
0.100000	14.063000
end
# SeqScan-RingRange Intersection
0.001000	20.734000
0.002000	20.609000
0.005000	20.531000
0.010000	20.735000
0.020000	20.687000
0.050000	20.578000
0.100000	31.281000
end
# SeqScan-Range
0.001000	10.234000
0.002000	10.000000
0.005000	10.000000
0.010000	10.016000
0.020000	10.016000
0.050000	10.015000
0.100000	10.016000
end

pause -1