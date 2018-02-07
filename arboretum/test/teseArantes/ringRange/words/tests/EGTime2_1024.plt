set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =2.00"
set logscale y
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
2	15.187000
3	24.765000
4	47.734000
5	78.157000
6	86.250000
7	68.469000
end
# SlimTree-RingRange Intersection
2	24.640000
3	40.313000
4	107.500000
5	509.047000
6	1729.672000
7	3854.125000
end
# SlimTree-Range
2	11.922000
3	15.359000
4	27.671000
5	76.704000
6	227.813000
7	446.765000
end
# SeqScan-RingRange
2	15.688000
3	23.657000
4	44.672000
5	72.250000
6	79.406000
7	63.875000
end
# SeqScan-RingRange Intersection
2	30.344000
3	42.203000
4	109.281000
5	527.937000
6	1799.297000
7	3981.484000
end
# SeqScan-Range
2	14.547000
3	16.032000
4	26.750000
5	75.171000
6	231.672000
7	459.063000
end

pause -1