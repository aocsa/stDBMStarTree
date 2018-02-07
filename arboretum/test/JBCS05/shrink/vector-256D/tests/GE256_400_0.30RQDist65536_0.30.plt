set title "RQ: Synt256D"
set xlabel "% radius"
set ylabel "Avg Number of Distance Calculation"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'MTree-Minmax' with linespoints lt 6 lw 2 pt 5, '-' title 'SlimTree-MinMax-SlimDown' with linespoints lt 8 lw 2 pt 11, '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4, '-' title 'DBMTree-4' with linespoints lt 5 lw 2 pt 5, '-' title 'DBMTree-5' with linespoints lt 6 lw 2 pt 6, '-' title 'DBMTree-6' with linespoints lt 7 lw 2 pt 7, '-' title 'DBMTree-7' with linespoints lt 8 lw 2 pt 8

####################
# MTree-Minmax
0.0001	426.772
0.000215443	431.31
0.000464159	440.966
0.001	461.904
0.00215443	506.85
0.00464159	603.55
0.01	808.118
0.0215443	1189.26
0.0464159	1578.9
0.1	1843.43
end
# SlimTree-MinMax-SlimDown
0.0001	382.626
0.000215443	387.046
0.000464159	396.39
0.001	416.976
0.00215443	460.964
0.00464159	555.66
0.01	756.546
0.0215443	1146.36
0.0464159	1562.33
0.1	1835.4
end
# DBMTree-0
0.0001	145.222
0.000215443	150.21
0.000464159	160.84
0.001	182.704
0.00215443	230.846
0.00464159	334.008
0.01	546.884
0.0215443	924.24
0.0464159	1229.48
0.1	1334.84
end
# DBMTree-1
0.0001	166.6
0.000215443	171.172
0.000464159	180.846
0.001	201.614
0.00215443	247.778
0.00464159	345.514
0.01	548.91
0.0215443	917.684
0.0464159	1228.41
0.1	1344.43
end
# DBMTree-2
0.0001	406.932
0.000215443	411.426
0.000464159	420.962
0.001	441.226
0.00215443	485.526
0.00464159	579.252
0.01	774.462
0.0215443	1123.99
0.0464159	1409.22
0.1	1476.6
end
# DBMTree-3
0.0001	523.294
0.000215443	528.196
0.000464159	538.594
0.001	561.138
0.00215443	609.516
0.00464159	713.916
0.01	930.028
0.0215443	1311.2
0.0464159	1683.09
0.1	1886.96
end
# DBMTree-4
0.0001	143.348
0.000215443	148.506
0.000464159	159.448
0.001	182.21
0.00215443	232.064
0.00464159	338.79
0.01	559.022
0.0215443	947.912
0.0464159	1271.74
0.1	1393.58
end
# DBMTree-5
0.0001	142.126
0.000215443	146.842
0.000464159	156.828
0.001	178.48
0.00215443	226.088
0.00464159	326.26
0.01	536.716
0.0215443	918.63
0.0464159	1239.79
0.1	1346.81
end
# DBMTree-6
0.0001	338.474
0.000215443	343.312
0.000464159	353.938
0.001	376.55
0.00215443	425.132
0.00464159	528.9
0.01	744.63
0.0215443	1130.39
0.0464159	1462.4
0.1	1571.99
end
# DBMTree-7
0.0001	415.518
0.000215443	421.014
0.000464159	432.584
0.001	457.286
0.00215443	510.674
0.00464159	623.952
0.01	858.484
0.0215443	1265.43
0.0464159	1653.22
0.1	1889.69
end


pause -1