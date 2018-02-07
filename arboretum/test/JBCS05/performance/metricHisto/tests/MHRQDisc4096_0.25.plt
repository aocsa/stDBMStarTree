set title "RQ: medHisto"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'MTree-Minmax' with linespoints lt 6 lw 2 pt 5, '-' title 'SlimTree-MinMax-SlimDown' with linespoints lt 8 lw 2 pt 11, '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4

####################
# MTree-Minmax
0.0001	74.284
0.000215443	74.454
0.000464159	74.87
0.001	75.624
0.00215443	77.358
0.00464159	81.556
0.01	90.748
0.0215443	112.606
0.0464159	166.826
0.1	298.238
end
# SlimTree-MinMax-SlimDown
0.0001	68.524
0.000215443	68.664
0.000464159	69.006
0.001	69.684
0.00215443	71.202
0.00464159	74.778
0.01	82.604
0.0215443	101.356
0.0464159	148.966
0.1	264.898
end
# DBMTree-0
0.0001	57.946
0.000215443	58.086
0.000464159	58.39
0.001	59.126
0.00215443	60.606
0.00464159	64.114
0.01	72.282
0.0215443	92.232
0.0464159	143.72
0.1	271.82
end
# DBMTree-1
0.0001	51.85
0.000215443	51.998
0.000464159	52.31
0.001	52.92
0.00215443	54.294
0.00464159	57.456
0.01	64.42
0.0215443	82.438
0.0464159	130.55
0.1	255.358
end
# DBMTree-2
0.0001	64.474
0.000215443	64.608
0.000464159	64.898
0.001	65.556
0.00215443	67.2
0.00464159	70.346
0.01	78.31
0.0215443	97.628
0.0464159	146.492
0.1	281.424
end
# DBMTree-3
0.0001	68.922
0.000215443	69.068
0.000464159	69.366
0.001	69.942
0.00215443	71.136
0.00464159	73.956
0.01	80.764
0.0215443	97.626
0.0464159	141.996
0.1	265.772
end


pause -1