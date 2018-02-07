set title "Conjunto de Dados: metricHisto  page=8192,  k=0.0100"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	1.125000
0.002000	1.203000
0.005000	1.547000
0.010000	2.000000
0.020000	2.875000
0.050000	5.313000
0.100000	6.297000
end
# SlimTree-KIntersectionRange
0.001000	7.500000
0.002000	7.625000
0.005000	7.828000
0.010000	8.265000
0.020000	9.265000
0.050000	13.250000
0.100000	23.641000
end
# SlimTree-KORRange
0.001000	6.078000
0.002000	6.109000
0.005000	6.109000
0.010000	6.110000
0.020000	6.187000
0.050000	7.297000
0.100000	15.547000
end
# SlimTree-KUnionRange
0.001000	7.578000
0.002000	7.719000
0.005000	7.937000
0.010000	8.375000
0.020000	9.375000
0.050000	13.375000
0.100000	26.672000
end
# SeqScan-KAndRange
0.001000	25.187000
0.002000	25.188000
0.005000	25.187000
0.010000	24.891000
0.020000	25.234000
0.050000	25.328000
0.100000	25.625000
end
# SeqScan-KIntersectionRange
0.001000	51.422000
0.002000	51.484000
0.005000	51.485000
0.010000	51.485000
0.020000	51.672000
0.050000	52.750000
0.100000	57.547000
end
# SeqScan-KORRange
0.001000	25.875000
0.002000	25.922000
0.005000	25.828000
0.010000	25.875000
0.020000	25.828000
0.050000	26.328000
0.100000	29.532000
end
# SeqScan-KUnionRange
0.001000	51.281000
0.002000	51.516000
0.005000	51.453000
0.010000	51.500000
0.020000	51.735000
0.050000	52.765000
0.100000	60.547000
end

pause -1