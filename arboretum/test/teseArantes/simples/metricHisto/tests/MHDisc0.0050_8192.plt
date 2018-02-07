set title "Conjunto de Dados: metricHisto  page=8192,  k=0.0050"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	37.010000
0.002000	37.610000
0.005000	39.566000
0.010000	42.912000
0.020000	49.432000
0.050000	65.556000
0.100000	69.174000
end
# SlimTree-KIntersectionRange
0.001000	106.356000
0.002000	106.956000
0.005000	108.912000
0.010000	112.278000
0.020000	119.642000
0.050000	146.574000
0.100000	196.008000
end
# SlimTree-KORRange
0.001000	69.346000
0.002000	69.346000
0.005000	69.346000
0.010000	69.374000
0.020000	70.212000
0.050000	81.032000
0.100000	126.836000
end
# SlimTree-KUnionRange
0.001000	106.356000
0.002000	106.956000
0.005000	108.912000
0.010000	112.278000
0.020000	119.642000
0.050000	146.574000
0.100000	196.008000
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