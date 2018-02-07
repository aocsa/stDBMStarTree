set title "Conjunto de Dados: ColorHisto  page=8192,  k=0.0500"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, '-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, '-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, '-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, '-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8####################
# SlimTree-KAndRange
0.001000	4.110000
0.002000	4.172000
0.005000	4.422000
0.010000	4.813000
0.020000	5.594000
0.050000	8.359000
0.100000	14.812000
end
# SlimTree-KIntersectionRange
0.001000	180.094000
0.002000	181.422000
0.005000	180.688000
0.010000	180.875000
0.020000	181.250000
0.050000	185.046000
0.100000	190.938000
end
# SlimTree-KORRange
0.001000	176.156000
0.002000	177.438000
0.005000	177.531000
0.010000	177.140000
0.020000	177.453000
0.050000	177.531000
0.100000	177.610000
end
# SlimTree-KUnionRange
0.001000	210.375000
0.002000	210.172000
0.005000	211.406000
0.010000	211.156000
0.020000	210.266000
0.050000	205.516000
0.100000	210.125000
end
# SeqScan-KAndRange
0.001000	57.859000
0.002000	57.875000
0.005000	57.859000
0.010000	57.890000
0.020000	58.875000
0.050000	59.063000
0.100000	58.938000
end
# SeqScan-KIntersectionRange
0.001000	397.234000
0.002000	398.890000
0.005000	397.734000
0.010000	397.532000
0.020000	397.875000
0.050000	399.000000
0.100000	399.719000
end
# SeqScan-KORRange
0.001000	345.609000
0.002000	349.422000
0.005000	348.672000
0.010000	347.766000
0.020000	348.641000
0.050000	347.734000
0.100000	348.453000
end
# SeqScan-KUnionRange
0.001000	426.312000
0.002000	425.141000
0.005000	426.719000
0.010000	425.953000
0.020000	425.578000
0.050000	419.281000
0.100000	419.203000
end

pause -1