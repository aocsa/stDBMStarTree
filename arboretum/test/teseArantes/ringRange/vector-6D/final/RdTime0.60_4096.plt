set title "Conjunto de Dados: Cidades  page=4096, ratio (outer/inner) =0.60"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	0.141000
0.002000	0.141000
0.005000	0.140000
0.010000	0.157000
0.020000	0.172000
0.050000	0.219000
0.100000	0.296000
end
# SlimTree-RingRange Intersection
0.001000	0.235000
0.002000	0.250000
0.005000	0.250000
0.010000	0.265000
0.020000	0.281000
0.050000	0.360000
0.100000	0.485000
end
# SlimTree-Range
0.001000	0.141000
0.002000	0.141000
0.005000	0.141000
0.010000	0.140000
0.020000	0.156000
0.050000	0.203000
0.100000	0.281000
end
# SeqScan-RingRange
0.001000	10.015000
0.002000	10.016000
0.005000	10.078000
0.010000	10.015000
0.020000	9.953000
0.050000	9.938000
0.100000	10.125000
end
# SeqScan-RingRange Intersection
0.001000	20.328000
0.002000	20.297000
0.005000	20.219000
0.010000	20.360000
0.020000	20.312000
0.050000	20.343000
0.100000	20.312000
end
# SeqScan-Range
0.001000	11.406000
0.002000	11.484000
0.005000	11.422000
0.010000	11.391000
0.020000	11.453000
0.050000	11.438000
0.100000	11.422000
end

pause -1