set title "Conjunto de Dados: Cidades  page=1024,  k=0.0020"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8

####################
# SlimTree-KAndRange
0.001000	0.031000
0.002000	0.031000
0.005000	0.031000
0.010000	0.063000
0.020000	0.062000
0.050000	0.078000
0.100000	0.078000
end
# SlimTree-KIntersectionRange
0.001000	0.109000
0.002000	0.125000
0.005000	0.125000
0.010000	0.156000
0.020000	0.187000
0.050000	0.453000
0.100000	1.516000
end
# SlimTree-KORRange
0.001000	0.078000
0.002000	0.078000
0.005000	0.078000
0.010000	0.078000
0.020000	0.125000
0.050000	0.360000
0.100000	1.594000
end
# SlimTree-KUnionRange
0.001000	0.125000
0.002000	0.109000
0.005000	0.125000
0.010000	0.157000
0.020000	0.203000
0.050000	0.625000
0.100000	2.985000
end
# SeqScan-KAndRange
0.001000	0.922000
0.002000	0.922000
0.005000	0.922000
0.010000	0.922000
0.020000	0.938000
0.050000	0.953000
0.100000	1.000000
end
# SeqScan-KIntersectionRange
0.001000	1.875000
0.002000	1.875000
0.005000	1.860000
0.010000	1.875000
0.020000	1.922000
0.050000	2.172000
0.100000	3.281000
end
# SeqScan-KORRange
0.001000	0.953000
0.002000	0.953000
0.005000	0.954000
0.010000	0.953000
0.020000	0.984000
0.050000	1.234000
0.100000	2.218000
end
# SeqScan-KUnionRange
0.001000	1.891000
0.002000	1.891000
0.005000	1.859000
0.010000	1.890000
0.020000	1.954000
0.050000	2.390000
0.100000	4.859000
end

pause -1