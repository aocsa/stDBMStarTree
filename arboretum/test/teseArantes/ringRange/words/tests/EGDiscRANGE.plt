set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =1.00"
set logscale y
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
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
2	1861.185000
3	2193.720000
4	2498.250000
5	2860.280000
6	3269.205000
7	3640.265000
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
2	372.000000
3	372.000000
4	372.000000
5	372.000000
6	372.000000
7	372.000000
end

pause -1