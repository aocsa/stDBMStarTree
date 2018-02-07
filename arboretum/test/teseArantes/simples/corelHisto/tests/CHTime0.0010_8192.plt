set title "Conjunto de Dados: ColorHisto  page=8192,  k=0.0010"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	4.125000
0.002000	4.188000
0.005000	4.422000
0.010000	4.781000
0.020000	5.610000
0.050000	8.360000
0.100000	14.250000
end
# SlimTree-KIntersectionRange
0.001000	19.532000
0.002000	19.625000
0.005000	19.812000
0.010000	20.172000
0.020000	20.813000
0.050000	23.265000
0.100000	29.078000
end
# SlimTree-KORRange
0.001000	15.437000
0.002000	15.438000
0.005000	15.437000
0.010000	15.438000
0.020000	15.437000
0.050000	15.484000
0.100000	16.063000
end
# SlimTree-KUnionRange
0.001000	19.594000
0.002000	19.640000
0.005000	19.875000
0.010000	20.203000
0.020000	20.890000
0.050000	23.297000
0.100000	29.188000
end
# SeqScan-KAndRange
0.001000	59.750000
0.002000	59.406000
0.005000	59.281000
0.010000	59.422000
0.020000	59.468000
0.050000	59.390000
0.100000	59.500000
end
# SeqScan-KIntersectionRange
0.001000	119.343000
0.002000	119.282000
0.005000	119.375000
0.010000	119.328000
0.020000	119.156000
0.050000	119.407000
0.100000	119.719000
end
# SeqScan-KORRange
0.001000	71.109000
0.002000	71.141000
0.005000	71.156000
0.010000	71.047000
0.020000	71.094000
0.050000	71.094000
0.100000	71.140000
end
# SeqScan-KUnionRange
0.001000	119.469000
0.002000	119.500000
0.005000	119.672000
0.010000	119.563000
0.020000	119.407000
0.050000	119.218000
0.100000	119.797000
end

pause -1