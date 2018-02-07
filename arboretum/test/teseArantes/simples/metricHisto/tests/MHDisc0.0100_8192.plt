set title "Conjunto de Dados: metricHisto  page=8192,  k=0.0100"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	37.010000
0.002000	37.610000
0.005000	39.566000
0.010000	42.932000
0.020000	49.898000
0.050000	69.556000
0.100000	76.702000
end
# SlimTree-KIntersectionRange
0.001000	114.182000
0.002000	114.782000
0.005000	116.738000
0.010000	120.104000
0.020000	127.468000
0.050000	154.400000
0.100000	203.834000
end
# SlimTree-KORRange
0.001000	77.168000
0.002000	77.168000
0.005000	77.168000
0.010000	77.168000
0.020000	77.590000
0.050000	84.848000
0.100000	127.132000
end
# SlimTree-KUnionRange
0.001000	114.182000
0.002000	114.782000
0.005000	116.738000
0.010000	120.104000
0.020000	127.468000
0.050000	154.400000
0.100000	203.834000
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