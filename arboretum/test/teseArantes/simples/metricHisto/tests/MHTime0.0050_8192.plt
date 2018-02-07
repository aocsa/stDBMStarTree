set title "Conjunto de Dados: ColorHisto  page=8192,  k=0.0050"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	1.125000
0.002000	1.250000
0.005000	1.500000
0.010000	1.984000
0.020000	2.812000
0.050000	4.797000
0.100000	5.343000
end
# SlimTree-KIntersectionRange
0.001000	6.484000
0.002000	6.547000
0.005000	6.813000
0.010000	7.218000
0.020000	8.203000
0.050000	11.984000
0.100000	21.703000
end
# SlimTree-KORRange
0.001000	5.079000
0.002000	5.094000
0.005000	5.156000
0.010000	5.125000
0.020000	5.265000
0.050000	6.766000
0.100000	15.547000
end
# SlimTree-KUnionRange
0.001000	6.485000
0.002000	6.578000
0.005000	6.797000
0.010000	7.265000
0.020000	8.282000
0.050000	12.328000
0.100000	25.547000
end
# SeqScan-KAndRange
0.001000	25.203000
0.002000	25.156000
0.005000	25.219000
0.010000	25.157000
0.020000	25.219000
0.050000	25.297000
0.100000	25.438000
end
# SeqScan-KIntersectionRange
0.001000	51.141000
0.002000	51.187000
0.005000	51.219000
0.010000	51.219000
0.020000	51.344000
0.050000	52.391000
0.100000	56.578000
end
# SeqScan-KORRange
0.001000	25.562000
0.002000	25.547000
0.005000	25.562000
0.010000	25.532000
0.020000	25.625000
0.050000	26.062000
0.100000	29.375000
end
# SeqScan-KUnionRange
0.001000	51.281000
0.002000	51.234000
0.005000	51.235000
0.010000	51.250000
0.020000	51.406000
0.050000	52.500000
0.100000	60.187000
end

pause -1