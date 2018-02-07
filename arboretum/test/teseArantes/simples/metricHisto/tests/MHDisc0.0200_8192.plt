set title "Conjunto de Dados: metricHisto  page=8192,  k=0.0200"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	37.010000
0.002000	37.610000
0.005000	39.566000
0.010000	42.932000
0.020000	50.184000
0.050000	72.842000
0.100000	86.388000
end
# SlimTree-KIntersectionRange
0.001000	124.534000
0.002000	125.134000
0.005000	127.090000
0.010000	130.456000
0.020000	137.820000
0.050000	164.752000
0.100000	214.186000
end
# SlimTree-KORRange
0.001000	87.514000
0.002000	87.514000
0.005000	87.514000
0.010000	87.514000
0.020000	87.628000
0.050000	91.902000
0.100000	127.792000
end
# SlimTree-KUnionRange
0.001000	124.534000
0.002000	125.134000
0.005000	127.090000
0.010000	130.456000
0.020000	137.820000
0.050000	164.752000
0.100000	214.186000
end
# SeqScan-KAndRange
0.001000	142.000000
0.002000	142.000000
0.005000	142.000000
0.010000	142.000000
0.020000	142.000000
0.050000	142.000000
0.100000	142.000000
end
# SeqScan-KIntersectionRange
0.001000	284.000000
0.002000	284.000000
0.005000	284.000000
0.010000	284.000000
0.020000	284.000000
0.050000	284.000000
0.100000	284.000000
end
# SeqScan-KORRange
0.001000	142.000000
0.002000	142.000000
0.005000	142.000000
0.010000	142.000000
0.020000	142.000000
0.050000	142.000000
0.100000	142.000000
end
# SeqScan-KUnionRange
0.001000	284.000000
0.002000	284.000000
0.005000	284.000000
0.010000	284.000000
0.020000	284.000000
0.050000	284.000000
0.100000	284.000000
end

pause -1