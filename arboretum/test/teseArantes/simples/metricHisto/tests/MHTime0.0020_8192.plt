set title "Conjunto de Dados: ColorHisto  page=8192,  k=0.0020"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	1.688000
0.002000	1.797000
0.005000	2.328000
0.010000	2.907000
0.020000	4.109000
0.050000	6.094000
0.100000	6.375000
end
# SlimTree-KIntersectionRange
0.001000	7.891000
0.002000	8.063000
0.005000	8.391000
0.010000	9.172000
0.020000	10.594000
0.050000	16.125000
0.100000	30.375000
end
# SlimTree-KORRange
0.001000	6.094000
0.002000	6.078000
0.005000	6.015000
0.010000	6.094000
0.020000	6.391000
0.050000	9.735000
0.100000	23.250000
end
# SlimTree-KUnionRange
0.001000	7.891000
0.002000	8.141000
0.005000	8.453000
0.010000	9.187000
0.020000	10.609000
0.050000	16.671000
0.100000	24.407000
end
# SeqScan-KAndRange
0.001000	37.812000
0.002000	37.781000
0.005000	37.672000
0.010000	37.812000
0.020000	37.766000
0.050000	37.906000
0.100000	38.094000
end
# SeqScan-KIntersectionRange
0.001000	76.328000
0.002000	76.484000
0.005000	76.593000
0.010000	76.578000
0.020000	76.594000
0.050000	77.906000
0.100000	83.922000
end
# SeqScan-KORRange
0.001000	38.062000
0.002000	38.063000
0.005000	38.141000
0.010000	38.062000
0.020000	38.156000
0.050000	38.812000
0.100000	43.844000
end
# SeqScan-KUnionRange
0.001000	76.500000
0.002000	76.500000
0.005000	76.578000
0.010000	76.235000
0.020000	76.688000
0.050000	55.922000
0.100000	60.046000
end

pause -1