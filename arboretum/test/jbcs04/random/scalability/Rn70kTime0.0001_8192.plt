set title "Random dataset:  page=8192,  k=0.0001"
set logscale xy
set xlabel "% Radius"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
0.000100	1657
0.000200	1734
0.000500	1766
0.001000	1781
0.002000	1781
0.005000	1797
0.010000	1797
0.020000	1797
end
# SlimTree-KIntersectionRange
0.000100	3485
0.000200	3735
0.000500	4157
0.001000	4578
0.002000	5140
0.005000	6407
0.010000	8422
0.020000	13141
end
# SlimTree-KORRange
0.000100	1812
0.000200	2000
0.000500	2375
0.001000	2797
0.002000	3375
0.005000	4609
0.010000	6547
0.020000	11828
end
# SlimTree-KUnionRange
0.000100	3563
0.000200	3813
0.000500	4234
0.001000	4688
0.002000	5344
0.005000	7032
0.010000	10234
0.020000	20500
end
# SeqScan-KAndRange
0.000100	10656
0.000200	10672
0.000500	10672
0.001000	10672
0.002000	10672
0.005000	10687
0.010000	10688
0.020000	10718
end
# SeqScan-KIntersectionRange
0.000100	20890
0.000200	20890
0.000500	20953
0.001000	21047
0.002000	21125
0.005000	21468
0.010000	23219
0.020000	27265
end
# SeqScan-KORRange
0.000100	10953
0.000200	10938
0.000500	11125
0.001000	11203
0.002000	11297
0.005000	11641
0.010000	12250
0.020000	15937
end
# SeqScan-KUnionRange
0.000100	21812
0.000200	21797
0.000500	21984
0.001000	22047
0.002000	22218
0.005000	23062
0.010000	25360
0.020000	33531
end

pause -1