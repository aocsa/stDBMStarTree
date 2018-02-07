set title "Conjunto de Dados: ColorHisto  page=8192,  k=0.0500"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. M�dio de C�lculo de Dist�ncia"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	123.982000
0.002000	139.692000
0.005000	185.992000
0.010000	262.424000
0.020000	417.210000
0.050000	878.510000
0.100000	1356.600000
end
# SlimTree-KIntersectionRange
0.001000	1589.062000
0.002000	1604.774000
0.005000	1651.110000
0.010000	1727.698000
0.020000	1883.164000
0.050000	2388.368000
0.100000	3367.214000
end
# SlimTree-KORRange
0.001000	1444.140000
0.002000	1444.140000
0.005000	1444.140000
0.010000	1444.140000
0.020000	1444.162000
0.050000	1482.568000
0.100000	1956.832000
end
# SlimTree-KUnionRange
0.001000	1589.062000
0.002000	1604.774000
0.005000	1651.110000
0.010000	1727.698000
0.020000	1883.164000
0.050000	2388.368000
0.100000	3367.214000
end
# SeqScan-KAndRange
0.001000	4247.000000
0.002000	4247.000000
0.005000	4247.000000
0.010000	4247.000000
0.020000	4247.000000
0.050000	4247.000000
0.100000	4247.000000
end
# SeqScan-KIntersectionRange
0.001000	8494.000000
0.002000	8494.000000
0.005000	8494.000000
0.010000	8494.000000
0.020000	8494.000000
0.050000	8494.000000
0.100000	8494.000000
end
# SeqScan-KORRange
0.001000	4247.000000
0.002000	4247.000000
0.005000	4247.000000
0.010000	4247.000000
0.020000	4247.000000
0.050000	4247.000000
0.100000	4247.000000
end
# SeqScan-KUnionRange
0.001000	8494.000000
0.002000	8494.000000
0.005000	8494.000000
0.010000	8494.000000
0.020000	8494.000000
0.050000	8494.000000
0.100000	8494.000000
end

pause -1