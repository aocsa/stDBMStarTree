set title "kNNQ: Synt256D"
set xlabel "k"
set ylabel "Total Time (s)"
set xrange [2:20]
plot '-' title 'MTree-Minmax' with linespoints lt 6 lw 2 pt 5, '-' title 'SlimTree-MinMax-SlimDown' with linespoints lt 8 lw 2 pt 11, '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4

####################
# MTree-Minmax
2	28120
3	28120
4	28200
5	28230
6	28230
7	28300
8	28310
9	28360
10	28370
11	28430
12	28420
13	28480
14	28490
15	28520
16	28570
17	28580
18	28640
19	28630
20	28690
end
# SlimTree-MinMax-SlimDown
2	25540
3	25610
4	25630
5	25690
6	25700
7	25750
8	25770
9	25810
10	25840
11	25850
12	25900
13	25920
14	25940
15	25980
16	26010
17	26060
18	26060
19	26110
20	26110
end
# DBMTree-0
2	17050
3	17140
4	17200
5	17260
6	17310
7	17360
8	17400
9	17450
10	17490
11	17530
12	17560
13	17600
14	17640
15	17700
16	17750
17	17780
18	17810
19	17860
20	17880
end
# DBMTree-1
2	13860
3	13950
4	14010
5	14060
6	14160
7	14210
8	14280
9	14320
10	14370
11	14460
12	14500
13	14540
14	14590
15	14620
16	14740
17	14800
18	15020
19	15050
20	15150
end
# DBMTree-2
2	16690
3	16740
4	16780
5	16830
6	16850
7	16890
8	16920
9	16970
10	16980
11	17010
12	17050
13	17080
14	17100
15	17140
16	17160
17	17180
18	17210
19	17230
20	17270
end
# DBMTree-3
2	18860
3	18950
4	19100
5	19160
6	19240
7	19390
8	19430
9	19470
10	19520
11	19680
12	19730
13	19880
14	19920
15	19950
16	20000
17	20060
18	20290
19	20500
20	20600
end


pause -1