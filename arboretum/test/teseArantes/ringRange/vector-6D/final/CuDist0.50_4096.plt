set title "Conjunto de Dados: Cidades  page=4096, ratio (outer/inner) =0.50"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. M�dio de C�lculo de Dist�ncia"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	16.598000
0.002000	22.406000
0.005000	40.240000
0.010000	67.756000
0.020000	121.326000
0.050000	292.816000
0.100000	504.166000
end
# SlimTree-RingRange Intersection
0.001000	30.204000
0.002000	39.034000
0.005000	65.842000
0.010000	108.302000
0.020000	190.110000
0.050000	449.300000
0.100000	851.794000
end
# SlimTree-Range
0.001000	16.612000
0.002000	22.422000
0.005000	40.298000
0.010000	68.004000
0.020000	122.106000
0.050000	298.746000
0.100000	553.048000
end
# SeqScan-RingRange
0.001000	2061.000000
0.002000	2061.000000
0.005000	2061.000000
0.010000	2061.000000
0.020000	2061.000000
0.050000	2061.000000
0.100000	2061.000000
end
# SeqScan-RingRange Intersection
0.001000	4122.000000
0.002000	4122.000000
0.005000	4122.000000
0.010000	4122.000000
0.020000	4122.000000
0.050000	4122.000000
0.100000	4122.000000
end
# SeqScan-Range
0.001000	2061.000000
0.002000	2061.000000
0.005000	2061.000000
0.010000	2061.000000
0.020000	2061.000000
0.050000	2061.000000
0.100000	2061.000000
end

pause -1