set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.50"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. M�dio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	22.730000
0.002000	23.642000
0.005000	26.590000
0.010000	32.750000
0.020000	47.474000
0.050000	107.922000
0.100000	245.774000
end
# SlimTree-RingRange Intersection
0.001000	44.968000
0.002000	46.372000
0.005000	50.736000
0.010000	59.376000
0.020000	80.722000
0.050000	171.430000
0.100000	396.272000
end
# SlimTree-Range
0.001000	22.574000
0.002000	23.354000
0.005000	25.758000
0.010000	30.758000
0.020000	42.872000
0.050000	94.316000
0.100000	223.328000
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