set title "Conjunto de Dados: Cidades  page=1024,  k=0.0010"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8

####################
# SlimTree-KAndRange
0.001000	0.031000
0.002000	0.032000
0.005000	0.047000
0.010000	0.063000
0.020000	0.062000
0.050000	0.078000
0.100000	0.078000
end
# SlimTree-KIntersectionRange
0.001000	0.110000
0.002000	0.125000
0.005000	0.140000
0.010000	0.156000
0.020000	0.234000
0.050000	0.922000
0.100000	4.843000
end
# SlimTree-KORRange
0.001000	0.078000
0.002000	0.079000
0.005000	0.078000
0.010000	0.094000
0.020000	0.140000
0.050000	0.906000
0.100000	5.953000
end
# SlimTree-KUnionRange
0.001000	0.110000
0.002000	0.125000
0.005000	0.125000
0.010000	0.156000
0.020000	0.297000
0.050000	1.812000
0.100000	11.906000
end
# SeqScan-KAndRange
0.001000	1.000000
0.002000	0.984000
0.005000	0.984000
0.010000	1.000000
0.020000	1.016000
0.050000	1.031000
0.100000	1.094000
end
# SeqScan-KIntersectionRange
0.001000	2.343000
0.002000	2.313000
0.005000	2.329000
0.010000	2.344000
0.020000	2.437000
0.050000	3.110000
0.100000	6.969000
end
# SeqScan-KORRange
0.001000	1.078000
0.002000	1.093000
0.005000	1.063000
0.010000	1.078000
0.020000	1.157000
0.050000	1.781000
0.100000	5.625000
end
# SeqScan-KUnionRange
0.001000	2.343000
0.002000	2.344000
0.005000	2.360000
0.010000	2.375000
0.020000	2.500000
0.050000	4.016000
0.100000	14.078000
end

pause -1