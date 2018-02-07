set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.50"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	16.338000
0.002000	16.660000
0.005000	17.876000
0.010000	20.072000
0.020000	25.302000
0.050000	43.968000
0.100000	77.382000
end
# SlimTree-RingRange Intersection
0.001000	32.510000
0.002000	32.998000
0.005000	34.742000
0.010000	37.954000
0.020000	45.424000
0.050000	73.314000
0.100000	130.274000
end
# SlimTree-Range
0.001000	16.338000
0.002000	16.660000
0.005000	17.876000
0.010000	20.078000
0.020000	25.346000
0.050000	45.166000
0.100000	85.108000
end
# SeqScan-RingRange
0.001000	183.000000
0.002000	183.000000
0.005000	183.000000
0.010000	183.000000
0.020000	183.000000
0.050000	183.000000
0.100000	183.000000
end
# SeqScan-RingRange Intersection
0.001000	366.000000
0.002000	366.000000
0.005000	366.000000
0.010000	366.000000
0.020000	366.000000
0.050000	366.000000
0.100000	366.000000
end
# SeqScan-Range
0.001000	183.000000
0.002000	183.000000
0.005000	183.000000
0.010000	183.000000
0.020000	183.000000
0.050000	183.000000
0.100000	183.000000
end

pause -1