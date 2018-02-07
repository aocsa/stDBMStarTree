set title "Conjunto de Dados: Cidades  page=1024,  k=0.0200"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8

####################
# SlimTree-KAndRange
0.001000	0.032000
0.002000	0.031000
0.005000	0.047000
0.010000	0.047000
0.020000	0.109000
0.050000	0.203000
0.100000	0.250000
end
# SlimTree-KIntersectionRange
0.001000	0.329000
0.002000	0.328000
0.005000	0.328000
0.010000	0.343000
0.020000	0.407000
0.050000	0.781000
0.100000	2.109000
end
# SlimTree-KORRange
0.001000	0.282000
0.002000	0.281000
0.005000	0.281000
0.010000	0.281000
0.020000	0.297000
0.050000	0.422000
0.100000	1.609000
end
# SlimTree-KUnionRange
0.001000	0.359000
0.002000	0.359000
0.005000	0.375000
0.010000	0.406000
0.020000	0.485000
0.050000	0.906000
0.100000	3.359000
end
# SeqScan-KAndRange
0.001000	0.906000
0.002000	0.891000
0.005000	0.906000
0.010000	0.922000
0.020000	0.969000
0.050000	1.141000
0.100000	1.296000
end
# SeqScan-KIntersectionRange
0.001000	2.343000
0.002000	2.360000
0.005000	2.344000
0.010000	2.375000
0.020000	2.422000
0.050000	2.828000
0.100000	4.203000
end
# SeqScan-KORRange
0.001000	1.437000
0.002000	1.469000
0.005000	1.438000
0.010000	1.438000
0.020000	1.468000
0.050000	1.547000
0.100000	2.454000
end
# SeqScan-KUnionRange
0.001000	2.391000
0.002000	2.391000
0.005000	2.375000
0.010000	2.390000
0.020000	2.500000
0.050000	2.938000
0.100000	5.500000
end

pause -1