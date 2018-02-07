set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.30"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. M�dio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	23.356000
0.002000	24.322000
0.005000	27.288000
0.010000	33.054000
0.020000	47.572000
0.050000	110.076000
0.100000	256.750000
end
# SlimTree-RingRange Intersection
0.001000	46.056000
0.002000	47.324000
0.005000	51.130000
0.010000	58.340000
0.020000	75.946000
0.050000	151.354000
0.100000	332.494000
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