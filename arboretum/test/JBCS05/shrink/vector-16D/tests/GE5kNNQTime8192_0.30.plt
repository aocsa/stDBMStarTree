set title "kNNQ: Synt16D"
set xlabel "k"
set ylabel "Total Time (s)"
set xrange [2:20]
plot '-' title 'MTree-Minmax' with linespoints lt 6 lw 2 pt 5,  '-' title 'SlimTree-MinMax-SlimDown' with linespoints lt 8 lw 2 pt 11, '-' title 'DBMTree-0' with linespoints lt 1 lw 2 pt 1, '-' title 'DBMTree-1' with linespoints lt 2 lw 2 pt 2, '-' title 'DBMTree-2' with linespoints lt 3 lw 2 pt 3, '-' title 'DBMTree-3' with linespoints lt 4 lw 2 pt 4, '-' title 'DBMTree-4' with linespoints lt 5 lw 2 pt 5, '-' title 'DBMTree-5' with linespoints lt 6 lw 2 pt 6, '-' title 'DBMTree-6' with linespoints lt 7 lw 2 pt 7, '-' title 'DBMTree-7' with linespoints lt 8 lw 2 pt 8

####################
# MTree-Minmax
2	0.734
3	0.735
4	0.75
5	0.765
6	0.75
7	0.766
8	0.766
9	0.781
10	0.781
11	0.781
12	0.782
13	0.781
14	0.797
15	0.797
16	0.797
17	0.812
18	0.797
19	0.812
20	0.813
end
# SlimTree-MinMax-SlimDown
2	1.468
3	1.453
4	1.516
5	1.516
6	1.5
7	1.484
8	1.547
9	1.531
10	1.578
11	1.5
12	1.578
13	1.563
14	1.578
15	1.578
16	1.578
17	1.61
18	1.593
19	1.625
20	1.61
end
# DBMTree-0
2	1.391
3	1.453
4	1.484
5	1.454
6	1.453
7	1.515
8	1.5
9	1.516
10	1.578
11	1.516
12	1.547
13	1.578
14	1.5
15	1.609
16	1.594
17	1.562
18	1.578
19	1.579
20	1.593
end
# DBMTree-1
2	1.39
3	1.407
4	1.468
5	1.454
6	1.484
7	1.453
8	1.422
9	1.5
10	1.516
11	1.468
12	1.469
13	1.516
14	1.515
15	1.516
16	1.562
17	1.563
18	1.578
19	1.578
20	1.563
end
# DBMTree-2
2	1.578
3	1.578
4	1.61
5	1.562
6	1.578
7	1.61
8	1.578
9	1.625
10	1.578
11	1.672
12	1.625
13	1.672
14	1.625
15	1.64
16	1.641
17	1.688
18	1.671
19	1.704
20	1.687
end
# DBMTree-3
2	1.578
3	1.688
4	1.672
5	1.687
6	1.688
7	1.719
8	1.703
9	1.734
10	1.766
11	1.75
12	1.75
13	1.812
14	1.75
15	1.766
16	1.781
17	1.781
18	1.782
19	1.812
20	1.813
end
# DBMTree-4
2	1.203
3	1.266
4	1.265
5	1.282
6	1.297
7	1.312
8	1.313
9	1.343
10	1.313
11	1.328
12	1.375
13	1.312
14	1.344
15	1.391
16	1.344
17	1.39
18	1.375
19	1.375
20	1.328
end
# DBMTree-5
2	1.297
3	1.313
4	1.312
5	1.375
6	1.313
7	1.375
8	1.39
9	1.391
10	1.422
11	1.422
12	1.437
13	1.422
14	1.406
15	1.438
16	1.469
17	1.437
18	1.5
19	1.453
20	1.406
end
# DBMTree-6
2	1.328
3	1.328
4	1.375
5	1.391
6	1.39
7	1.375
8	1.407
9	1.406
10	1.437
11	1.407
12	1.437
13	1.406
14	1.438
15	1.422
16	1.437
17	1.438
18	1.437
19	1.485
20	1.437
end
# DBMTree-7
2	1.219
3	1.265
4	1.313
5	1.312
6	1.281
7	1.36
8	1.344
9	1.281
10	1.39
11	1.36
12	1.375
13	1.359
14	1.344
15	1.437
16	1.391
17	1.375
18	1.469
19	1.39
20	1.422
end


pause -1