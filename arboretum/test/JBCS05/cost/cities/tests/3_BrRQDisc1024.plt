set title "Cities: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-2CL: Measured' with error lt 4 lw 2 pt 4, '-' title 'DBM-2CL: Estimated' with linespoints lt 10 lw 2 pt 10

####################
# DBMTree: Real3
0.0001	12.244	9.47769	15.0103
0.000215443	12.284	9.49916	15.0688
0.000464159	12.368	9.57935	15.1567
0.001	12.526	9.69098	15.361
0.00215443	12.856	9.95165	15.7604
0.00464159	13.702	10.6157	16.7883
0.01	15.508	11.92	19.096
0.0215443	21.254	15.5013	27.0067
0.0464159	36.76	24.8583	48.6617
0.1	78.272	51.6282	104.916
end
# DBMTree: Ciaccia-Node Estimation3
0.0001	16.8521
0.000215443	16.8564
0.000464159	16.98
0.001	17.0602
0.00215443	17.5528
0.00464159	18.6087
0.01	21.0281
0.0215443	27.1651
0.0464159	43.6307
0.1	84.9644
end


pause -1