set title "Conjunto de Dados: ColorHisto  page=8192,  k=0.0200"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	4.110000
0.002000	4.172000
0.005000	4.421000
0.010000	4.797000
0.020000	5.594000
0.050000	8.343000
0.100000	14.859000
end
# SlimTree-KIntersectionRange
0.001000	52.531000
0.002000	52.547000
0.005000	52.766000
0.010000	53.031000
0.020000	53.844000
0.050000	56.297000
0.100000	62.437000
end
# SlimTree-KORRange
0.001000	48.500000
0.002000	48.375000
0.005000	48.344000
0.010000	48.453000
0.020000	48.500000
0.050000	48.297000
0.100000	48.437000
end
# SlimTree-KUnionRange
0.001000	57.234000
0.002000	57.328000
0.005000	57.468000
0.010000	57.844000
0.020000	58.391000
0.050000	60.079000
0.100000	67.625000
end
# SeqScan-KAndRange
0.001000	59.156000
0.002000	59.766000
0.005000	59.141000
0.010000	59.125000
0.020000	59.547000
0.050000	58.735000
0.100000	59.547000
end
# SeqScan-KIntersectionRange
0.001000	163.766000
0.002000	163.609000
0.005000	163.781000
0.010000	163.781000
0.020000	163.656000
0.050000	163.860000
0.100000	164.797000
end
# SeqScan-KORRange
0.001000	115.390000
0.002000	115.391000
0.005000	115.406000
0.010000	115.375000
0.020000	115.391000
0.050000	115.375000
0.100000	115.391000
end
# SeqScan-KUnionRange
0.001000	168.469000
0.002000	168.391000
0.005000	168.328000
0.010000	168.500000
0.020000	168.390000
0.050000	167.640000
0.100000	169.750000
end

pause -1