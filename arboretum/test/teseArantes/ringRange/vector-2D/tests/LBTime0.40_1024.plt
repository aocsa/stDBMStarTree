set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.40"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	0.047000
0.002000	0.046000
0.005000	0.062000
0.010000	0.094000
0.020000	0.204000
0.050000	1.609000
0.100000	17.610000
end
# SlimTree-RingRange Intersection
0.001000	0.078000
0.002000	0.078000
0.005000	0.109000
0.010000	0.156000
0.020000	0.328000
0.050000	2.719000
0.100000	29.125000
end
# SlimTree-Range
0.001000	0.437000
0.002000	0.047000
0.005000	0.078000
0.010000	0.078000
0.020000	0.188000
0.050000	1.344000
0.100000	13.484000
end
# SeqScan-RingRange
0.001000	4.157000
0.002000	4.704000
0.005000	4.469000
0.010000	4.546000
0.020000	4.328000
0.050000	5.984000
0.100000	19.125000
end
# SeqScan-RingRange Intersection
0.001000	8.500000
0.002000	8.516000
0.005000	8.500000
0.010000	8.563000
0.020000	8.687000
0.050000	11.000000
0.100000	38.438000
end
# SeqScan-Range
0.001000	4.203000
0.002000	4.125000
0.005000	4.141000
0.010000	4.156000
0.020000	4.203000
0.050000	5.281000
0.100000	17.532000
end

pause -1