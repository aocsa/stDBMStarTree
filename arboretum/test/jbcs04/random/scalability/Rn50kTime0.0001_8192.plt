set title "Random dataset:  page=8192,  k=0.0001"
set logscale xy
set xlabel "% Radius"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
0.000100	1438
0.000200	1500
0.000500	1515
0.001000	1515
0.002000	1531
0.005000	1531
0.010000	1547
0.020000	1532
end
# SlimTree-KIntersectionRange
0.000100	2984
0.000200	3172
0.000500	3485
0.001000	3828
0.002000	4265
0.005000	5110
0.010000	6375
0.020000	9172
end
# SlimTree-KORRange
0.000100	1547
0.000200	1703
0.000500	2032
0.001000	2360
0.002000	2812
0.005000	3734
0.010000	5031
0.020000	8094
end
# SlimTree-KUnionRange
0.000100	2937
0.000200	3141
0.000500	3469
0.001000	3812
0.002000	4297
0.005000	5406
0.010000	7421
0.020000	13094
end
# SeqScan-KAndRange
0.000100	7594
0.000200	7625
0.000500	7610
0.001000	7610
0.002000	7609
0.005000	7610
0.010000	7640
0.020000	7656
end
# SeqScan-KIntersectionRange
0.000100	14969
0.000200	14984
0.000500	15109
0.001000	15594
0.002000	15297
0.005000	15437
0.010000	16000
0.020000	18047
end
# SeqScan-KORRange
0.000100	7500
0.000200	7484
0.000500	7593
0.001000	7703
0.002000	7782
0.005000	8000
0.010000	8547
0.020000	10375
end
# SeqScan-KUnionRange
0.000100	15047
0.000200	15062
0.000500	15172
0.001000	15313
0.002000	15406
0.005000	15907
0.010000	17235
0.020000	22421
end

pause -1