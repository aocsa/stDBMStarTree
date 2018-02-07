set title "kNNQ: Cities"
set xlabel "dataset size"
set ylabel "Total Time (s)"
set xrange [1:20]
plot '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4

####################
# DBMTree-0
1	4480
2	7730
3	10510
4	13240
5	15770
6	18630
7	21250
8	23780
9	25800
10	27000
11	31810
12	33120
13	34960
14	39200
15	41650
16	43170
17	45030
18	48300
19	50860
20	52580
end
# DBMTree-1
1	4170
2	7030
3	9760
4	12410
5	15160
6	17060
7	19790
8	22110
9	24380
10	26910
11	29140
12	32030
13	33470
14	34660
15	37130
16	39010
17	41100
18	45150
19	45340
20	47540
end
# DBMTree-2
1	4450
2	7460
3	10150
4	12820
5	15430
6	17890
7	19910
8	22630
9	24300
10	26850
11	30290
12	33530
13	36170
14	38560
15	38560
16	43490
17	46230
18	48880
19	51040
20	53440
end
# DBMTree-3
1	4880
2	8050
3	11210
4	13580
5	15900
6	18390
7	20350
8	22200
9	23800
10	25890
11	29950
12	33460
13	36670
14	40160
15	42630
16	45720
17	48980
18	50910
19	53130
20	55530
end


pause -1