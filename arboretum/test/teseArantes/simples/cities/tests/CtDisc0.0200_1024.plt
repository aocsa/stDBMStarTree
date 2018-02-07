set title "Conjunto de Dados: Cidades  page=1024,  k=0.0200"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8

####################
# SlimTree-KAndRange
0.001000	16.338000
0.002000	16.660000
0.005000	17.876000
0.010000	20.078000
0.020000	25.346000
0.050000	35.126000
0.100000	38.140000
end
# SlimTree-KIntersectionRange
0.001000	55.938000
0.002000	56.260000
0.005000	57.476000
0.010000	59.678000
0.020000	64.946000
0.050000	84.766000
0.100000	124.708000
end
# SlimTree-KORRange
0.001000	39.600000
0.002000	39.600000
0.005000	39.600000
0.010000	39.600000
0.020000	39.600000
0.050000	49.640000
0.100000	86.568000
end
# SlimTree-KUnionRange
0.001000	55.938000
0.002000	56.260000
0.005000	57.476000
0.010000	59.678000
0.020000	64.946000
0.050000	84.766000
0.100000	124.708000
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