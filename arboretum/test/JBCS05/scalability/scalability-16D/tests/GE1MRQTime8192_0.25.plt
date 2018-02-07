set title "RQ: Vector-16D"
set xlabel "dataset size"
set ylabel "Total Time (s)"
set xrange [1:20]
plot '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4

####################
# DBMTree-0
1	90
2	120
3	180
4	220
5	270
6	310
7	320
8	370
9	400
10	390
11	430
12	480
13	530
14	530
15	610
16	640
17	670
18	710
19	700
20	750
end
# DBMTree-1
1	80
2	90
3	110
4	170
5	210
6	230
7	230
8	310
9	320
10	340
11	360
12	380
13	370
14	400
15	410
16	410
17	480
18	470
19	480
20	500
end
# DBMTree-2
1	260
2	420
3	500
4	660
5	820
6	970
7	1060
8	1210
9	1290
10	1440
11	1640
12	1760
13	1970
14	2060
15	2210
16	2320
17	2500
18	2720
19	2800
20	2930
end
# DBMTree-3
1	230
2	370
3	470
4	650
5	690
6	780
7	860
8	900
9	960
10	1000
11	1230
12	1460
13	1600
14	1800
15	1920
16	2060
17	2180
18	2320
19	2380
20	2450
end


pause -1