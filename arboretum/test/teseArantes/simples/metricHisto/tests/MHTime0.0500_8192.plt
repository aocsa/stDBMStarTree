set title "Conjunto de Dados: metricHisto  page=8192,  k=0.0500"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	0.578000
0.002000	0.609000
0.005000	0.766000
0.010000	0.985000
0.020000	1.469000
0.050000	3.047000
0.100000	4.984000
end
# SlimTree-KIntersectionRange
0.001000	6.000000
0.002000	6.031000
0.005000	6.172000
0.010000	6.375000
0.020000	6.890000
0.050000	9.032000
0.100000	15.547000
end
# SlimTree-KORRange
0.001000	5.172000
0.002000	5.172000
0.005000	5.171000
0.010000	5.156000
0.020000	5.156000
0.050000	5.359000
0.100000	8.094000
end
# SlimTree-KUnionRange
0.001000	6.375000
0.002000	6.406000
0.005000	6.516000
0.010000	6.734000
0.020000	7.250000
0.050000	9.375000
0.100000	16.125000
end
# SeqScan-KAndRange
0.001000	12.547000
0.002000	12.547000
0.005000	12.562000
0.010000	12.562000
0.020000	12.578000
0.050000	12.750000
0.100000	13.250000
end
# SeqScan-KIntersectionRange
0.001000	26.797000
0.002000	26.797000
0.005000	26.781000
0.010000	26.782000
0.020000	26.828000
0.050000	27.531000
0.100000	31.234000
end
# SeqScan-KORRange
0.001000	13.937000
0.002000	13.907000
0.005000	13.907000
0.010000	13.906000
0.020000	13.938000
0.050000	14.078000
0.100000	15.188000
end
# SeqScan-KUnionRange
0.001000	27.078000
0.002000	27.109000
0.005000	27.063000
0.010000	27.078000
0.020000	27.141000
0.050000	27.859000
0.100000	31.797000
end

pause -1