set title "Conjunto de Dados: Cidades  page=8192, ratio (outer/inner) =0.30"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	4.063000
0.002000	4.094000
0.005000	4.328000
0.010000	4.719000
0.020000	5.515000
0.050000	8.218000
0.100000	14.625000
end
# SlimTree-RingRange Intersection
0.001000	8.187000
0.002000	8.282000
0.005000	8.563000
0.010000	8.984000
0.020000	9.907000
0.050000	12.969000
0.100000	19.797000
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
0.001000	60.640000
0.002000	61.078000
0.005000	61.125000
0.010000	60.922000
0.020000	60.454000
0.050000	60.844000
0.100000	60.797000
end
# SeqScan-RingRange Intersection
0.001000	119.547000
0.002000	119.640000
0.005000	119.422000
0.010000	119.562000
0.020000	119.453000
0.050000	119.531000
0.100000	119.843000
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