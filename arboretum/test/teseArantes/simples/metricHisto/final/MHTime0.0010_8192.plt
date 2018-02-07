set title "Conjunto de Dados: ColorHisto  page=8192,  k=0.0010"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	0.468000
0.002000	0.532000
0.005000	0.656000
0.010000	0.844000
0.020000	1.203000
0.050000	1.672000
0.100000	1.734000
end
# SlimTree-KIntersectionRange
0.001000	2.125000
0.002000	2.172000
0.005000	2.281000
0.010000	2.500000
0.020000	2.953000
0.050000	4.703000
0.100000	9.140000
end
# SlimTree-KORRange
0.001000	1.625000
0.002000	1.610000
0.005000	1.625000
0.010000	1.656000
0.020000	1.781000
0.050000	3.000000
0.100000	7.282000
end
# SlimTree-KUnionRange
0.001000	2.125000
0.002000	2.172000
0.005000	2.297000
0.010000	2.516000
0.020000	2.984000
0.050000	4.891000
0.100000	11.172000
end
# SeqScan-KAndRange
0.001000	12.453000
0.002000	12.453000
0.005000	12.453000
0.010000	12.469000
0.020000	12.453000
0.050000	12.469000
0.100000	12.500000
end
# SeqScan-KIntersectionRange
0.001000	25.156000
0.002000	25.172000
0.005000	25.156000
0.010000	25.188000
0.020000	25.203000
0.050000	25.469000
0.100000	27.110000
end
# SeqScan-KORRange
0.001000	12.515000
0.002000	12.562000
0.005000	12.547000
0.010000	12.563000
0.020000	12.547000
0.050000	12.734000
0.100000	14.093000
end
# SeqScan-KUnionRange
0.001000	25.172000
0.002000	25.187000
0.005000	25.172000
0.010000	25.187000
0.020000	25.219000
0.050000	25.672000
0.100000	29.218000
end

pause -1