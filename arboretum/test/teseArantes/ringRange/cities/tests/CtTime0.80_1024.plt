set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.80"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	0.032000
0.002000	0.047000
0.005000	0.046000
0.010000	0.063000
0.020000	0.093000
0.050000	0.187000
0.100000	0.422000
end
# SlimTree-RingRange Intersection
0.001000	0.078000
0.002000	0.079000
0.005000	0.094000
0.010000	0.109000
0.020000	0.218000
0.050000	0.875000
0.100000	4.406000
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
0.005000	0.875000
0.010000	0.891000
0.020000	0.891000
0.050000	0.985000
0.100000	1.172000
end
# SeqScan-RingRange Intersection
0.001000	1.718000
0.002000	1.718000
0.005000	1.766000
0.010000	1.766000
0.020000	1.875000
0.050000	2.594000
0.100000	6.188000
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