set title "Conjunto de Dados: Vector-16D  page=8192,  k=0.0010"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	140.088000
0.002000	187.828000
0.005000	333.228000
0.010000	594.020000
0.020000	1039.222000
0.050000	1129.158000
end
# SlimTree-KIntersectionRange
0.001000	1271.640000
0.002000	1319.380000
0.005000	1464.780000
0.010000	1726.102000
0.020000	2357.482000
0.050000	4606.586000
end
# SlimTree-KORRange
0.001000	1129.696000
0.002000	1129.696000
0.005000	1129.696000
0.010000	1130.208000
0.020000	1315.414000
0.050000	3436.352000
end
# SlimTree-KUnionRange
0.001000	1271.640000
0.002000	1319.380000
0.005000	1464.780000
0.010000	1726.102000
0.020000	2357.482000
0.050000	4606.586000
end
# SeqScan-KAndRange
0.001000	11650.000000
0.002000	11650.000000
0.005000	11650.000000
0.010000	11650.000000
0.020000	11650.000000
0.050000	11650.000000
end
# SeqScan-KIntersectionRange
0.001000	23300.000000
0.002000	23300.000000
0.005000	23300.000000
0.010000	23300.000000
0.020000	23300.000000
0.050000	23300.000000
end
# SeqScan-KORRange
0.001000	11650.000000
0.002000	11650.000000
0.005000	11650.000000
0.010000	11650.000000
0.020000	11650.000000
0.050000	11650.000000
end
# SeqScan-KUnionRange
0.001000	23300.000000
0.002000	23300.000000
0.005000	23300.000000
0.010000	23300.000000
0.020000	23300.000000
0.050000	23300.000000
end

pause -1