set title "colorHisto: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-MM: Measured' with error lt 1 lw 2 pt 1, '-' title 'DBM-MM: Estimated' with linespoints lt 5 lw 2 pt 5

####################
# DBMTree: Real0
0.0001	308.072	140.992	475.152
0.000215443	308.49	141.172	475.808
0.000464159	309.364	141.482	477.246
0.001	311.214	142.311	480.117
0.00215443	315.538	143.894	487.182
0.00464159	325.3	147.529	503.071
0.01	346.7	155.939	537.461
0.0215443	397.848	176.189	619.507
0.0464159	531.918	231.366	832.47
0.1	935.628	422.441	1448.81
end
# DBMTree: Ciaccia-Node Estimation0
0.0001	293.846
0.000215443	294.192
0.000464159	294.961
0.001	296.654
0.00215443	299.829
0.00464159	308.328
0.01	327.22
0.0215443	370.718
0.0464159	486.712
0.1	849.35
end

pause -1