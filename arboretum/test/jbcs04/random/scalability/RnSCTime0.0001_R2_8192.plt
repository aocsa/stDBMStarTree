set title "Random dataset:  page=8KB,  k=0.0001, R=0.0002"
set logscale y
set xlabel "Dataset size (x1000)"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
5	390
10	469
20	750
30	984
40	1297
50	1500
60	1641
70	1734
80	2000
90	2172
100	2406
end
# SlimTree-KIntersectionRange
5	797
10	922
20	1547
30	2094
40	2640
50	3172
60	3469
70	3735
80	4094
90	4438
100	4891
end
# SlimTree-KORRange
5	391
10	531
20	859
30	1109
40	1453
50	1703
60	1844
70	2000
80	2281
90	2453
100	2796
end
# SlimTree-KUnionRange
5	797
10	906
20	1531
30	2094
40	2719
50	3141
60	3438
70	3813
80	4188
90	4406
100	4859
end
# SeqScan-KAndRange
5	782
10	1531
20	3063
30	4563
40	6578
50	7625
60	9359
70	10672
80	12109
90	13797
100	15578
end
# SeqScan-KIntersectionRange
5	1500
10	3047
20	6031
30	8953
40	11953
50	14984
60	18781
70	20890
80	23891
90	27906
100	31609
end
# SeqScan-KORRange
5	734
10	1516
20	3031
30	4516
40	6234
50	7484
60	9016
70	10938
80	12547
90	13609
100	36500
end
# SeqScan-KUnionRange
5	1500
10	3047
20	6032
30	8953
40	12813
50	15062
60	18750
70	21797
80	25000
90	26859
100	30672
end

pause -1