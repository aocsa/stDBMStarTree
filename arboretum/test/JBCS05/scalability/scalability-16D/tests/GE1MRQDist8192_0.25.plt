set title "RQ: Vector-16D"
set xlabel "dataset size"
set ylabel "Avg Number of Distance Calculation"
set xrange [1:20]
plot '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4

####################
# DBMTree-0
1	203.39
2	273.06
3	345.26
4	416.98
5	534.22
6	579.71
7	653.32
8	675.03
9	778.17
10	770.77
11	868.78
12	973.32
13	996.1
14	1006.24
15	1147.41
16	1151.05
17	1210.67
18	1318.22
19	1361.48
20	1448
end
# DBMTree-1
1	180.6
2	234.68
3	274.66
4	353.24
5	407.03
6	478.68
7	467.97
8	610.41
9	680.06
10	674.21
11	714.58
12	683.13
13	751.93
14	760.69
15	821.11
16	853.08
17	861.56
18	912.2
19	869.34
20	984.44
end
# DBMTree-2
1	522.93
2	720.15
3	950.82
4	1189.89
5	1561.04
6	1779.14
7	1980.09
8	2235.1
9	2388.98
10	2567.68
11	2823.51
12	3031.23
13	3291.92
14	3500.24
15	3763.69
16	3877.34
17	4222.15
18	4618.12
19	4753.41
20	4965.75
end
# DBMTree-3
1	403.61
2	613.66
3	762.47
4	1094.18
5	1240.88
6	1372.84
7	1485.77
8	1619.94
9	1789.77
10	1828.9
11	2065.86
12	2497.36
13	2756.79
14	3145.96
15	3354.92
16	3517.92
17	3746.58
18	3956.96
19	4061.66
20	4154.35
end


pause -1