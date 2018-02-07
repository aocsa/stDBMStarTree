set title "Synt256D: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-MM: Measured' with error lt 1 lw 2 pt 1, '-' title 'DBM-MM: Estimated' with linespoints lt 5 lw 2 pt 5

####################
# DBMTree: Real0
0.0001	21.998	17.2245	26.7715
0.000215443	22.056	17.276	26.836
0.000464159	22.238	17.3951	27.0809
0.001	22.626	17.769	27.483
0.00215443	23.436	18.4454	28.4266
0.00464159	25.358	20.3045	30.4115
0.01	29.252	24.5547	33.9493
0.0215443	35.656	32.4973	38.8147
0.0464159	40.966	38.4195	43.5125
0.1	46.656	44.7456	48.5664
end
# DBMTree: Ciaccia-Node Estimation0
0.0001	18.3963
0.000215443	18.4695
0.000464159	18.5654
0.001	18.9732
0.00215443	19.3725
0.00464159	20.6473
0.01	23.8282
0.0215443	30.8094
0.0464159	39.5172
0.1	46.2929
end

pause -1