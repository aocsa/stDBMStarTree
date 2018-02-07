set title "Conjunto de Dados: ColorHisto  page=8192,  k=0.0010"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	1.062000
0.002000	1.641000
0.005000	2.282000
0.010000	2.906000
0.020000	3.938000
0.050000	5.391000
0.100000	5.547000
end
# SlimTree-KIntersectionRange
0.001000	7.015000
0.002000	7.140000
0.005000	7.578000
0.010000	8.250000
0.020000	9.735000
0.050000	15.110000
0.100000	29.156000
end
# SlimTree-KORRange
0.001000	5.250000
0.002000	5.250000
0.005000	5.250000
0.010000	5.344000
0.020000	5.719000
0.050000	9.547000
0.100000	23.250000
end
# SlimTree-KUnionRange
0.001000	7.032000
0.002000	7.141000
0.005000	7.578000
0.010000	8.250000
0.020000	9.750000
0.050000	15.844000
0.100000	35.641000
end
# SeqScan-KAndRange
0.001000	43.281000
0.002000	36.984000
0.005000	37.953000
0.010000	37.859000
0.020000	37.812000
0.050000	37.797000
0.100000	37.937000
end
# SeqScan-KIntersectionRange
0.001000	76.532000
0.002000	76.375000
0.005000	76.407000
0.010000	76.390000
0.020000	76.515000
0.050000	77.797000
0.100000	83.625000
end
# SeqScan-KORRange
0.001000	37.937000
0.002000	37.094000
0.005000	37.969000
0.010000	37.968000
0.020000	37.984000
0.050000	38.735000
0.100000	43.781000
end
# SeqScan-KUnionRange
0.001000	76.515000
0.002000	76.500000
0.005000	76.500000
0.010000	76.500000
0.020000	76.609000
0.050000	78.547000
0.100000	90.187000
end

pause -1