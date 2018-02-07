set title "Random dataset:  page=8192,  k=0.0001"
set logscale xy
set xlabel "% Radius"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
0.000100	375
0.000200	390
0.000500	406
0.001000	422
0.002000	407
0.005000	390
0.010000	390
0.020000	391
end
# SlimTree-KIntersectionRange
0.000100	797
0.000200	797
0.000500	906
0.001000	953
0.002000	1032
0.005000	1157
0.010000	1265
0.020000	1422
end
# SlimTree-KORRange
0.000100	390
0.000200	391
0.000500	484
0.001000	515
0.002000	594
0.005000	703
0.010000	797
0.020000	938
end
# SlimTree-KUnionRange
0.000100	797
0.000200	797
0.000500	906
0.001000	953
0.002000	1031
0.005000	1172
0.010000	1297
0.020000	1500
end
# SeqScan-KAndRange
0.000100	797
0.000200	782
0.000500	797
0.001000	796
0.002000	797
0.005000	813
0.010000	750
0.020000	750
end
# SeqScan-KIntersectionRange
0.000100	1500
0.000200	1500
0.000500	1500
0.001000	1484
0.002000	1515
0.005000	1531
0.010000	1516
0.020000	1672
end
# SeqScan-KORRange
0.000100	813
0.000200	734
0.000500	813
0.001000	813
0.002000	812
0.005000	813
0.010000	765
0.020000	859
end
# SeqScan-KUnionRange
0.000100	1500
0.000200	1500
0.000500	1500
0.001000	1547
0.002000	1469
0.005000	1547
0.010000	1515
0.020000	1735
end

pause -1