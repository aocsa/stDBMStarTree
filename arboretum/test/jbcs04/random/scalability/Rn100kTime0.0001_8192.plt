set title "Random dataset:  page=8192,  k=0.0001"
set logscale xy
set xlabel "% Radius"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
0.000100	2266
0.000200	2406
0.000500	2438
0.001000	2454
0.002000	2453
0.005000	2453
0.010000	2453
0.020000	2453
end
# SlimTree-KIntersectionRange
0.000100	4563
0.000200	4891
0.000500	5391
0.001000	5953
0.002000	6718
0.005000	8516
0.010000	11641
0.020000	21063
end
# SlimTree-KORRange
0.000100	2578
0.000200	2796
0.000500	3329
0.001000	3906
0.002000	4750
0.005000	6625
0.010000	9922
0.020000	19843
end
# SlimTree-KUnionRange
0.000100	4531
0.000200	4859
0.000500	5390
0.001000	5968
0.002000	6938
0.005000	9547
0.010000	15438
0.020000	37250
end
# SeqScan-KAndRange
0.000100	15578
0.000200	15578
0.000500	15593
0.001000	15625
0.002000	15625
0.005000	15656
0.010000	15672
0.020000	15625
end
# SeqScan-KIntersectionRange
0.000100	31156
0.000200	31609
0.000500	31734
0.001000	31688
0.002000	32000
0.005000	32375
0.010000	34062
0.020000	45125
end
# SeqScan-KORRange
0.000100	37922
0.000200	36500
0.000500	35687
0.001000	36547
0.002000	36688
0.005000	32593
0.010000	30907
0.020000	31516
end
# SeqScan-KUnionRange
0.000100	30610
0.000200	30672
0.000500	30907
0.001000	31125
0.002000	44281
0.005000	42609
0.010000	43250
0.020000	58375
end

pause -1