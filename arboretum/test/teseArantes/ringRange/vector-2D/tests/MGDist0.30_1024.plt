set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.30"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	95.574000
0.002000	113.798000
0.005000	167.318000
0.010000	261.980000
0.020000	486.458000
0.050000	1501.392000
0.100000	4097.398000
end
# SlimTree-RingRange Intersection
0.001000	178.240000
0.002000	202.142000
0.005000	272.968000
0.010000	396.752000
0.020000	683.964000
0.050000	1950.290000
0.100000	5232.180000
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