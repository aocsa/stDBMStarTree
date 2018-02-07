set title "Conjunto de Dados: Cidades  page=8192, ratio (outer/inner) =0.70"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	4.047000
0.002000	4.109000
0.005000	4.359000
0.010000	5.047000
0.020000	5.563000
0.050000	8.329000
0.100000	14.735000
end
# SlimTree-RingRange Intersection
0.001000	8.203000
0.002000	8.391000
0.005000	8.765000
0.010000	9.343000
0.020000	10.563000
0.050000	15.172000
0.100000	27.453000
end
# SlimTree-Range
0.001000	3.422000
0.002000	3.485000
0.005000	3.672000
0.010000	3.984000
0.020000	4.625000
0.050000	6.812000
0.100000	12.125000
end
# SeqScan-RingRange
0.001000	61.406000
0.002000	62.907000
0.005000	63.094000
0.010000	61.546000
0.020000	62.312000
0.050000	77.890000
0.100000	61.906000
end
# SeqScan-RingRange Intersection
0.001000	122.406000
0.002000	120.547000
0.005000	121.485000
0.010000	122.172000
0.020000	125.000000
0.050000	120.250000
0.100000	121.359000
end
# SeqScan-Range
0.001000	56.062000
0.002000	55.500000
0.005000	55.500000
0.010000	55.500000
0.020000	55.516000
0.050000	55.625000
0.100000	56.188000
end

pause -1