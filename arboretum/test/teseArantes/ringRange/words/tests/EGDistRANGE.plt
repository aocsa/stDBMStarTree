set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =1.00"
set logscale y
set xlabel "% raio"
set ylabel "Nro. M�dio de C�lculo de Dist�ncia"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
2	0.000000
3	0.000000
4	0.000000
5	0.000000
6	0.000000
7	0.000000
end
# SlimTree-RingRange Intersection
2	0.000000
3	0.000000
4	0.000000
5	0.000000
6	0.000000
7	0.000000
end
# SlimTree-Range
2	18923.470000
3	21800.425000
4	23811.240000
5	25390.010000
6	26678.000000
7	27633.535000
end
# SeqScan-RingRange
2	0.000000
3	0.000000
4	0.000000
5	0.000000
6	0.000000
7	0.000000
end
# SeqScan-RingRange Intersection
2	0.000000
3	0.000000
4	0.000000
5	0.000000
6	0.000000
7	0.000000
end
# SeqScan-Range
2	24643.000000
3	24643.000000
4	24643.000000
5	24643.000000
6	24643.000000
7	24643.000000
end

pause -1