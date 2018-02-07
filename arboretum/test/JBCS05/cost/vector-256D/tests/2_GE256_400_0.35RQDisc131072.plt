set title "Synt256D: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-GMM: Measured' with error lt 3 lw 2 pt 3, '-' title 'DBM-GMM: Estimated' with linespoints lt 9 lw 2 pt 9

####################
# DBMTree: Real2
0.0001	26.836	21.6528	32.0192
0.000215443	26.938	21.7605	32.1155
0.000464159	27.164	21.9959	32.3321
0.001	27.548	22.3158	32.7802
0.00215443	28.466	23.1578	33.7742
0.00464159	30.566	25.0464	36.0856
0.01	34.774	29.3756	40.1724
0.0215443	42.212	37.523	46.901
0.0464159	49.662	44.9397	54.3843
0.1	55.732	52.1959	59.2681
end
# DBMTree: Ciaccia-Node Estimation2
0.0001	23.1887
0.000215443	23.2425
0.000464159	23.3437
0.001	23.5981
0.00215443	24.5578
0.00464159	26.2425
0.01	29.7658
0.0215443	37.6241
0.0464159	48.192
0.1	55.5282
end

pause -1