set title "Conjunto de Dados: ColorHisto  page=8192,  k=0.0050"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	4.109000
0.002000	4.187000
0.005000	4.406000
0.010000	4.797000
0.020000	5.610000
0.050000	8.359000
0.100000	14.797000
end
# SlimTree-KIntersectionRange
0.001000	26.672000
0.002000	26.750000
0.005000	26.937000
0.010000	27.297000
0.020000	27.969000
0.050000	30.468000
0.100000	36.437000
end
# SlimTree-KORRange
0.001000	22.641000
0.002000	22.625000
0.005000	22.609000
0.010000	22.593000
0.020000	22.594000
0.050000	22.609000
0.100000	22.641000
end
# SlimTree-KUnionRange
0.001000	27.094000
0.002000	27.141000
0.005000	27.360000
0.010000	27.719000
0.020000	28.359000
0.050000	30.797000
0.100000	36.953000
end
# SeqScan-KAndRange
0.001000	59.688000
0.002000	60.032000
0.005000	59.906000
0.010000	59.437000
0.020000	59.344000
0.050000	58.797000
0.100000	59.531000
end
# SeqScan-KIntersectionRange
0.001000	123.062000
0.002000	123.188000
0.005000	123.203000
0.010000	123.375000
0.020000	123.391000
0.050000	123.329000
0.100000	123.875000
end
# SeqScan-KORRange
0.001000	74.922000
0.002000	74.875000
0.005000	74.969000
0.010000	74.891000
0.020000	74.906000
0.050000	74.922000
0.100000	74.922000
end
# SeqScan-KUnionRange
0.001000	123.640000
0.002000	123.640000
0.005000	123.640000
0.010000	123.469000
0.020000	123.422000
0.050000	123.703000
0.100000	124.250000
end

pause -1