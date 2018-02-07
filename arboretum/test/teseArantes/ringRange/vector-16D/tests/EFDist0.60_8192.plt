set title "Conjunto de Dados: Cidades  page=8192, ratio (outer/inner) =0.60"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	140.088000
0.002000	187.828000
0.005000	333.228000
0.010000	594.528000
0.020000	1224.696000
0.050000	3435.024000
0.100000	5925.074000
end
# SlimTree-RingRange Intersection
0.001000	261.532000
0.002000	337.428000
0.005000	568.948000
0.010000	977.368000
0.020000	1936.164000
0.050000	5441.796000
0.100000	10611.252000
end
# SlimTree-Range
0.001000	140.094000
0.002000	187.834000
0.005000	333.234000
0.010000	594.556000
0.020000	1225.936000
0.050000	3475.040000
0.100000	6455.326000
end
# SeqScan-RingRange
0.001000	11650.000000
0.002000	11650.000000
0.005000	11650.000000
0.010000	11650.000000
0.020000	11650.000000
0.050000	11650.000000
0.100000	11650.000000
end
# SeqScan-RingRange Intersection
0.001000	23300.000000
0.002000	23300.000000
0.005000	23300.000000
0.010000	23300.000000
0.020000	23300.000000
0.050000	23300.000000
0.100000	23300.000000
end
# SeqScan-Range
0.001000	11650.000000
0.002000	11650.000000
0.005000	11650.000000
0.010000	11650.000000
0.020000	11650.000000
0.050000	11650.000000
0.100000	11650.000000
end

pause -1