set title "EigenFaces: Nearest Queries"
set logscale xy
set xlabel "k"
set ylabel "# AVG Distance Function"
plot '-' title 'Incremental Nearest - Hjaltson' with linespoints 1, '-' title 'Local Nearest - Roussopoulos' with linespoints 2, '-' title 'Global Nearest - Slim-tree' with linespoints 3, '-' title 'Fractal Nearest - Traina' with linespoints 4,'-' title 'Range' with linespoints 5

0.000100	10018.000000
0.000200	10019.000000
0.000500	10022.000000
0.001000	10025.000000
0.002000	10030.000000
0.005000	10042.000000
0.010000	10059.000000
0.020000	10088.000000
0.050000	10163.000000
0.100000	10284.000000
0.200000	10542.000000
0.500000	11404.000000
end

0.000100	10019.000000
0.000200	10020.000000
0.000500	10023.000000
0.001000	10026.000000
0.002000	10030.000000
0.005000	10041.000000
0.010000	10055.000000
0.020000	10080.000000
0.050000	10143.000000
0.100000	10240.000000
0.200000	10447.000000
0.500000	11149.000000
end

0.000100	10019.000000
0.000200	10020.000000
0.000500	10022.000000
0.001000	10025.000000
0.002000	10030.000000
0.005000	10040.000000
0.010000	10054.000000
0.020000	10077.000000
0.050000	10136.000000
0.100000	10230.000000
0.200000	10427.000000
0.500000	11120.000000
end

0.000100	11855.000000
0.000200	10280.000000
0.000500	10055.000000
0.001000	10047.000000
0.002000	10047.000000
0.005000	10050.000000
0.010000	10066.000000
0.020000	10128.000000
0.050000	10141.000000
0.100000	10235.000000
0.200000	10432.000000
0.500000	11125.000000
end

0.000100	10018.000000
0.000200	10019.000000
0.000500	10021.000000
0.001000	10024.000000
0.002000	10028.000000
0.005000	10038.000000
0.010000	10051.000000
0.020000	10072.000000
0.050000	10126.000000
0.100000	10213.000000
0.200000	10400.000000
0.500000	11047.000000
end


pause -1