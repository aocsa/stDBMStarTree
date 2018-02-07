set title "Conjunto de Dados: Cidades  page=1024,  k=0.0500"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. M�dio de C�lculo de Dist�ncia"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8

####################
# SlimTree-KAndRange
0.001000	55.294000
0.002000	61.888000
0.005000	81.600000
0.010000	113.924000
0.020000	180.330000
0.050000	400.642000
0.100000	551.596000
end
# SlimTree-KIntersectionRange
0.001000	716.616000
0.002000	723.226000
0.005000	743.118000
0.010000	776.140000
0.020000	844.908000
0.050000	1096.558000
0.100000	1626.848000
end
# SlimTree-KORRange
0.001000	630.476000
0.002000	630.476000
0.005000	630.476000
0.010000	630.476000
0.020000	630.476000
0.050000	649.330000
0.100000	996.856000
end
# SlimTree-KUnionRange
0.001000	716.616000
0.002000	723.226000
0.005000	743.118000
0.010000	776.140000
0.020000	844.908000
0.050000	1096.558000
0.100000	1626.848000
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