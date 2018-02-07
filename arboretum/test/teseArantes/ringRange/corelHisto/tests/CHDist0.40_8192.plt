set title "Conjunto de Dados: Cidades  page=8192, ratio (outer/inner) =0.40"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. M�dio de C�lculo de Dist�ncia"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	1608.462000
0.002000	1673.616000
0.005000	1868.298000
0.010000	2194.548000
0.020000	2860.114000
0.050000	5071.160000
0.100000	10090.090000
end
# SlimTree-RingRange Intersection
0.001000	3177.898000
0.002000	3269.240000
0.005000	3542.106000
0.010000	3997.736000
0.020000	4924.066000
0.050000	7932.978000
0.100000	14383.478000
end
# SlimTree-Range
0.001000	1608.494000
0.002000	1673.662000
0.005000	1868.444000
0.010000	2194.730000
0.020000	2860.584000
0.050000	5072.394000
0.100000	10098.590000
end
# SeqScan-RingRange
0.001000	67790.000000
0.002000	67790.000000
0.005000	67790.000000
0.010000	67790.000000
0.020000	67790.000000
0.050000	67790.000000
0.100000	67790.000000
end
# SeqScan-RingRange Intersection
0.001000	135580.000000
0.002000	135580.000000
0.005000	135580.000000
0.010000	135580.000000
0.020000	135580.000000
0.050000	135580.000000
0.100000	135580.000000
end
# SeqScan-Range
0.001000	67790.000000
0.002000	67790.000000
0.005000	67790.000000
0.010000	67790.000000
0.020000	67790.000000
0.050000	67790.000000
0.100000	67790.000000
end

pause -1