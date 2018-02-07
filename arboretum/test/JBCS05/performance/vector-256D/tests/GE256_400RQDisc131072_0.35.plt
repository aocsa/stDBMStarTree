set title "RQ: Synt256D"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'MTree-Minmax' with linespoints lt 6 lw 2 pt 5, '-' title 'SlimTree-MinMax-SlimDown' with linespoints lt 8 lw 2 pt 11, '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4

####################
# MTree-Minmax
0.0001	40.418
0.000215443	40.554
0.000464159	40.856
0.001	41.51
0.00215443	43.022
0.00464159	46.176
0.01	52.966
0.0215443	65.612
0.0464159	89.996
0.1	124.434
end
# SlimTree-MinMax-SlimDown
0.0001	32.416
0.000215443	32.502
0.000464159	32.74
0.001	33.284
0.00215443	34.424
0.00464159	36.99
0.01	42.8
0.0215443	54.636
0.0464159	73.422
0.1	93.446
end
# DBMTree-0
0.0001	22.73
0.000215443	22.838
0.000464159	22.982
0.001	23.394
0.00215443	24.236
0.00464159	26.136
0.01	29.992
0.0215443	36.354
0.0464159	42.304
0.1	51.508
end
# DBMTree-1
0.0001	18.042
0.000215443	18.114
0.000464159	18.284
0.001	18.654
0.00215443	19.472
0.00464159	21.174
0.01	24.846
0.0215443	30.614
0.0464159	34.852
0.1	38.486
end
# DBMTree-2
0.0001	26.836
0.000215443	26.934
0.000464159	27.158
0.001	27.542
0.00215443	28.448
0.00464159	30.524
0.01	34.716
0.0215443	42.104
0.0464159	49.596
0.1	55.7
end
# DBMTree-3
0.0001	35.192
0.000215443	35.274
0.000464159	35.444
0.001	35.866
0.00215443	36.844
0.00464159	38.856
0.01	43.06
0.0215443	50.984
0.0464159	62.594
0.1	73.794
end


pause -1