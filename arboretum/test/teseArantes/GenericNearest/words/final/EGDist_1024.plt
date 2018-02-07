set title "Conjunto de Dados: Words  page=1024"
set logscale y
set xlabel "k"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
1	10965.494000
2	15830.442000
3	17216.362000
4	18035.320000
5	18638.456000
6	19054.718000
7	19355.036000
end
# SlimTree-NearestIntersection
1	38779.472000
2	43644.410000
3	45030.306000
4	45849.264000
5	46452.382000
6	46868.614000
7	47168.932000
end
# SeqScan-Nearest
1	24643.000000
2	24643.000000
3	24643.000000
4	24643.000000
5	24643.000000
6	24643.000000
7	24643.000000
end
# SeqScan-NearestIntersection
1	49286.000000
2	49286.000000
3	49286.000000
4	49286.000000
5	49286.000000
6	49286.000000
7	49286.000000
end

pause -1