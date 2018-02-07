set title "Conjunto de Dados: Cidades  page=1024,  k=0.0050"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8

####################
# SlimTree-KAndRange
0.001000	16.338000
0.002000	16.660000
0.005000	17.876000
0.010000	20.058000
0.020000	22.994000
0.050000	24.892000
0.100000	25.460000
end
# SlimTree-KIntersectionRange
0.001000	41.894000
0.002000	42.216000
0.005000	43.432000
0.010000	45.634000
0.020000	50.902000
0.050000	70.722000
0.100000	110.664000
end
# SlimTree-KORRange
0.001000	25.556000
0.002000	25.556000
0.005000	25.556000
0.010000	25.576000
0.020000	27.912000
0.050000	45.832000
0.100000	85.204000
end
# SlimTree-KUnionRange
0.001000	41.894000
0.002000	42.216000
0.005000	43.432000
0.010000	45.634000
0.020000	50.902000
0.050000	70.722000
0.100000	110.664000
end
# SeqScan-KAndRange
0.001000	183.000000
0.002000	183.000000
0.005000	183.000000
0.010000	183.000000
0.020000	183.000000
0.050000	183.000000
0.100000	183.000000
end
# SeqScan-KIntersectionRange
0.001000	366.000000
0.002000	366.000000
0.005000	366.000000
0.010000	366.000000
0.020000	366.000000
0.050000	366.000000
0.100000	366.000000
end
# SeqScan-KORRange
0.001000	183.000000
0.002000	183.000000
0.005000	183.000000
0.010000	183.000000
0.020000	183.000000
0.050000	183.000000
0.100000	183.000000
end
# SeqScan-KUnionRange
0.001000	366.000000
0.002000	366.000000
0.005000	366.000000
0.010000	366.000000
0.020000	366.000000
0.050000	366.000000
0.100000	366.000000
end

pause -1