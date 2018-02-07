set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.20"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	95.574000
0.002000	113.798000
0.005000	167.318000
0.010000	262.020000
0.020000	487.098000
0.050000	1517.334000
0.100000	4198.772000
end
# SlimTree-RingRange Intersection
0.001000	176.344000
0.002000	198.384000
0.005000	263.748000
0.010000	378.836000
0.020000	647.402000
0.050000	1842.652000
0.100000	4934.234000
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