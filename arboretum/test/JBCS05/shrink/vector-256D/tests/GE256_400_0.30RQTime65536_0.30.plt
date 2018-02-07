set title "RQ: Synt256D"
set xlabel "% radius"
set ylabel "Total Time (s)"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'MTree-Minmax' with linespoints lt 6 lw 2 pt 5, '-' title 'SlimTree-MinMax-SlimDown' with linespoints lt 8 lw 2 pt 11, '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4, '-' title 'DBMTree-4' with linespoints lt 5 lw 2 pt 5, '-' title 'DBMTree-5' with linespoints lt 6 lw 2 pt 6, '-' title 'DBMTree-6' with linespoints lt 7 lw 2 pt 7, '-' title 'DBMTree-7' with linespoints lt 8 lw 2 pt 8

####################
# MTree-Minmax
0.0001	16.906
0.000215443	7.375
0.000464159	7.281
0.001	7.359
0.00215443	7.813
0.00464159	8.703
0.01	10.672
0.0215443	14.25
0.0464159	18.594
0.1	23.062
end
# SlimTree-MinMax-SlimDown
0.0001	13.579
0.000215443	6.765
0.000464159	6.766
0.001	6.906
0.00215443	7.234
0.00464159	8.047
0.01	9.813
0.0215443	13.328
0.0464159	17.359
0.1	20.719
end
# DBMTree-0
0.0001	13.984
0.000215443	4.579
0.000464159	4.593
0.001	4.797
0.00215443	5.25
0.00464159	6.235
0.01	8.312
0.0215443	12.047
0.0464159	15.141
0.1	16.703
end
# DBMTree-1
0.0001	14.765
0.000215443	4.25
0.000464159	4.266
0.001	4.468
0.00215443	4.86
0.00464159	5.75
0.01	7.64
0.0215443	11.11
0.0464159	14.015
0.1	15.594
end
# DBMTree-2
0.0001	19.265
0.000215443	8.547
0.000464159	8.703
0.001	8.875
0.00215443	9.391
0.00464159	10.375
0.01	12.547
0.0215443	15.578
0.0464159	18.14
0.1	19.016
end
# DBMTree-3
0.0001	21.86
0.000215443	12.546
0.000464159	12.579
0.001	12.843
0.00215443	13.594
0.00464159	15.109
0.01	17.594
0.0215443	21.328
0.0464159	25.547
0.1	28.75
end
# DBMTree-4
0.0001	9.703
0.000215443	4.016
0.000464159	4.062
0.001	4.188
0.00215443	4.578
0.00464159	5.484
0.01	7.422
0.0215443	10.719
0.0464159	13.359
0.1	14.672
end
# DBMTree-5
0.0001	9.766
0.000215443	3.797
0.000464159	3.859
0.001	4.016
0.00215443	4.375
0.00464159	5.203
0.01	7.015
0.0215443	10.297
0.0464159	12.953
0.1	14.203
end
# DBMTree-6
0.0001	15.234
0.000215443	6.5
0.000464159	6.563
0.001	6.828
0.00215443	7.281
0.00464159	8.172
0.01	10.219
0.0215443	13.343
0.0464159	16.11
0.1	17.25
end
# DBMTree-7
0.0001	19.656
0.000215443	8.906
0.000464159	8.984
0.001	9.266
0.00215443	9.781
0.00464159	10.907
0.01	12.921
0.0215443	16.454
0.0464159	20.015
0.1	22.766
end


pause -1