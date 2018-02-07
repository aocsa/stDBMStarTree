set title "RQ: Synt256D"
set xlabel "% radius"
set ylabel "Avg Number of Distance Calculation"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'MTree-Minmax' with linespoints lt 6 lw 2 pt 5, '-' title 'SlimTree-MinMax-SlimDown' with linespoints lt 8 lw 2 pt 11, '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4

####################
# MTree-Minmax
0.0001	358.106
0.000215443	363.422
0.000464159	374.85
0.001	398.716
0.00215443	450.908
0.00464159	561.87
0.01	794.012
0.0215443	1215.09
0.0464159	1682.39
0.1	2129.21
end
# SlimTree-MinMax-SlimDown
0.0001	330.076
0.000215443	335.434
0.000464159	346.81
0.001	370.848
0.00215443	423.43
0.00464159	535.62
0.01	771.274
0.0215443	1225.07
0.0464159	1782.02
0.1	2292.42
end
# DBMTree-0
0.0001	107.09
0.000215443	112.874
0.000464159	124.868
0.001	151.538
0.00215443	207.89
0.00464159	328.444
0.01	575.244
0.0215443	1007.88
0.0464159	1406.71
0.1	1634.94
end
# DBMTree-1
0.0001	106.736
0.000215443	111.602
0.000464159	121.914
0.001	143.792
0.00215443	191.774
0.00464159	293.724
0.01	503.346
0.0215443	860.204
0.0464159	1105.88
0.1	1148.45
end
# DBMTree-2
0.0001	193.356
0.000215443	198.45
0.000464159	209.362
0.001	231.78
0.00215443	281.276
0.00464159	386.724
0.01	606.632
0.0215443	1003.14
0.0464159	1362.33
0.1	1546.76
end
# DBMTree-3
0.0001	137.54
0.000215443	142.388
0.000464159	153.05
0.001	176.31
0.00215443	225.572
0.00464159	331.936
0.01	551.402
0.0215443	947.476
0.0464159	1325.75
0.1	1482.2
end


pause -1