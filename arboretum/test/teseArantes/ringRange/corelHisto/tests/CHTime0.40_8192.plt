set title "Conjunto de Dados: Cidades  page=8192, ratio (outer/inner) =0.40"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	4.063000
0.002000	4.093000
0.005000	4.328000
0.010000	4.688000
0.020000	5.485000
0.050000	8.219000
0.100000	14.610000
end
# SlimTree-RingRange Intersection
0.001000	8.172000
0.002000	8.265000
0.005000	8.578000
0.010000	9.047000
0.020000	10.016000
0.050000	13.313000
0.100000	20.547000
end
# SlimTree-Range
0.001000	3.422000
0.002000	3.485000
0.005000	3.672000
0.010000	3.984000
0.020000	4.625000
0.050000	6.812000
0.100000	12.125000
end
# SeqScan-RingRange
0.001000	60.375000
0.002000	60.891000
0.005000	59.906000
0.010000	60.484000
0.020000	60.390000
0.050000	60.859000
0.100000	60.937000
end
# SeqScan-RingRange Intersection
0.001000	120.438000
0.002000	120.125000
0.005000	119.735000
0.010000	119.265000
0.020000	119.203000
0.050000	118.234000
0.100000	119.750000
end
# SeqScan-Range
0.001000	56.062000
0.002000	55.500000
0.005000	55.500000
0.010000	55.500000
0.020000	55.516000
0.050000	55.625000
0.100000	56.188000
end

pause -1