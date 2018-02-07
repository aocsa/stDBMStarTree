set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.70"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	23.356000
0.002000	24.320000
0.005000	27.276000
0.010000	32.942000
0.020000	46.538000
0.050000	97.026000
0.100000	197.504000
end
# SlimTree-RingRange Intersection
0.001000	46.460000
0.002000	48.074000
0.005000	53.062000
0.010000	62.422000
0.020000	86.174000
0.050000	187.602000
0.100000	433.458000
end
# SlimTree-Range
0.001000	23.246000
0.002000	24.060000
0.005000	26.558000
0.010000	31.274000
0.020000	43.218000
0.050000	93.946000
0.100000	217.338000
end
# SeqScan-RingRange
0.001000	859.000000
0.002000	859.000000
0.005000	859.000000
0.010000	859.000000
0.020000	859.000000
0.050000	859.000000
0.100000	859.000000
end
# SeqScan-RingRange Intersection
0.001000	1718.000000
0.002000	1718.000000
0.005000	1718.000000
0.010000	1718.000000
0.020000	1718.000000
0.050000	1718.000000
0.100000	1718.000000
end
# SeqScan-Range
0.001000	859.000000
0.002000	859.000000
0.005000	859.000000
0.010000	859.000000
0.020000	859.000000
0.050000	859.000000
0.100000	859.000000
end

pause -1