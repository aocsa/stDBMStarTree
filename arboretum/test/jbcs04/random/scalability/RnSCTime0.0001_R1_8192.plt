set title "Random dataset:  page=8KB,  k=0.0001, R=0.0001"
set logscale y
set xlabel "Dataset size (x1000)"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
5	375
10	422
20	718
30	922
40	1234
50	1438
60	1578
70	1657
80	1907
90	2078
100	2266
end
# SlimTree-KIntersectionRange
5	797
10	828
20	1437
30	1953
40	2468
50	2984
60	3250
70	3485
80	3844
90	4156
100	4563
end
# SlimTree-KORRange
5	390
10	453
20	781
30	1031
40	1328
50	1547
60	1672
70	1812
80	2094
90	2250
100	2578
end
# SlimTree-KUnionRange
5	797
10	828
20	1437
30	1953
40	2547
50	2937
60	3234
70	3563
80	3922
90	4109
100	4531
end
# SeqScan-KAndRange
5	797
10	1516
20	3047
30	4547
40	6578
50	7594
60	9375
70	10656
80	12109
90	13750
100	15578
end
# SeqScan-KIntersectionRange
5	1500
10	3000
20	6078
30	8938
40	11954
50	14969
60	18750
70	20890
80	23843
90	27625
100	31156
end
# SeqScan-KORRange
5	813
10	1516
20	3032
30	4500
40	6266
50	7500
60	9015
70	10953
80	12531
90	13578
100	37922
end
# SeqScan-KUnionRange
5	1500
10	3000
20	6078
30	8953
40	12828
50	15047
60	18781
70	21812
80	24937
90	26844
100	30610
end

pause -1