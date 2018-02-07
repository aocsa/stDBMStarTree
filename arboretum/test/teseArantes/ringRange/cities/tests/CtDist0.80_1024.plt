set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.80"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	55.294000
0.002000	61.888000
0.005000	81.600000
0.010000	113.908000
0.020000	178.450000
0.050000	372.832000
0.100000	657.270000
end
# SlimTree-RingRange Intersection
0.001000	109.336000
0.002000	121.198000
0.005000	156.972000
0.010000	216.342000
0.020000	338.946000
0.050000	777.970000
0.100000	1711.696000
end
# SlimTree-Range
0.001000	55.334000
0.002000	61.944000
0.005000	81.836000
0.010000	114.858000
0.020000	183.626000
0.050000	435.276000
0.100000	965.566000
end
# SeqScan-RingRange
0.001000	5257.000000
0.002000	5257.000000
0.005000	5257.000000
0.010000	5257.000000
0.020000	5257.000000
0.050000	5257.000000
0.100000	5257.000000
end
# SeqScan-RingRange Intersection
0.001000	10514.000000
0.002000	10514.000000
0.005000	10514.000000
0.010000	10514.000000
0.020000	10514.000000
0.050000	10514.000000
0.100000	10514.000000
end
# SeqScan-Range
0.001000	5257.000000
0.002000	5257.000000
0.005000	5257.000000
0.010000	5257.000000
0.020000	5257.000000
0.050000	5257.000000
0.100000	5257.000000
end

pause -1