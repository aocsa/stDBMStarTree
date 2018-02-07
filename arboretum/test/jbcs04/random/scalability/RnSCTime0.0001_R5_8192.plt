set title "Random dataset:  page=8KB,  k=0.0001, R=0.002"
set logscale y
set xlabel "Dataset size (x1000)"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
5	407
10	469
20	766
30	1015
40	1281
50	1531
60	1672
70	1781
80	2046
90	2234
100	2453
end
# SlimTree-KIntersectionRange
5	1032
10	1188
20	2047
30	2781
40	3640
50	4265
60	4750
70	5140
80	5656
90	6078
100	6718
end
# SlimTree-KORRange
5	594
10	812
20	1359
30	1765
40	2344
50	2812
60	3094
70	3375
80	3859
90	4187
100	4750
end
# SlimTree-KUnionRange
5	1031
10	1203
20	2078
30	2828
40	3672
50	4297
60	4797
70	5344
80	5860
90	6234
100	6938
end
# SeqScan-KAndRange
5	797
10	1531
20	3046
30	4563
40	6109
50	7609
60	9375
70	10672
80	12125
90	13797
100	15625
end
# SeqScan-KIntersectionRange
5	1515
10	3015
20	6047
30	9078
40	12625
50	15297
60	19078
70	21125
80	24375
90	27157
100	32000
end
# SeqScan-KORRange
5	812
10	1532
20	3110
30	4657
40	6297
50	7782
60	9265
70	11297
80	12953
90	13907
100	36688
end
# SeqScan-KUnionRange
5	1469
10	3031
20	6047
30	9141
40	12656
50	15406
60	19109
70	22218
80	25562
90	27360
100	44281
end

pause -1