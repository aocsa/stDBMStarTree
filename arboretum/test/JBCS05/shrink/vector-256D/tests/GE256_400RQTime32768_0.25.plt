set title "RQ: Synt16D"
set xlabel "% radius"
set ylabel "Total Time (s)"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'SlimTree-MinMax-SlimDown' with linespoints lt 8 lw 2 pt 11, '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4, '-' title 'DBMTree-4' with linespoints lt 5 lw 2 pt 5, '-' title 'DBMTree-5' with linespoints lt 6 lw 2 pt 6, '-' title 'DBMTree-6' with linespoints lt 7 lw 2 pt 7, '-' title 'DBMTree-7' with linespoints lt 8 lw 2 pt 8

####################
# SlimTree-MinMax-SlimDown
0.0001	21.875
0.000215443	9.218
0.000464159	9.235
0.001	9.281
0.00215443	9.531
0.00464159	10.016
0.01	10.922
0.0215443	12.89
0.0464159	16.329
0.1	20.234
end
# DBMTree-0
0.0001	26.781
0.000215443	5.516
0.000464159	5.547
0.001	5.672
0.00215443	6
0.00464159	6.671
0.01	7.797
0.0215443	9.313
0.0464159	12.047
0.1	15.031
end
# DBMTree-1
0.0001	30.625
0.000215443	5.422
0.000464159	5.469
0.001	5.594
0.00215443	5.89
0.00464159	6.641
0.01	7.609
0.0215443	9.219
0.0464159	12.125
0.1	15.031
end
# DBMTree-2
0.0001	26.156
0.000215443	9.047
0.000464159	8.969
0.001	9
0.00215443	9.109
0.00464159	9.422
0.01	10.266
0.0215443	11.859
0.0464159	14.235
0.1	16.234
end
# DBMTree-3
0.0001	27.484
0.000215443	12.313
0.000464159	12.297
0.001	12.343
0.00215443	12.657
0.00464159	13.187
0.01	14.313
0.0215443	16.515
0.0464159	18.969
0.1	21.422
end
# DBMTree-4
0.0001	21.329
0.000215443	4.75
0.000464159	4.703
0.001	4.812
0.00215443	5.031
0.00464159	5.454
0.01	6.359
0.0215443	7.75
0.0464159	10.422
0.1	13.109
end
# DBMTree-5
0.0001	18.672
0.000215443	4.484
0.000464159	4.5
0.001	4.547
0.00215443	4.75
0.00464159	5.109
0.01	6.125
0.0215443	7.61
0.0464159	10.437
0.1	13.125
end
# DBMTree-6
0.0001	22.5
0.000215443	7.86
0.000464159	7.875
0.001	7.906
0.00215443	8.109
0.00464159	8.453
0.01	9.172
0.0215443	10.672
0.0464159	13.109
0.1	15.11
end
# DBMTree-7
0.0001	24.359
0.000215443	9.547
0.000464159	9.578
0.001	9.656
0.00215443	9.797
0.00464159	10.328
0.01	11.391
0.0215443	13.187
0.0464159	15.625
0.1	18.235
end


pause -1