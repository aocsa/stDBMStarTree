set title "Conjunto de Dados: Cidades  page=1024,  k=0.0010"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. M�dio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8

####################
# SlimTree-KAndRange
0.001000	16.338000
0.002000	16.660000
0.005000	17.838000
0.010000	18.930000
0.020000	19.546000
0.050000	19.966000
0.100000	20.476000
end
# SlimTree-KIntersectionRange
0.001000	36.320000
0.002000	36.642000
0.005000	37.858000
0.010000	40.060000
0.020000	45.328000
0.050000	65.148000
0.100000	105.090000
end
# SlimTree-KORRange
0.001000	19.982000
0.002000	19.982000
0.005000	20.032000
0.010000	21.168000
0.020000	25.858000
0.050000	45.396000
0.100000	85.124000
end
# SlimTree-KUnionRange
0.001000	36.320000
0.002000	36.642000
0.005000	37.858000
0.010000	40.060000
0.020000	45.328000
0.050000	65.148000
0.100000	105.090000
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