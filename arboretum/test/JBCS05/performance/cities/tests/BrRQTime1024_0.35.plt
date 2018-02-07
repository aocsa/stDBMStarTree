set title "RQ: Cities"
set xlabel "% radius"
set ylabel "Total Time (s)"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'MTree-Minmax' with linespoints lt 6 lw 2 pt 5, '-' title 'SlimTree-MinMax-SlimDown' with linespoints lt 8 lw 2 pt 11, '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4

####################
# MTree-Minmax
0.0001	0.047
0.000215443	0.031
0.000464159	0.031
0.001	0.031
0.00215443	0.047
0.00464159	0.047
0.01	0.062
0.0215443	0.11
0.0464159	0.281
0.1	1.25
end
# SlimTree-MinMax-SlimDown
0.0001	0.031
0.000215443	0.031
0.000464159	0.032
0.001	0.047
0.00215443	0.031
0.00464159	0.047
0.01	0.062
0.0215443	0.11
0.0464159	0.281
0.1	1.234
end
# DBMTree-0
0.0001	0.031
0.000215443	0.016
0.000464159	0.031
0.001	0.031
0.00215443	0.032
0.00464159	0.047
0.01	0.046
0.0215443	0.094
0.0464159	0.297
0.1	1.266
end
# DBMTree-1
0.0001	0.032
0.000215443	0.015
0.000464159	0.032
0.001	0.015
0.00215443	0.031
0.00464159	0.032
0.01	0.062
0.0215443	0.094
0.0464159	0.281
0.1	1.297
end
# DBMTree-2
0.0001	0.032
0.000215443	0.015
0.000464159	0.031
0.001	0.016
0.00215443	0.031
0.00464159	0.032
0.01	0.062
0.0215443	0.078
0.0464159	0.281
0.1	1.297
end
# DBMTree-3
0.0001	0.031
0.000215443	0.032
0.000464159	0.031
0.001	0.031
0.00215443	0.031
0.00464159	0.047
0.01	0.063
0.0215443	0.094
0.0464159	0.281
0.1	1.281
end


pause -1