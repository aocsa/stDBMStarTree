set title "Random dataset:  page=8192,  k=0.0001"
set logscale xy
set xlabel "% Radius"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
0.000100	1234
0.000200	1297
0.000500	1281
0.001000	1281
0.002000	1281
0.005000	1282
0.010000	1281
0.020000	1297
end
# SlimTree-KIntersectionRange
0.000100	2468
0.000200	2640
0.000500	2891
0.001000	3172
0.002000	3640
0.005000	4313
0.010000	5203
0.020000	7204
end
# SlimTree-KORRange
0.000100	1328
0.000200	1453
0.000500	1719
0.001000	1984
0.002000	2344
0.005000	3062
0.010000	4031
0.020000	6016
end
# SlimTree-KUnionRange
0.000100	2547
0.000200	2719
0.000500	3000
0.001000	3297
0.002000	3672
0.005000	4547
0.010000	5922
0.020000	9843
end
# SeqScan-KAndRange
0.000100	6578
0.000200	6578
0.000500	6094
0.001000	6110
0.002000	6109
0.005000	6125
0.010000	6125
0.020000	6125
end
# SeqScan-KIntersectionRange
0.000100	11954
0.000200	11953
0.000500	12031
0.001000	12141
0.002000	12625
0.005000	12312
0.010000	13000
0.020000	14312
end
# SeqScan-KORRange
0.000100	6266
0.000200	6234
0.000500	6297
0.001000	6344
0.002000	6297
0.005000	6500
0.010000	6750
0.020000	7906
end
# SeqScan-KUnionRange
0.000100	12828
0.000200	12813
0.000500	12843
0.001000	12797
0.002000	12656
0.005000	13047
0.010000	13672
0.020000	19079
end

pause -1