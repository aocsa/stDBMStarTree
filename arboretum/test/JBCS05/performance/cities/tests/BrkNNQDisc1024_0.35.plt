set title "kNNQ: Cities"
set xlabel "k"
set ylabel "Avg Number of Disk Access"
set xrange [2:20]
plot '-' title 'MTree-Minmax' with linespoints lt 6 lw 2 pt 5, '-' title 'SlimTree-MinMax-SlimDown' with linespoints lt 8 lw 2 pt 11, '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4

####################
# MTree-Minmax
2	18.914
3	19.432
4	19.86
5	20.316
6	20.67
7	21.022
8	21.424
9	21.808
10	22.086
11	22.418
12	22.748
13	23.048
14	23.336
15	23.688
16	23.946
17	24.234
18	24.56
19	24.922
20	25.162
end
# SlimTree-MinMax-SlimDown
2	17.904
3	18.356
4	18.78
5	19.166
6	19.46
7	19.776
8	20.124
9	20.42
10	20.674
11	20.99
12	21.308
13	21.562
14	21.842
15	22.174
16	22.468
17	22.728
18	23.056
19	23.378
20	23.642
end
# DBMTree-0
2	13.466
3	14.172
4	14.642
5	15.076
6	15.456
7	15.836
8	16.248
9	16.578
10	16.908
11	17.294
12	17.628
13	17.924
14	18.188
15	18.47
16	18.776
17	19.052
18	19.298
19	19.63
20	19.912
end
# DBMTree-1
2	11.25
3	11.744
4	12.094
5	12.448
6	12.75
7	13.07
8	13.406
9	13.708
10	13.954
11	14.192
12	14.426
13	14.674
14	14.94
15	15.248
16	15.516
17	15.806
18	16.056
19	16.32
20	16.566
end
# DBMTree-2
2	10.808
3	11.168
4	11.478
5	11.774
6	12.024
7	12.318
8	12.652
9	12.944
10	13.138
11	13.384
12	13.676
13	13.964
14	14.222
15	14.492
16	14.74
17	14.978
18	15.216
19	15.408
20	15.646
end
# DBMTree-3
2	13.936
3	14.35
4	14.668
5	14.952
6	15.268
7	15.604
8	15.904
9	16.172
10	16.472
11	16.738
12	16.974
13	17.25
14	17.522
15	17.8
16	18.028
17	18.292
18	18.504
19	18.738
20	18.96
end


pause -1