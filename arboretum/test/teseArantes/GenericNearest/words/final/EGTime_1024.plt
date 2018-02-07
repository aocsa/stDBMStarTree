set title "Conjunto de Dados: Words  page=1024"
set logscale y
set xlabel "k"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
1	28.531000
2	41.219000
3	44.859000
4	47.265000
5	48.469000
6	49.469000
7	50.110000
end
# SlimTree-RangeIntersection
1	4354.453000
2	4368.032000
3	4372.735000
4	4376.422000
5	4378.797000
6	4381.125000
7	4383.547000
end
# SeqScan-Nearest
1	59.922000
2	59.625000
3	59.657000
4	59.688000
5	59.656000
6	59.718000
7	59.875000
end
# SeqScan-NearestIntersection
1	6390.515000
2	6386.015000
3	6384.312000
4	6388.547000
5	6391.375000
6	6394.859000
7	6391.250000
end

pause -1