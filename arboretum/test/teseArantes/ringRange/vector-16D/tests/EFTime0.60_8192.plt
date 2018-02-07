set title "Conjunto de Dados: Cidades  page=8192, ratio (outer/inner) =0.60"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	0.156000
0.002000	0.172000
0.005000	0.235000
0.010000	0.375000
0.020000	0.735000
0.050000	6.125000
0.100000	23.203000
end
# SlimTree-RingRange Intersection
0.001000	0.250000
0.002000	0.297000
0.005000	0.406000
0.010000	0.640000
0.020000	1.234000
0.050000	11.046000
0.100000	264.453000
end
# SlimTree-Range
0.001000	0.141000
0.002000	0.156000
0.005000	0.250000
0.010000	0.407000
0.020000	0.812000
0.050000	7.875000
0.100000	65.891000
end
# SeqScan-RingRange
0.001000	5.172000
0.002000	5.156000
0.005000	5.172000
0.010000	5.171000
0.020000	5.187000
0.050000	9.032000
0.100000	21.812000
end
# SeqScan-RingRange Intersection
0.001000	10.047000
0.002000	10.094000
0.005000	10.172000
0.010000	10.063000
0.020000	10.157000
0.050000	18.204000
0.100000	311.547000
end
# SeqScan-Range
0.001000	4.969000
0.002000	4.953000
0.005000	5.031000
0.010000	4.953000
0.020000	4.985000
0.050000	10.937000
0.100000	65.203000
end

pause -1