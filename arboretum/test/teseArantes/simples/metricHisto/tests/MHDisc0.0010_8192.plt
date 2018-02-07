set title "Conjunto de Dados: metricHisto  page=8192,  k=0.0010"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	37.010000
0.002000	37.606000
0.005000	39.496000
0.010000	42.456000
0.020000	47.948000
0.050000	55.604000
0.100000	56.666000
end
# SlimTree-KIntersectionRange
0.001000	92.844000
0.002000	93.444000
0.005000	95.400000
0.010000	98.766000
0.020000	106.130000
0.050000	133.062000
0.100000	182.496000
end
# SlimTree-KORRange
0.001000	55.834000
0.002000	55.838000
0.005000	55.906000
0.010000	56.328000
0.020000	58.300000
0.050000	77.830000
0.100000	126.716000
end
# SlimTree-KUnionRange
0.001000	92.844000
0.002000	93.444000
0.005000	95.400000
0.010000	98.766000
0.020000	106.130000
0.050000	133.062000
0.100000	182.496000
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