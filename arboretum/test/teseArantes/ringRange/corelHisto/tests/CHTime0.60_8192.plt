set title "Conjunto de Dados: Cidades  page=8192, ratio (outer/inner) =0.60"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	4.109000
0.002000	4.110000
0.005000	5.157000
0.010000	4.765000
0.020000	5.641000
0.050000	8.406000
0.100000	15.890000
end
# SlimTree-RingRange Intersection
0.001000	8.422000
0.002000	8.469000
0.005000	10.000000
0.010000	9.188000
0.020000	10.312000
0.050000	14.313000
0.100000	22.453000
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
0.001000	62.719000
0.002000	61.718000
0.005000	61.578000
0.010000	62.875000
0.020000	65.250000
0.050000	66.735000
0.100000	65.813000
end
# SeqScan-RingRange Intersection
0.001000	121.406000
0.002000	123.171000
0.005000	135.219000
0.010000	120.922000
0.020000	119.734000
0.050000	120.953000
0.100000	119.672000
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