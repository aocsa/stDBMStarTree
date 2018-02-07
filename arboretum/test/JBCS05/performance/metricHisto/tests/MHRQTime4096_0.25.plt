set title "RQ: medHisto"
set xlabel "% radius"
set ylabel "Total Time (s)"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'MTree-Minmax' with linespoints lt 6 lw 2 pt 5, '-' title 'SlimTree-MinMax-SlimDown' with linespoints lt 8 lw 2 pt 11, '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4

####################
# MTree-Minmax
0.0001	0.875
0.000215443	0.891
0.000464159	0.89
0.001	0.907
0.00215443	0.968
0.00464159	1.063
0.01	1.312
0.0215443	1.875
0.0464159	3.297
0.1	8.203
end
# SlimTree-MinMax-SlimDown
0.0001	0.781
0.000215443	0.797
0.000464159	0.797
0.001	0.828
0.00215443	0.875
0.00464159	1
0.01	1.234
0.0215443	1.797
0.0464159	3.25
0.1	8.078
end
# DBMTree-0
0.0001	0.578
0.000215443	0.578
0.000464159	0.594
0.001	0.625
0.00215443	0.672
0.00464159	0.781
0.01	1.032
0.0215443	1.593
0.0464159	3.094
0.1	7.875
end
# DBMTree-1
0.0001	0.562
0.000215443	0.563
0.000464159	0.594
0.001	0.593
0.00215443	0.657
0.00464159	0.781
0.01	1.015
0.0215443	1.563
0.0464159	3.031
0.1	7.735
end
# DBMTree-2
0.0001	0.75
0.000215443	0.75
0.000464159	0.766
0.001	0.781
0.00215443	0.828
0.00464159	0.938
0.01	1.172
0.0215443	1.687
0.0464159	3.078
0.1	7.813
end
# DBMTree-3
0.0001	0.782
0.000215443	0.796
0.000464159	0.813
0.001	0.828
0.00215443	0.875
0.00464159	0.969
0.01	1.219
0.0215443	1.734
0.0464159	3.109
0.1	7.813
end


pause -1