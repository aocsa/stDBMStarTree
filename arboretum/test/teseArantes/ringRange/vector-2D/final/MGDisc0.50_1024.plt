set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.50"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	22.160000
0.002000	22.574000
0.005000	23.762000
0.010000	25.754000
0.020000	30.734000
0.050000	49.314000
0.100000	90.074000
end
# SlimTree-RingRange Intersection
0.001000	44.152000
0.002000	44.734000
0.005000	46.544000
0.010000	49.520000
0.020000	56.516000
0.050000	83.342000
0.100000	144.198000
end
# SlimTree-Range
0.001000	22.160000
0.002000	22.574000
0.005000	23.762000
0.010000	25.758000
0.020000	30.758000
0.050000	49.882000
0.100000	94.316000
end
# SeqScan-RingRange
0.001000	644.000000
0.002000	644.000000
0.005000	644.000000
0.010000	644.000000
0.020000	644.000000
0.050000	644.000000
0.100000	644.000000
end
# SeqScan-RingRange Intersection
0.001000	1288.000000
0.002000	1288.000000
0.005000	1288.000000
0.010000	1288.000000
0.020000	1288.000000
0.050000	1288.000000
0.100000	1288.000000
end
# SeqScan-Range
0.001000	644.000000
0.002000	644.000000
0.005000	644.000000
0.010000	644.000000
0.020000	644.000000
0.050000	644.000000
0.100000	644.000000
end

pause -1