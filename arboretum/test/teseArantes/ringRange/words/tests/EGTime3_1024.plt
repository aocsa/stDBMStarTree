set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =3.00"
set logscale y
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
2	27.563000
3	72.125000
4	178.765000
5	242.485000
6	209.875000
7	133.734000
end
# SlimTree-RingRange Intersection
2	36.875000
3	89.406000
4	256.281000
5	733.250000
6	1953.703000
7	3999.203000
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
2	26.265000
3	66.188000
4	160.828000
5	220.328000
6	192.828000
7	124.422000
end
# SeqScan-RingRange Intersection
2	41.219000
3	91.157000
4	267.406000
5	769.703000
6	2029.141000
7	4171.797000
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