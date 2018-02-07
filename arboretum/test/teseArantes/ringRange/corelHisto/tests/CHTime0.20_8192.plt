set title "Conjunto de Dados: Cidades  page=8192, ratio (outer/inner) =0.20"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	4.094000
0.002000	4.109000
0.005000	4.343000
0.010000	4.718000
0.020000	5.516000
0.050000	8.234000
0.100000	14.656000
end
# SlimTree-RingRange Intersection
0.001000	8.172000
0.002000	8.266000
0.005000	8.515000
0.010000	8.922000
0.020000	9.782000
0.050000	12.657000
0.100000	19.109000
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
0.001000	61.062000
0.002000	60.657000
0.005000	61.032000
0.010000	60.875000
0.020000	60.875000
0.050000	60.985000
0.100000	61.094000
end
# SeqScan-RingRange Intersection
0.001000	118.765000
0.002000	119.344000
0.005000	118.735000
0.010000	119.546000
0.020000	119.718000
0.050000	118.750000
0.100000	119.406000
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