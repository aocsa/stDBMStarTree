set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =4.00"
set logscale y
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
2	81.859000
3	236.641000
4	414.250000
5	440.891000
6	311.390000
7	170.500000
end
# SlimTree-RingRange Intersection
2	85.953000
3	236.156000
4	483.094000
5	942.000000
6	2074.969000
7	4046.328000
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
2	74.375000
3	212.343000
4	372.500000
5	394.016000
6	286.625000
7	158.125000
end
# SeqScan-RingRange Intersection
2	90.172000
3	245.750000
4	500.547000
5	1009.843000
6	2204.563000
7	4238.844000
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