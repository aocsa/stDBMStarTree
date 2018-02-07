set title "RQ: Synt256D"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'MTree-Minmax' with linespoints lt 6 lw 2 pt 5, '-' title 'SlimTree-MinMax-SlimDown' with linespoints lt 8 lw 2 pt 11, '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4, '-' title 'DBMTree-4' with linespoints lt 5 lw 2 pt 5, '-' title 'DBMTree-5' with linespoints lt 6 lw 2 pt 6, '-' title 'DBMTree-6' with linespoints lt 7 lw 2 pt 7, '-' title 'DBMTree-7' with linespoints lt 8 lw 2 pt 8

####################
# MTree-Minmax
0.0001	250.178
0.000215443	250.656
0.000464159	251.628
0.001	253.864
0.00215443	258.998
0.00464159	270.438
0.01	296.048
0.0215443	345.714
0.0464159	424.202
0.1	538.092
end
# SlimTree-MinMax-SlimDown
0.0001	234.316
0.000215443	234.722
0.000464159	235.474
0.001	237.294
0.00215443	241.53
0.00464159	250.842
0.01	272.446
0.0215443	315.874
0.0464159	381.9
0.1	467.152
end
# DBMTree-0
0.0001	136.074
0.000215443	136.564
0.000464159	137.496
0.001	139.704
0.00215443	144.298
0.00464159	155.29
0.01	180.782
0.0215443	232.506
0.0464159	284.688
0.1	326.692
end
# DBMTree-1
0.0001	142.4
0.000215443	142.864
0.000464159	143.82
0.001	146.056
0.00215443	151.08
0.00464159	162.378
0.01	188.676
0.0215443	240.388
0.0464159	292.326
0.1	331.618
end
# DBMTree-2
0.0001	238.142
0.000215443	238.526
0.000464159	239.378
0.001	241.276
0.00215443	245.296
0.00464159	254.39
0.01	273.61
0.0215443	307.424
0.0464159	341.762
0.1	367.228
end
# DBMTree-3
0.0001	354.228
0.000215443	354.668
0.000464159	355.584
0.001	357.7
0.00215443	362.406
0.00464159	372.05
0.01	394.408
0.0215443	442.624
0.0464159	516.71
0.1	571.58
end
# DBMTree-4
0.0001	113.176
0.000215443	113.57
0.000464159	114.354
0.001	116.188
0.00215443	119.828
0.00464159	128.572
0.01	147.58
0.0215443	183.592
0.0464159	219.42
0.1	249.786
end
# DBMTree-5
0.0001	121.216
0.000215443	121.596
0.000464159	122.376
0.001	124.23
0.00215443	128.492
0.00464159	137.59
0.01	157.67
0.0215443	193.996
0.0464159	229.478
0.1	260.074
end
# DBMTree-6
0.0001	199.22
0.000215443	199.544
0.000464159	200.248
0.001	201.812
0.00215443	205.308
0.00464159	213.036
0.01	229.322
0.0215443	257.892
0.0464159	285.874
0.1	307.392
end
# DBMTree-7
0.0001	270.766
0.000215443	271.1
0.000464159	271.864
0.001	273.584
0.00215443	277.392
0.00464159	285.576
0.01	303.83
0.0215443	339.936
0.0464159	393.682
0.1	437.936
end


pause -1