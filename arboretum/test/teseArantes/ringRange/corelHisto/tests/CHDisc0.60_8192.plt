set title "Conjunto de Dados: Cidades  page=8192, ratio (outer/inner) =0.60"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. M�dio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	378.238000
0.002000	381.184000
0.005000	390.218000
0.010000	405.750000
0.020000	439.420000
0.050000	564.150000
0.100000	861.750000
end
# SlimTree-RingRange Intersection
0.001000	755.308000
0.002000	760.034000
0.005000	774.496000
0.010000	799.188000
0.020000	851.722000
0.050000	1041.022000
0.100000	1476.578000
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