set title "Conjunto de Dados: ColorHisto  page=8192,  k=0.0100"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	4.109000
0.002000	4.187000
0.005000	4.422000
0.010000	4.813000
0.020000	5.610000
0.050000	8.359000
0.100000	14.813000
end
# SlimTree-KIntersectionRange
0.001000	33.797000
0.002000	33.906000
0.005000	34.125000
0.010000	34.407000
0.020000	35.141000
0.050000	37.578000
0.100000	43.766000
end
# SlimTree-KORRange
0.001000	29.750000
0.002000	29.766000
0.005000	29.796000
0.010000	29.750000
0.020000	29.782000
0.050000	29.828000
0.100000	29.812000
end
# SlimTree-KUnionRange
0.001000	35.172000
0.002000	35.266000
0.005000	35.516000
0.010000	35.781000
0.020000	36.500000
0.050000	38.781000
0.100000	45.578000
end
# SeqScan-KAndRange
0.001000	58.407000
0.002000	59.547000
0.005000	59.312000
0.010000	58.859000
0.020000	58.703000
0.050000	59.375000
0.100000	59.312000
end
# SeqScan-KIntersectionRange
0.001000	131.750000
0.002000	131.735000
0.005000	131.796000
0.010000	131.859000
0.020000	131.828000
0.050000	131.859000
0.100000	132.734000
end
# SeqScan-KORRange
0.001000	83.719000
0.002000	83.547000
0.005000	83.547000
0.010000	83.750000
0.020000	83.734000
0.050000	83.594000
0.100000	83.563000
end
# SeqScan-KUnionRange
0.001000	133.140000
0.002000	133.203000
0.005000	133.422000
0.010000	133.297000
0.020000	133.125000
0.050000	133.109000
0.100000	134.375000
end

pause -1