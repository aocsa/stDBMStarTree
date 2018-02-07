set title "Random dataset:  page=8192,  k=0.0001"
set logscale xy
set xlabel "% Radius"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
0.000100	1907
0.000200	2000
0.000500	2032
0.001000	2047
0.002000	2046
0.005000	2063
0.010000	2078
0.020000	2078
end
# SlimTree-KIntersectionRange
0.000100	3844
0.000200	4094
0.000500	4531
0.001000	5015
0.002000	5656
0.005000	7063
0.010000	9453
0.020000	15625
end
# SlimTree-KORRange
0.000100	2094
0.000200	2281
0.000500	2719
0.001000	3203
0.002000	3859
0.005000	5344
0.010000	7813
0.020000	14235
end
# SlimTree-KUnionRange
0.000100	3922
0.000200	4188
0.000500	4656
0.001000	5125
0.002000	5860
0.005000	7828
0.010000	11891
0.020000	25078
end
# SeqScan-KAndRange
0.000100	12109
0.000200	12109
0.000500	12125
0.001000	12125
0.002000	12125
0.005000	12141
0.010000	12156
0.020000	12172
end
# SeqScan-KIntersectionRange
0.000100	23843
0.000200	23891
0.000500	24016
0.001000	24141
0.002000	24375
0.005000	24703
0.010000	26891
0.020000	30437
end
# SeqScan-KORRange
0.000100	12531
0.000200	12547
0.000500	12719
0.001000	12797
0.002000	12953
0.005000	13187
0.010000	14312
0.020000	18875
end
# SeqScan-KUnionRange
0.000100	24937
0.000200	25000
0.000500	25172
0.001000	25312
0.002000	25562
0.005000	26297
0.010000	28562
0.020000	41875
end

pause -1