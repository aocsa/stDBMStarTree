set title "Conjunto de Dados: Cidades  page=8192"
set logscale xy
set xlabel "k"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	0.062000
0.002000	0.078000
0.005000	0.094000
0.010000	0.125000
0.020000	0.157000
end
# SlimTree-RangeIntersection
0.001000	11.140000
0.002000	12.078000
0.005000	14.968000
0.010000	19.781000
0.020000	29.266000
end
# SeqScan-Nearest
0.001000	0.516000
0.002000	0.516000
0.005000	0.531000
0.010000	0.562000
0.020000	0.656000
end
# SeqScan-NearestIntersection
0.001000	50.907000
0.002000	54.172000
0.005000	55.813000
0.010000	61.469000
0.020000	73.187000
end

pause -1