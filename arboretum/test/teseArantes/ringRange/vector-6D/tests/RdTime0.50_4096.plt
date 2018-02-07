set title "Conjunto de Dados: Cidades  page=4096, ratio (outer/inner) =0.50"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	0.156000
0.002000	0.157000
0.005000	0.172000
0.010000	0.218000
0.020000	0.296000
0.050000	0.734000
0.100000	7.718000
end
# SlimTree-RingRange Intersection
0.001000	0.250000
0.002000	0.266000
0.005000	0.297000
0.010000	0.344000
0.020000	0.468000
0.050000	1.094000
0.100000	9.203000
end
# SlimTree-Range
0.001000	0.156000
0.002000	0.141000
0.005000	0.140000
0.010000	0.141000
0.020000	0.156000
0.050000	0.203000
0.100000	0.297000
end
# SeqScan-RingRange
0.001000	10.625000
0.002000	10.656000
0.005000	10.672000
0.010000	10.704000
0.020000	10.657000
0.050000	10.766000
0.100000	16.313000
end
# SeqScan-RingRange Intersection
0.001000	20.687000
0.002000	20.656000
0.005000	20.625000
0.010000	20.766000
0.020000	20.688000
0.050000	20.609000
0.100000	27.469000
end
# SeqScan-Range
0.001000	10.234000
0.002000	10.000000
0.005000	10.000000
0.010000	10.016000
0.020000	10.016000
0.050000	10.015000
0.100000	10.016000
end

pause -1