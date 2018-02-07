set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.50"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	0.047000
0.002000	0.046000
0.005000	0.047000
0.010000	0.062000
0.020000	0.109000
0.050000	0.282000
0.100000	0.859000
end
# SlimTree-RingRange Intersection
0.001000	0.078000
0.002000	0.062000
0.005000	0.078000
0.010000	0.109000
0.020000	0.156000
0.050000	0.515000
0.100000	2.281000
end
# SlimTree-Range
0.001000	0.047000
0.002000	0.032000
0.005000	0.047000
0.010000	0.078000
0.020000	0.125000
0.050000	0.625000
0.100000	3.469000
end
# SeqScan-RingRange
0.001000	0.875000
0.002000	0.875000
0.005000	0.891000
0.010000	0.891000
0.020000	0.922000
0.050000	1.125000
0.100000	1.578000
end
# SeqScan-RingRange Intersection
0.001000	1.688000
0.002000	1.688000
0.005000	1.703000
0.010000	1.719000
0.020000	1.782000
0.050000	2.125000
0.100000	4.016000
end
# SeqScan-Range
0.001000	0.984000
0.002000	0.984000
0.005000	0.984000
0.010000	1.000000
0.020000	1.078000
0.050000	1.594000
0.100000	4.359000
end

pause -1