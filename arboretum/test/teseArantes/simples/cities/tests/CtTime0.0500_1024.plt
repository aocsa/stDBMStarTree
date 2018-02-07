set title "Conjunto de Dados: Cidades  page=1024,  k=0.0500"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8

####################
# SlimTree-KAndRange
0.001000	0.015000
0.002000	0.032000
0.005000	0.031000
0.010000	0.047000
0.020000	0.094000
0.050000	0.328000
0.100000	0.547000
end
# SlimTree-KIntersectionRange
0.001000	0.719000
0.002000	0.719000
0.005000	0.719000
0.010000	0.735000
0.020000	0.812000
0.050000	1.360000
0.100000	3.204000
end
# SlimTree-KORRange
0.001000	0.687000
0.002000	0.687000
0.005000	0.687000
0.010000	0.672000
0.020000	0.672000
0.050000	0.703000
0.100000	1.735000
end
# SlimTree-KUnionRange
0.001000	0.859000
0.002000	0.860000
0.005000	0.844000
0.010000	0.890000
0.020000	1.047000
0.050000	1.656000
0.100000	4.141000
end
# SeqScan-KAndRange
0.001000	0.906000
0.002000	0.906000
0.005000	0.922000
0.010000	0.922000
0.020000	0.984000
0.050000	1.219000
0.100000	1.609000
end
# SeqScan-KIntersectionRange
0.001000	3.203000
0.002000	3.187000
0.005000	3.187000
0.010000	3.203000
0.020000	3.297000
0.050000	3.968000
0.100000	5.828000
end
# SeqScan-KORRange
0.001000	2.391000
0.002000	2.407000
0.005000	2.391000
0.010000	2.406000
0.020000	2.406000
0.050000	2.406000
0.100000	3.031000
end
# SeqScan-KUnionRange
0.001000	3.422000
0.002000	3.406000
0.005000	3.375000
0.010000	3.422000
0.020000	3.578000
0.050000	4.250000
0.100000	6.750000
end

pause -1