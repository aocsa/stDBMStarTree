set title "Conjunto de Dados: Cidades  page=8192"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	1116.420000
0.002000	1249.440000
0.005000	1475.940000
0.010000	1700.540000
0.020000	2007.780000
end
# SlimTree-NearestIntersection
0.001000	13088.420000
0.002000	13221.440000
0.005000	13447.680000
0.010000	13671.140000
0.020000	13974.780000
end
# SeqScan-Nearest
0.001000	11650.000000
0.002000	11650.000000
0.005000	11650.000000
0.010000	11650.000000
0.020000	11650.000000
end
# SeqScan-NearestIntersection
0.001000	23300.000000
0.002000	23300.000000
0.005000	23300.000000
0.010000	23300.000000
0.020000	23300.000000
end

pause -1