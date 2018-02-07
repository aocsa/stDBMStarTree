set title "Random dataset:  page=8KB,  k=0.0001, R=0.001"
set logscale y
set xlabel "Dataset size (x1000)"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
5	422
10	469
20	765
30	1000
40	1281
50	1515
60	1657
70	1781
80	2047
90	2219
100	2454
end
# SlimTree-KIntersectionRange
5	953
10	1094
20	1860
30	2515
40	3172
50	3828
60	4250
70	4578
80	5015
90	5406
100	5953
end
# SlimTree-KORRange
5	515
10	704
20	1156
30	1500
40	1984
50	2360
60	2594
70	2797
80	3203
90	3453
100	3906
end
# SlimTree-KUnionRange
5	953
10	1094
20	1875
30	2532
40	3297
50	3812
60	4234
70	4688
80	5125
90	5422
100	5968
end
# SeqScan-KAndRange
5	796
10	1531
20	3063
30	4579
40	6110
50	7610
60	9390
70	10672
80	12125
90	13781
100	15625
end
# SeqScan-KIntersectionRange
5	1484
10	3000
20	6015
30	9094
40	12141
50	15594
60	19078
70	21047
80	24141
90	27234
100	31688
end
# SeqScan-KORRange
5	813
10	1531
20	3094
30	4610
40	6344
50	7703
60	9203
70	11203
80	12797
90	13750
100	36547
end
# SeqScan-KUnionRange
5	1547
10	3016
20	6031
30	9062
40	12797
50	15313
60	18922
70	22047
80	25312
90	27109
100	31125
end

pause -1