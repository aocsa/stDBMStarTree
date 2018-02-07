set title "Conjunto de Dados: Cidades  page=8192, ratio (outer/inner) =0.40"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	378.240000
0.002000	381.188000
0.005000	390.218000
0.010000	405.760000
0.020000	439.422000
0.050000	564.196000
0.100000	861.848000
end
# SlimTree-RingRange Intersection
0.001000	754.726000
0.002000	758.820000
0.005000	771.420000
0.010000	792.964000
0.020000	838.948000
0.050000	1003.692000
0.100000	1380.192000
end
# SlimTree-Range
0.001000	378.242000
0.002000	381.192000
0.005000	390.228000
0.010000	405.772000
0.020000	439.448000
0.050000	564.244000
0.100000	861.976000
end
# SeqScan-RingRange
0.001000	2187.000000
0.002000	2187.000000
0.005000	2187.000000
0.010000	2187.000000
0.020000	2187.000000
0.050000	2187.000000
0.100000	2187.000000
end
# SeqScan-RingRange Intersection
0.001000	4374.000000
0.002000	4374.000000
0.005000	4374.000000
0.010000	4374.000000
0.020000	4374.000000
0.050000	4374.000000
0.100000	4374.000000
end
# SeqScan-Range
0.001000	2187.000000
0.002000	2187.000000
0.005000	2187.000000
0.010000	2187.000000
0.020000	2187.000000
0.050000	2187.000000
0.100000	2187.000000
end

pause -1