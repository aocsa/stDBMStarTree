set title "Conjunto de Dados: Cidades  page=1024,  k=0.0050"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8

####################
# SlimTree-KAndRange
0.001000	0.031000
0.002000	0.032000
0.005000	0.031000
0.010000	0.063000
0.020000	0.078000
0.050000	0.109000
0.100000	0.109000
end
# SlimTree-KIntersectionRange
0.001000	0.157000
0.002000	0.157000
0.005000	0.156000
0.010000	0.172000
0.020000	0.234000
0.050000	0.500000
0.100000	1.610000
end
# SlimTree-KORRange
0.001000	0.125000
0.002000	0.109000
0.005000	0.109000
0.010000	0.109000
0.020000	0.125000
0.050000	0.359000
0.100000	1.594000
end
# SlimTree-KUnionRange
0.001000	0.171000
0.002000	0.156000
0.005000	0.172000
0.010000	0.188000
0.020000	0.250000
0.050000	0.688000
0.100000	3.047000
end
# SeqScan-KAndRange
0.001000	0.906000
0.002000	0.906000
0.005000	0.906000
0.010000	0.922000
0.020000	0.953000
0.050000	1.016000
0.100000	1.047000
end
# SeqScan-KIntersectionRange
0.001000	1.968000
0.002000	1.953000
0.005000	1.969000
0.010000	1.984000
0.020000	2.047000
0.050000	2.328000
0.100000	3.437000
end
# SeqScan-KORRange
0.001000	1.047000
0.002000	1.063000
0.005000	1.063000
0.010000	1.063000
0.020000	1.078000
0.050000	1.281000
0.100000	2.235000
end
# SeqScan-KUnionRange
0.001000	1.969000
0.002000	1.985000
0.005000	1.968000
0.010000	1.984000
0.020000	2.047000
0.050000	2.484000
0.100000	4.969000
end

pause -1