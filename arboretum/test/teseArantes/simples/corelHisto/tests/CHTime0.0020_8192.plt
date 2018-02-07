set title "Conjunto de Dados: ColorHisto  page=8192,  k=0.0020"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	4.093000
0.002000	4.187000
0.005000	4.422000
0.010000	4.797000
0.020000	5.594000
0.050000	8.343000
0.100000	14.563000
end
# SlimTree-KIntersectionRange
0.001000	21.860000
0.002000	21.921000
0.005000	22.141000
0.010000	22.468000
0.020000	23.203000
0.050000	25.610000
0.100000	31.453000
end
# SlimTree-KORRange
0.001000	17.766000
0.002000	17.766000
0.005000	17.734000
0.010000	17.766000
0.020000	17.750000
0.050000	17.781000
0.100000	18.032000
end
# SlimTree-KUnionRange
0.001000	21.938000
0.002000	22.015000
0.005000	22.204000
0.010000	22.531000
0.020000	23.297000
0.050000	25.687000
0.100000	31.625000
end
# SeqScan-KAndRange
0.001000	59.329000
0.002000	59.328000
0.005000	59.328000
0.010000	59.359000
0.020000	59.188000
0.050000	58.969000
0.100000	59.437000
end
# SeqScan-KIntersectionRange
0.001000	120.375000
0.002000	120.094000
0.005000	120.047000
0.010000	120.344000
0.020000	120.078000
0.050000	120.156000
0.100000	120.406000
end
# SeqScan-KORRange
0.001000	71.875000
0.002000	71.859000
0.005000	71.891000
0.010000	71.890000
0.020000	71.891000
0.050000	71.828000
0.100000	71.937000
end
# SeqScan-KUnionRange
0.001000	120.156000
0.002000	120.125000
0.005000	120.109000
0.010000	120.188000
0.020000	120.219000
0.050000	120.500000
0.100000	120.672000
end

pause -1