set title "Conjunto de Dados: Cidades  page=8192, ratio (outer/inner) =0.30"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	22.892000
0.002000	24.010000
0.005000	27.680000
0.010000	35.082000
0.020000	52.674000
0.050000	109.912000
0.100000	184.302000
end
# SlimTree-RingRange Intersection
0.001000	45.036000
0.002000	46.492000
0.005000	51.080000
0.010000	60.240000
0.020000	81.736000
0.050000	153.376000
0.100000	256.562000
end
# SlimTree-Range
0.001000	22.892000
0.002000	24.010000
0.005000	27.680000
0.010000	35.082000
0.020000	52.674000
0.050000	109.914000
0.100000	184.390000
end
# SeqScan-RingRange
0.001000	195.000000
0.002000	195.000000
0.005000	195.000000
0.010000	195.000000
0.020000	195.000000
0.050000	195.000000
0.100000	195.000000
end
# SeqScan-RingRange Intersection
0.001000	390.000000
0.002000	390.000000
0.005000	390.000000
0.010000	390.000000
0.020000	390.000000
0.050000	390.000000
0.100000	390.000000
end
# SeqScan-Range
0.001000	195.000000
0.002000	195.000000
0.005000	195.000000
0.010000	195.000000
0.020000	195.000000
0.050000	195.000000
0.100000	195.000000
end

pause -1