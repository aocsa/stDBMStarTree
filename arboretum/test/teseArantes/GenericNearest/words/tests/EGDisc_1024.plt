set title "Conjunto de Dados: Words  page=1024"
set logscale y
set xlabel "k"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
1	1146.640000
2	1375.540000
3	1448.300000
4	1489.000000
5	1525.260000
6	1542.580000
end
# SlimTree-RangeIntersection
1	4318.600000
2	4547.500000
3	4620.260000
4	4660.960000
5	4697.220000
6	4714.540000
end
# SeqScan-Nearest
1	372.000000
2	372.000000
3	372.000000
4	372.000000
5	372.000000
6	372.000000
end
# SeqScan-IntersectionNearest
1	744.000000
2	744.000000
3	744.000000
4	744.000000
5	744.000000
6	744.000000
end

pause -1