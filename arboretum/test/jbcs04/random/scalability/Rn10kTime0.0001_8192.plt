set title "Random dataset:  page=8192,  k=0.0001"
set logscale xy
set xlabel "% Radius"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
0.000100	422
0.000200	469
0.000500	484
0.001000	469
0.002000	469
0.005000	454
0.010000	453
0.020000	453
end
# SlimTree-KIntersectionRange
0.000100	828
0.000200	922
0.000500	1015
0.001000	1094
0.002000	1188
0.005000	1391
0.010000	1562
0.020000	1875
end
# SlimTree-KORRange
0.000100	453
0.000200	531
0.000500	625
0.001000	704
0.002000	812
0.005000	1000
0.010000	1219
0.020000	1531
end
# SlimTree-KUnionRange
0.000100	828
0.000200	906
0.000500	1016
0.001000	1094
0.002000	1203
0.005000	1406
0.010000	1641
0.020000	2109
end
# SeqScan-KAndRange
0.000100	1516
0.000200	1531
0.000500	1531
0.001000	1531
0.002000	1531
0.005000	1531
0.010000	1547
0.020000	1547
end
# SeqScan-KIntersectionRange
0.000100	3000
0.000200	3047
0.000500	3016
0.001000	3000
0.002000	3015
0.005000	3047
0.010000	3079
0.020000	3390
end
# SeqScan-KORRange
0.000100	1516
0.000200	1516
0.000500	1515
0.001000	1531
0.002000	1532
0.005000	1546
0.010000	1563
0.020000	1703
end
# SeqScan-KUnionRange
0.000100	3000
0.000200	3047
0.000500	3031
0.001000	3016
0.002000	3031
0.005000	3078
0.010000	3141
0.020000	3547
end

pause -1