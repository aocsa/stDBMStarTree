set title "Conjunto de Dados: Words  page=1024"
set logscale y
set xlabel "k"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
1	3.110000
2	4.219000
3	4.547000
4	4.719000
5	4.875000
6	4.938000
end
# SlimTree-RangeIntersection
1	435.594000
2	437.000000
3	436.219000
4	436.812000
5	437.593000
6	437.234000
end
# SeqScan-Nearest
1	6.140000
2	6.140000
3	6.125000
4	6.141000
5	6.140000
6	6.140000
end
# SeqScan-NearestIntersection
1	643.500000
2	643.719000
3	643.453000
4	643.235000
5	643.063000
6	642.860000
end

pause -1