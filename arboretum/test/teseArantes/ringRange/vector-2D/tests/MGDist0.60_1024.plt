set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.60"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	95.574000
0.002000	113.798000
0.005000	167.278000
0.010000	261.286000
0.020000	477.756000
0.050000	1372.142000
0.100000	3397.092000
end
# SlimTree-RingRange Intersection
0.001000	183.806000
0.002000	213.300000
0.005000	300.000000
0.010000	451.384000
0.020000	803.540000
0.050000	2373.178000
0.100000	6490.492000
end
# SlimTree-Range
0.001000	92.780000
0.002000	108.332000
0.005000	153.736000
0.010000	233.710000
0.020000	418.046000
0.050000	1248.538000
0.100000	3423.904000
end
# SeqScan-RingRange
0.001000	27032.000000
0.002000	27032.000000
0.005000	27032.000000
0.010000	27032.000000
0.020000	27032.000000
0.050000	27032.000000
0.100000	27032.000000
end
# SeqScan-RingRange Intersection
0.001000	54064.000000
0.002000	54064.000000
0.005000	54064.000000
0.010000	54064.000000
0.020000	54064.000000
0.050000	54064.000000
0.100000	54064.000000
end
# SeqScan-Range
0.001000	27032.000000
0.002000	27032.000000
0.005000	27032.000000
0.010000	27032.000000
0.020000	27032.000000
0.050000	27032.000000
0.100000	27032.000000
end

pause -1