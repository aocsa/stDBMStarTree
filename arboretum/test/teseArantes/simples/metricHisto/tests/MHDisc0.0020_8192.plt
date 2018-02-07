set title "Conjunto de Dados: metricHisto  page=8192,  k=0.0020"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	37.010000
0.002000	37.606000
0.005000	39.540000
0.010000	42.704000
0.020000	48.702000
0.050000	59.400000
0.100000	60.762000
end
# SlimTree-KIntersectionRange
0.001000	97.594000
0.002000	98.194000
0.005000	100.150000
0.010000	103.516000
0.020000	110.880000
0.050000	137.812000
0.100000	187.246000
end
# SlimTree-KORRange
0.001000	60.578000
0.002000	60.582000
0.005000	60.604000
0.010000	60.824000
0.020000	62.250000
0.050000	78.534000
0.100000	126.758000
end
# SlimTree-KUnionRange
0.001000	97.594000
0.002000	98.194000
0.005000	100.150000
0.010000	103.516000
0.020000	110.880000
0.050000	137.812000
0.100000	187.246000
end
# SeqScan-KAndRange
0.001000	142.000000
0.002000	142.000000
0.005000	142.000000
0.010000	142.000000
0.020000	142.000000
0.050000	142.000000
0.100000	142.000000
end
# SeqScan-KIntersectionRange
0.001000	284.000000
0.002000	284.000000
0.005000	284.000000
0.010000	284.000000
0.020000	284.000000
0.050000	284.000000
0.100000	284.000000
end
# SeqScan-KORRange
0.001000	142.000000
0.002000	142.000000
0.005000	142.000000
0.010000	142.000000
0.020000	142.000000
0.050000	142.000000
0.100000	142.000000
end
# SeqScan-KUnionRange
0.001000	284.000000
0.002000	284.000000
0.005000	284.000000
0.010000	284.000000
0.020000	284.000000
0.050000	284.000000
0.100000	284.000000
end

pause -1