set title "RQ: Vector-16D"
set xlabel "dataset size"
set ylabel "Avg Number of Disk Access"
set xrange [1:20]
plot '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4

####################
# DBMTree-0
1	20.26
2	28.12
3	40.31
4	48.89
5	57.4
6	73.09
7	68.28
8	80.93
9	85.57
10	85.68
11	89.46
12	103.24
13	115.11
14	110
15	129.25
16	134.37
17	134.49
18	144.05
19	145.05
20	160.58
end
# DBMTree-1
1	22.42
2	23.71
3	27.56
4	35.79
5	40.83
6	49.96
7	50.78
8	64.03
9	67.6
10	74.75
11	74.74
12	76.18
13	74.33
14	79.73
15	82.61
16	82.68
17	90.78
18	88.13
19	86.88
20	91.84
end
# DBMTree-2
1	60.88
2	94.52
3	117.53
4	156.14
5	201.96
6	232.92
7	258.02
8	297.2
9	314.96
10	354.93
11	401.21
12	415.1
13	467.96
14	484.42
15	515.8
16	541.27
17	578.48
18	619.57
19	643.87
20	668.96
end
# DBMTree-3
1	57.99
2	88.76
3	127.45
4	161.99
5	177.62
6	199.71
7	219.92
8	225.38
9	239.11
10	250.04
11	321.75
12	350.51
13	378.58
14	415.95
15	449.57
16	485.68
17	512.3
18	534.45
19	546.83
20	567.78
end


pause -1