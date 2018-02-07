set title "RQ: Synt16D"
set xlabel "% radius"
set ylabel "Avg Number of Distance Calculation"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'MTree-Minmax' with linespoints lt 6 lw 2 pt 5,  '-' title 'SlimTree-MinMax-SlimDown' with linespoints lt 8 lw 2 pt 11, '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4, '-' title 'DBMTree-4' with linespoints lt 5 lw 2 pt 5, '-' title 'DBMTree-5' with linespoints lt 6 lw 2 pt 6, '-' title 'DBMTree-6' with linespoints lt 7 lw 2 pt 7, '-' title 'DBMTree-7' with linespoints lt 8 lw 2 pt 8

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
0.0001	58.036
0.000215443	59.502
0.000464159	62.672
0.001	69.238
0.00215443	83.678
0.00464159	114.798
0.01	182.06
0.0215443	323.54
0.0464159	610.79
0.1	970.964
end
# DBMTree-1
0.0001	71.832
0.000215443	73.18
0.000464159	76.148
0.001	82.7
0.00215443	96.782
0.00464159	126.588
0.01	191.192
0.0215443	331.034
0.0464159	617.454
0.1	985.718
end
# DBMTree-2
0.0001	102.468
0.000215443	103.768
0.000464159	106.628
0.001	112.746
0.00215443	125.712
0.00464159	153.478
0.01	212.528
0.0215443	340.71
0.0464159	614.758
0.1	1019.01
end
# DBMTree-3
0.0001	87.95
0.000215443	89.116
0.000464159	91.768
0.001	97.366
0.00215443	109.692
0.00464159	136.422
0.01	193.358
0.0215443	317.12
0.0464159	579.028
0.1	979.978
end
# DBMTree-4
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
# DBMTree-5
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
# DBMTree-6
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
# DBMTree-7
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