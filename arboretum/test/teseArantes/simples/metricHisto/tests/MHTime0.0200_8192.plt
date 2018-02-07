set title "Conjunto de Dados: ColorHisto  page=8192,  k=0.0200"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	1.125000
0.002000	1.250000
0.005000	1.516000
0.010000	1.984000
0.020000	2.938000
0.050000	5.766000
0.100000	7.610000
end
# SlimTree-KIntersectionRange
0.001000	8.984000
0.002000	9.094000
0.005000	9.312000
0.010000	9.828000
0.020000	5.360000
0.050000	7.422000
0.100000	12.984000
end
# SlimTree-KORRange
0.001000	3.734000
0.002000	3.750000
0.005000	3.735000
0.010000	3.734000
0.020000	3.750000
0.050000	4.109000
0.100000	7.796000
end
# SlimTree-KUnionRange
0.001000	4.562000
0.002000	4.610000
0.005000	4.750000
0.010000	4.969000
0.020000	5.469000
0.050000	7.484000
0.100000	14.109000
end
# SeqScan-KAndRange
0.001000	25.172000
0.002000	25.140000
0.005000	25.219000
0.010000	25.156000
0.020000	25.281000
0.050000	25.421000
0.100000	25.875000
end
# SeqScan-KIntersectionRange
0.001000	51.969000
0.002000	52.000000
0.005000	52.047000
0.010000	37.094000
0.020000	26.046000
0.050000	26.610000
0.100000	29.391000
end
# SeqScan-KORRange
0.001000	13.141000
0.002000	13.140000
0.005000	13.156000
0.010000	13.141000
0.020000	13.141000
0.050000	13.391000
0.100000	14.813000
end
# SeqScan-KUnionRange
0.001000	26.219000
0.002000	26.109000
0.005000	26.125000
0.010000	26.140000
0.020000	26.250000
0.050000	26.735000
0.100000	30.516000
end

pause -1