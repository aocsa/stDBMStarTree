set title "Random dataset:  page=8KB,  k=0.0001, R=0.0005"
set logscale y
set xlabel "Dataset size (x1000)"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
5	406
10	484
20	765
30	1000
40	1281
50	1515
60	1672
70	1766
80	2032
90	2203
100	2438
end
# SlimTree-KIntersectionRange
5	906
10	1015
20	1704
30	2297
40	2891
50	3485
60	3860
70	4157
80	4531
90	4906
100	5391
end
# SlimTree-KORRange
5	484
10	625
20	1000
30	1297
40	1719
50	2032
60	2203
70	2375
80	2719
90	2922
100	3329
end
# SlimTree-KUnionRange
5	906
10	1016
20	1703
30	2313
40	3000
50	3469
60	3843
70	4234
80	4656
90	4891
100	5390
end
# SeqScan-KAndRange
5	797
10	1531
20	3063
30	4562
40	6094
50	7610
60	9375
70	10672
80	12125
90	13797
100	15593
end
# SeqScan-KIntersectionRange
5	1500
10	3016
20	6046
30	8953
40	12031
50	15109
60	18875
70	20953
80	24016
90	27860
100	31734
end
# SeqScan-KORRange
5	813
10	1515
20	3016
30	4515
40	6297
50	7593
60	9203
70	11125
80	12719
90	13688
100	35687
end
# SeqScan-KUnionRange
5	1500
10	3031
20	6047
30	8968
40	12843
50	15172
60	18907
70	21984
80	25172
90	27016
100	30907
end

pause -1