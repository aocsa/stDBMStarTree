set title "Conjunto de Dados: Cidades  page=8192, ratio (outer/inner) =0.80"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	4.047000
0.002000	4.079000
0.005000	4.312000
0.010000	4.687000
0.020000	5.484000
0.050000	8.203000
0.100000	14.531000
end
# SlimTree-RingRange Intersection
0.001000	8.203000
0.002000	8.328000
0.005000	8.703000
0.010000	9.312000
0.020000	10.563000
0.050000	14.891000
0.100000	24.641000
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
0.001000	60.953000
0.002000	60.781000
0.005000	60.610000
0.010000	60.797000
0.020000	60.891000
0.050000	60.219000
0.100000	60.828000
end
# SeqScan-RingRange Intersection
0.001000	119.235000
0.002000	119.109000
0.005000	119.157000
0.010000	119.156000
0.020000	119.093000
0.050000	119.203000
0.100000	119.703000
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