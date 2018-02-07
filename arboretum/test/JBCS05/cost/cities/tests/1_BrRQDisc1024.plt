set title "Cities: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-MS: Measured' with error lt 2 lw 2 pt 2, '-' title 'DBM-MS: Estimated' with linespoints lt 6 lw 2 pt 6

####################
# DBMTree: Real1
0.0001	10.554	8.07628	13.0317
0.000215443	10.582	8.09619	13.0678
0.000464159	10.668	8.16165	13.1743
0.001	10.826	8.27811	13.3739
0.00215443	11.226	8.55937	13.8926
0.00464159	12.12	9.09517	15.1448
0.01	14.238	10.371	18.105
0.0215443	20.282	13.8884	26.6756
0.0464159	36.58	23.3034	49.8566
0.1	80.14	51.0135	109.266
end
# DBMTree: Ciaccia-Node Estimation1
0.0001	15.4379
0.000215443	15.4573
0.000464159	15.6426
0.001	15.8658
0.00215443	16.3574
0.00464159	17.6036
0.01	19.9563
0.0215443	26.3966
0.0464159	43.9658
0.1	86.3938
end

pause -1