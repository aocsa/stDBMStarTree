set title "Conjunto de Dados: Words  page=1024"
set logscale y
set xlabel "k"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
1	11828.380000
2	16093.880000
3	17331.040000
4	18004.180000
5	18523.600000
6	18816.740000
end
# SlimTree-NearestIntersection
1	39642.340000
2	43907.840000
3	45144.980000
4	45818.120000
5	46337.540000
6	46630.680000
end
# SeqScan-Nearest
1	24643.000000
2	24643.000000
3	24643.000000
4	24643.000000
5	24643.000000
6	24643.000000
end
# SeqScan-NearestIntersection
1	49286.000000
2	49286.000000
3	49286.000000
4	49286.000000
5	49286.000000
6	49286.000000
end

pause -1