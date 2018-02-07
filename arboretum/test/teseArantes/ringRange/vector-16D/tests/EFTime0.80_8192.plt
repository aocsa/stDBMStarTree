set title "Conjunto de Dados: Cidades  page=8192, ratio (outer/inner) =0.80"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	0.156000
0.002000	0.156000
0.005000	0.234000
0.010000	0.391000
0.020000	0.735000
0.050000	3.141000
0.100000	6.390000
end
# SlimTree-RingRange Intersection
0.001000	0.250000
0.002000	0.297000
0.005000	0.438000
0.010000	0.703000
0.020000	1.391000
0.050000	23.297000
0.100000	803.375000
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
0.001000	5.141000
0.002000	5.157000
0.005000	5.156000
0.010000	5.156000
0.020000	5.171000
0.050000	6.469000
0.100000	8.704000
end
# SeqScan-RingRange Intersection
0.001000	10.078000
0.002000	10.093000
0.005000	10.094000
0.010000	10.093000
0.020000	10.156000
0.050000	30.453000
0.100000	902.641000
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