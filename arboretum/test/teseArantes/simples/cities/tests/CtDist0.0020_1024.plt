set title "Conjunto de Dados: Cidades  page=1024,  k=0.0020"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. M�dio de C�lculo de Dist�ncia"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8

####################
# SlimTree-KAndRange
0.001000	55.294000
0.002000	61.888000
0.005000	81.578000
0.010000	107.814000
0.020000	127.932000
0.050000	140.358000
0.100000	149.334000
end
# SlimTree-KIntersectionRange
0.001000	206.132000
0.002000	212.742000
0.005000	232.634000
0.010000	265.656000
0.020000	334.424000
0.050000	586.074000
0.100000	1116.364000
end
# SlimTree-KORRange
0.001000	148.116000
0.002000	148.116000
0.005000	148.148000
0.010000	154.448000
0.020000	201.170000
0.050000	429.346000
0.100000	921.850000
end
# SlimTree-KUnionRange
0.001000	206.132000
0.002000	212.742000
0.005000	232.634000
0.010000	265.656000
0.020000	334.424000
0.050000	586.074000
0.100000	1116.364000
end
# SeqScan-KAndRange
0.001000	5257.000000
0.002000	5257.000000
0.005000	5257.000000
0.010000	5257.000000
0.020000	5257.000000
0.050000	5257.000000
0.100000	5257.000000
end
# SeqScan-KIntersectionRange
0.001000	10514.000000
0.002000	10514.000000
0.005000	10514.000000
0.010000	10514.000000
0.020000	10514.000000
0.050000	10514.000000
0.100000	10514.000000
end
# SeqScan-KORRange
0.001000	5257.000000
0.002000	5257.000000
0.005000	5257.000000
0.010000	5257.000000
0.020000	5257.000000
0.050000	5257.000000
0.100000	5257.000000
end
# SeqScan-KUnionRange
0.001000	10514.000000
0.002000	10514.000000
0.005000	10514.000000
0.010000	10514.000000
0.020000	10514.000000
0.050000	10514.000000
0.100000	10514.000000
end

pause -1