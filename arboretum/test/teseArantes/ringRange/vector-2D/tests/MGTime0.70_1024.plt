set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.70"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	0.046000
0.002000	0.047000
0.005000	0.062000
0.010000	0.078000
0.020000	0.172000
0.050000	0.828000
0.100000	6.921000
end
# SlimTree-RingRange Intersection
0.001000	0.078000
0.002000	0.079000
0.005000	0.109000
0.010000	0.172000
0.020000	0.500000
0.050000	6.797000
0.100000	83.765000
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
0.001000	3.110000
0.002000	3.625000
0.005000	3.563000
0.010000	3.312000
0.020000	3.313000
0.050000	3.969000
0.100000	9.016000
end
# SeqScan-RingRange Intersection
0.001000	6.281000
0.002000	6.281000
0.005000	6.281000
0.010000	6.344000
0.020000	6.609000
0.050000	13.032000
0.100000	95.813000
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