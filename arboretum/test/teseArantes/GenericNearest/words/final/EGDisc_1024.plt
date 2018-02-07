set title "Conjunto de Dados: Words  page=1024"
set logscale y
set xlabel "k"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
1	1108.456000
2	1361.828000
3	1445.618000
4	1497.792000
5	1536.614000
6	1563.566000
7	1583.250000
end
# SlimTree-RangeIntersection
1	4280.434000
2	4533.798000
3	4617.570000
4	4669.744000
5	4708.552000
6	4735.478000
7	4755.162000
end
# SeqScan-Nearest
1	372.000000
2	372.000000
3	372.000000
4	372.000000
5	372.000000
6	372.000000
7	372.000000
end
# SeqScan-IntersectionNearest
1	744.000000
2	744.000000
3	744.000000
4	744.000000
5	744.000000
6	744.000000
7	744.000000
end

pause -1