set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.70"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	16.338000
0.002000	16.660000
0.005000	17.874000
0.010000	20.064000
0.020000	25.206000
0.050000	42.006000
0.100000	68.354000
end
# SlimTree-RingRange Intersection
0.001000	32.580000
0.002000	33.130000
0.005000	35.122000
0.010000	38.814000
0.020000	47.414000
0.050000	79.568000
0.100000	145.702000
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