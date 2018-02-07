set title "Conjunto de Dados: Words  page=1024, ratio (outer/inner) =1.00"
set logscale y
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
2	1286.566000
3	1562.750000
4	1795.862000
5	1978.706000
6	2133.338000
7	2232.252000
end
# SlimTree-RingRange Intersection
2	2299.350000
3	2849.818000
4	3363.982000
5	3810.688000
6	4261.458000
7	4792.194000
end
# SlimTree-Range
2	1286.606000
3	1563.212000
4	1800.770000
5	2009.918000
6	2251.540000
7	2540.654000
end
# SeqScan-RingRange
2	372.000000
3	372.000000
4	372.000000
5	372.000000
6	372.000000
7	372.000000
end
# SeqScan-RingRange Intersection
2	744.000000
3	744.000000
4	744.000000
5	744.000000
6	744.000000
7	744.000000
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