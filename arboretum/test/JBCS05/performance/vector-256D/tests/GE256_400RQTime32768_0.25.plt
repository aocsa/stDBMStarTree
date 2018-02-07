set title "RQ: Synt256D"
set xlabel "% radius"
set ylabel "Total Time (s)"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'MTree-Minmax' with linespoints lt 6 lw 2 pt 5, '-' title 'SlimTree-MinMax-SlimDown' with linespoints lt 8 lw 2 pt 11, '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4

####################
# MTree-Minmax
0.0001	43.828
0.000215443	9.969
0.000464159	10
0.001	10.25
0.00215443	10.453
0.00464159	11.078
0.01	12.438
0.0215443	14.609
0.0464159	20.484
0.1	26.641
end
# SlimTree-MinMax-SlimDown
0.0001	41.109
0.000215443	10.782
0.000464159	11.375
0.001	12.047
0.00215443	12.062
0.00464159	11.969
0.01	12.781
0.0215443	14.891
0.0464159	19.406
0.1	24.984
end
# DBMTree-0
0.0001	20.093
0.000215443	5.047
0.000464159	5.032
0.001	5.109
0.00215443	5.344
0.00464159	5.75
0.01	6.75
0.0215443	8.375
0.0464159	11.593
0.1	14.641
end
# DBMTree-1
0.0001	19.906
0.000215443	4.797
0.000464159	4.844
0.001	4.875
0.00215443	5.062
0.00464159	5.469
0.01	6.516
0.0215443	8.281
0.0464159	11.625
0.1	14.687
end
# DBMTree-2
0.0001	19.875
0.000215443	8.422
0.000464159	8.453
0.001	8.485
0.00215443	8.687
0.00464159	9.141
0.01	10
0.0215443	11.859
0.0464159	14.797
0.1	17.266
end
# DBMTree-3
0.0001	21.86
0.000215443	10.469
0.000464159	10.484
0.001	10.562
0.00215443	10.719
0.00464159	11.328
0.01	12.375
0.0215443	14.344
0.0464159	17.141
0.1	20.125
end


pause -1