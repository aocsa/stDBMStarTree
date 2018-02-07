set title "Synt16D: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-MS: Measured' with error lt 2 lw 2 pt 2, '-' title 'DBM-MS: Estimated' with linespoints lt 6 lw 2 pt 6

####################
# DBMTree: Real1
0.0001	12.28	6.64284	17.9172
0.000215443	12.324	6.67289	17.9751
0.000464159	12.412	6.71724	18.1068
0.001	12.576	6.86214	18.2899
0.00215443	12.928	7.13535	18.7207
0.00464159	13.598	7.65726	19.5387
0.01	15.196	8.94671	21.4453
0.0215443	18.78	12.2703	25.2897
0.0464159	25.534	19.8327	31.2353
0.1	32.796	29.9792	35.6128
end
# DBMTree: Ciaccia-Node Estimation1
0.0001	10.4338
0.000215443	10.4594
0.000464159	10.471
0.001	10.5547
0.00215443	10.7772
0.00464159	11.259
0.01	12.3454
0.0215443	14.9684
0.0464159	21.1172
0.1	31.2227
end

pause -1