set title "Conjunto de Dados: Words  page=1024, ratio (outer/inner) =1.00"
set logscale y
set xlabel "% raio"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
2	15073.554000
3	19118.510000
4	21878.792000
5	23560.982000
6	24508.158000
7	24923.924000
end
# SlimTree-RingRange Intersection
2	25034.906000
3	34210.878000
4	41103.106000
5	45822.148000
6	49060.010000
7	51449.028000
end
# SlimTree-Range
2	15075.414000
3	19135.464000
4	21967.642000
5	23854.506000
6	25205.504000
7	26243.524000
end
# SeqScan-RingRange
2	24643.000000
3	24643.000000
4	24643.000000
5	24643.000000
6	24643.000000
7	24643.000000
end
# SeqScan-RingRange Intersection
2	49286.000000
3	49286.000000
4	49286.000000
5	49286.000000
6	49286.000000
7	49286.000000
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