set title "Synt16D: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-MM: Measured' with error lt 1 lw 2 pt 1, '-' title 'DBM-MM: Estimated' with linespoints lt 5 lw 2 pt 5

####################
# DBMTree: Real0
0.0001	13.858	8.39743	19.3186
0.000215443	13.886	8.41197	19.36
0.000464159	13.948	8.46336	19.4326
0.001	14.068	8.56242	19.5736
0.00215443	14.382	8.83618	19.9278
0.00464159	14.972	9.28665	20.6574
0.01	16.41	10.4362	22.3838
0.0215443	19.49	13.2995	25.6805
0.0464159	25.956	20.7393	31.1727
0.1	32.22	29.5857	34.8543
end
# DBMTree: Ciaccia-Node Estimation0
0.0001	11.0839
0.000215443	11.1152
0.000464159	11.1521
0.001	11.2447
0.00215443	11.399
0.00464159	11.9327
0.01	13.0134
0.0215443	15.4397
0.0464159	21.355
0.1	31.0644
end

pause -1