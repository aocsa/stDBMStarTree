set title "Conjunto de Dados: Cidades  page=4096, ratio (outer/inner) =0.20"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	4.064000
0.002000	4.180000
0.005000	4.486000
0.010000	4.990000
0.020000	6.302000
0.050000	10.962000
0.100000	17.496000
end
# SlimTree-RingRange Intersection
0.001000	8.038000
0.002000	8.180000
0.005000	8.550000
0.010000	9.170000
0.020000	10.672000
0.050000	15.954000
0.100000	23.830000
end
# SlimTree-Range
0.001000	4.064000
0.002000	4.180000
0.005000	4.486000
0.010000	4.990000
0.020000	6.302000
0.050000	10.964000
0.100000	17.528000
end
# SeqScan-RingRange
0.001000	29.000000
0.002000	29.000000
0.005000	29.000000
0.010000	29.000000
0.020000	29.000000
0.050000	29.000000
0.100000	29.000000
end
# SeqScan-RingRange Intersection
0.001000	58.000000
0.002000	58.000000
0.005000	58.000000
0.010000	58.000000
0.020000	58.000000
0.050000	58.000000
0.100000	58.000000
end
# SeqScan-Range
0.001000	29.000000
0.002000	29.000000
0.005000	29.000000
0.010000	29.000000
0.020000	29.000000
0.050000	29.000000
0.100000	29.000000
end

pause -1