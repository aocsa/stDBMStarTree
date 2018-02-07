set title "RQ: Synt16D"
set xlabel "% radius"
set ylabel "Avg Number of Distance Calculation"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'MTree-Minmax' with linespoints lt 6 lw 2 pt 5, '-' title 'SlimTree-MinMax-SlimDown' with linespoints lt 8 lw 2 pt 11, '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4

####################
# MTree-Minmax
0.0001	139.446
0.000215443	140.958
0.000464159	144.282
0.001	150.864
0.00215443	165.358
0.00464159	197.248
0.01	264.532
0.0215443	410.654
0.0464159	708.326
0.1	1115.17
end
# SlimTree-MinMax-SlimDown
0.0001	123.028
0.000215443	124.484
0.000464159	127.766
0.001	134.328
0.00215443	148.476
0.00464159	179.618
0.01	246.198
0.0215443	390.084
0.0464159	683.836
0.1	1099.57
end
# DBMTree-0
0.0001	46.184
0.000215443	47.69
0.000464159	50.854
0.001	57.576
0.00215443	72.334
0.00464159	104.366
0.01	173.628
0.0215443	318.564
0.0464159	609.208
0.1	962.506
end
# DBMTree-1
0.0001	66.842
0.000215443	68.26
0.000464159	71.24
0.001	77.942
0.00215443	92.21
0.00464159	122.762
0.01	188.57
0.0215443	331.402
0.0464159	624.444
0.1	1004.61
end
# DBMTree-2
0.0001	89.728
0.000215443	91.094
0.000464159	93.958
0.001	100.304
0.00215443	113.594
0.00464159	141.948
0.01	203.714
0.0215443	337.276
0.0464159	620.292
0.1	1018.87
end
# DBMTree-3
0.0001	59.716
0.000215443	60.962
0.000464159	64.052
0.001	70.398
0.00215443	84.004
0.00464159	113.116
0.01	176.066
0.0215443	311.182
0.0464159	586.96
0.1	973.446
end


pause -1