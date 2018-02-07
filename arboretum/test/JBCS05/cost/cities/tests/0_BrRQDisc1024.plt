set title "Cities: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-MM: Measured' with error lt 1 lw 2 pt 1, '-' title 'DBM-MM: Estimated' with linespoints lt 5 lw 2 pt 5

####################
# DBMTree: Real0
0.0001	13.354	8.62149	18.0865
0.000215443	13.41	8.64955	18.1705
0.000464159	13.512	8.73017	18.2938
0.001	13.7	8.85707	18.5429
0.00215443	14.144	9.15849	19.1295
0.00464159	15.246	9.90732	20.5847
0.01	17.496	11.3211	23.6709
0.0215443	23.532	15.0203	32.0437
0.0464159	40.422	25.3147	55.5293
0.1	84.438	54.6111	114.265
end
# DBMTree: Ciaccia-Node Estimation0
0.0001	17.962
0.000215443	18.0113
0.000464159	18.0807
0.001	18.2595
0.00215443	18.7818
0.00464159	20.1464
0.01	22.7728
0.0215443	29.3692
0.0464159	46.8726
0.1	89.9961
end

pause -1