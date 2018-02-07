set title "Conjunto de Dados: Vector-16D  page=8192,  k=0.0200"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	22.892000
0.002000	24.010000
0.005000	27.680000
0.010000	35.082000
0.020000	52.674000
0.050000	74.326000
end
# SlimTree-KIntersectionRange
0.001000	98.448000
0.002000	99.566000
0.005000	103.236000
0.010000	110.638000
0.020000	128.230000
0.050000	185.470000
end
# SlimTree-KORRange
0.001000	75.556000
0.002000	75.556000
0.005000	75.556000
0.010000	75.556000
0.020000	75.556000
0.050000	111.144000
end
# SlimTree-KUnionRange
0.001000	98.448000
0.002000	99.566000
0.005000	103.236000
0.010000	110.638000
0.020000	128.230000
0.050000	185.470000
end
# SeqScan-KAndRange
0.001000	195.000000
0.002000	195.000000
0.005000	195.000000
0.010000	195.000000
0.020000	195.000000
0.050000	195.000000
end
# SeqScan-KIntersectionRange
0.001000	390.000000
0.002000	390.000000
0.005000	390.000000
0.010000	390.000000
0.020000	390.000000
0.050000	390.000000
end
# SeqScan-KORRange
0.001000	195.000000
0.002000	195.000000
0.005000	195.000000
0.010000	195.000000
0.020000	195.000000
0.050000	195.000000
end
# SeqScan-KUnionRange
0.001000	390.000000
0.002000	390.000000
0.005000	390.000000
0.010000	390.000000
0.020000	390.000000
0.050000	390.000000
end

pause -1