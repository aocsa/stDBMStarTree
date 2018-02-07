set title "Random dataset:  page=8192,  k=0.0001"
set logscale xy
set xlabel "% Radius"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
0.000100	922
0.000200	984
0.000500	1000
0.001000	1000
0.002000	1015
0.005000	1015
0.010000	1016
0.020000	1015
end
# SlimTree-KIntersectionRange
0.000100	1953
0.000200	2094
0.000500	2297
0.001000	2515
0.002000	2781
0.005000	3313
0.010000	3953
0.020000	5219
end
# SlimTree-KORRange
0.000100	1031
0.000200	1109
0.000500	1297
0.001000	1500
0.002000	1765
0.005000	2281
0.010000	2937
0.020000	4235
end
# SlimTree-KUnionRange
0.000100	1953
0.000200	2094
0.000500	2313
0.001000	2532
0.002000	2828
0.005000	3453
0.010000	4391
0.020000	6781
end
# SeqScan-KAndRange
0.000100	4547
0.000200	4563
0.000500	4562
0.001000	4579
0.002000	4563
0.005000	4578
0.010000	4594
0.020000	4594
end
# SeqScan-KIntersectionRange
0.000100	8938
0.000200	8953
0.000500	8953
0.001000	9094
0.002000	9078
0.005000	9250
0.010000	9406
0.020000	10141
end
# SeqScan-KORRange
0.000100	4500
0.000200	4516
0.000500	4515
0.001000	4610
0.002000	4657
0.005000	4766
0.010000	4984
0.020000	5656
end
# SeqScan-KUnionRange
0.000100	8953
0.000200	8953
0.000500	8968
0.001000	9062
0.002000	9141
0.005000	9406
0.010000	9891
0.020000	11672
end

pause -1