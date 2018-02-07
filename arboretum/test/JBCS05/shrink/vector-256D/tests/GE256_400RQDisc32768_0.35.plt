set title "RQ: Synt16D"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'SlimTree-MinMax-SlimDown' with linespoints lt 8 lw 2 pt 11, '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4, '-' title 'DBMTree-4' with linespoints lt 5 lw 2 pt 5, '-' title 'DBMTree-5' with linespoints lt 6 lw 2 pt 6, '-' title 'DBMTree-6' with linespoints lt 7 lw 2 pt 7, '-' title 'DBMTree-7' with linespoints lt 8 lw 2 pt 8

####################
# SlimTree-MinMax-SlimDown
0.0001	234.144
0.000215443	234.344
0.000464159	234.784
0.001	235.612
0.00215443	237.606
0.00464159	242.19
0.01	252.406
0.0215443	275.964
0.0464159	322.048
0.1	390.96
end
# DBMTree-0
0.0001	157.008
0.000215443	157.214
0.000464159	157.658
0.001	158.728
0.00215443	161.038
0.00464159	166.514
0.01	178.426
0.0215443	205.57
0.0464159	256.748
0.1	313.32
end
# DBMTree-1
0.0001	135.762
0.000215443	136.002
0.000464159	136.498
0.001	137.576
0.00215443	139.822
0.00464159	145.038
0.01	156.598
0.0215443	182.956
0.0464159	229.442
0.1	274.14
end
# DBMTree-2
0.0001	237.99
0.000215443	238.166
0.000464159	238.594
0.001	239.524
0.00215443	241.626
0.00464159	246.01
0.01	255.846
0.0215443	276.592
0.0464159	311.652
0.1	345.034
end
# DBMTree-3
0.0001	354.06
0.000215443	354.272
0.000464159	354.744
0.001	355.744
0.00215443	358.076
0.00464159	363.082
0.01	373.714
0.0215443	398.092
0.0464159	450.008
0.1	523.946
end
# DBMTree-4
0.0001	136.788
0.000215443	136.978
0.000464159	137.418
0.001	138.336
0.00215443	140.476
0.00464159	145.114
0.01	155.376
0.0215443	177.924
0.0464159	216.862
0.1	260.202
end
# DBMTree-5
0.0001	118.418
0.000215443	118.634
0.000464159	119.046
0.001	119.934
0.00215443	121.816
0.00464159	126.046
0.01	135.334
0.0215443	155.324
0.0464159	188.398
0.1	220.978
end
# DBMTree-6
0.0001	199.102
0.000215443	199.244
0.000464159	199.6
0.001	200.362
0.00215443	202.094
0.00464159	205.88
0.01	214.272
0.0215443	231.88
0.0464159	261.508
0.1	288.512
end
# DBMTree-7
0.0001	270.63
0.000215443	270.79
0.000464159	271.15
0.001	272.016
0.00215443	273.892
0.00464159	277.972
0.01	286.958
0.0215443	306.652
0.0464159	345.272
0.1	399.364
end


pause -1