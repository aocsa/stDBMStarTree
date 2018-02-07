set title "Conjunto de Dados: Cidades  page=4096, ratio (outer/inner) =0.40"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	0.015000
0.002000	0.015000
0.005000	0.016000
0.010000	0.016000
0.020000	0.047000
0.050000	0.141000
0.100000	0.422000
end
# SlimTree-RingRange Intersection
0.001000	0.031000
0.002000	0.032000
0.005000	0.031000
0.010000	0.031000
0.020000	0.079000
0.050000	0.219000
0.100000	0.796000
end
# SlimTree-Range
0.001000	0.016000
0.002000	0.016000
0.005000	0.015000
0.010000	0.031000
0.020000	0.047000
0.050000	0.156000
0.100000	0.515000
end
# SeqScan-RingRange
0.001000	0.391000
0.002000	0.391000
0.005000	0.390000
0.010000	0.406000
0.020000	0.406000
0.050000	0.469000
0.100000	0.640000
end
# SeqScan-RingRange Intersection
0.001000	0.750000
0.002000	0.750000
0.005000	0.766000
0.010000	0.765000
0.020000	0.765000
0.050000	0.891000
0.100000	1.360000
end
# SeqScan-Range
0.001000	0.359000
0.002000	0.375000
0.005000	0.360000
0.010000	0.375000
0.020000	0.375000
0.050000	0.469000
0.100000	0.766000
end

pause -1