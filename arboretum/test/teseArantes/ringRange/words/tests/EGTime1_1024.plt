set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =1.00"
set logscale y
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
2	11.844000
3	14.140000
4	17.016000
5	20.453000
6	22.015000
7	21.203000
end
# SlimTree-RingRange Intersection
2	21.141000
3	28.000000
4	57.266000
5	348.375000
6	1486.656000
7	3623.922000
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
2	14.297000
3	14.750000
4	16.328000
5	18.907000
6	20.000000
7	19.078000
end
# SeqScan-RingRange Intersection
2	28.781000
3	31.266000
4	58.187000
5	357.063000
6	1527.187000
7	3725.297000
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