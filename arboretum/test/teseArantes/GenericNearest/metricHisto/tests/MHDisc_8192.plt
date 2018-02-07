set title "Conjunto de Dados: Cidades  page=8192"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	55.834000
0.002000	60.584000
0.005000	69.346000
0.010000	77.172000
0.020000	87.524000
0.050000	105.290000
0.100000	123.980000
end
# SlimTree-RangeIntersection
0.001000	305.828000
0.002000	310.568000
0.005000	319.312000
0.010000	327.104000
0.020000	337.356000
0.050000	354.712000
0.100000	372.612000
end
# SeqScan-Nearest
0.001000	142.000000
0.002000	142.000000
0.005000	142.000000
0.010000	142.000000
0.020000	142.000000
0.050000	142.000000
0.100000	142.000000
end
# SeqScan-IntersectionNearest
0.001000	284.000000
0.002000	284.000000
0.005000	284.000000
0.010000	284.000000
0.020000	284.000000
0.050000	284.000000
0.100000	284.000000
end

pause -1