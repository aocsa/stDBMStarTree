set title "Random dataset:  page=8192,  k=0.0001"
set logscale xy
set xlabel "% Radius"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
0.000100	718
0.000200	750
0.000500	765
0.001000	765
0.002000	766
0.005000	782
0.010000	766
0.020000	782
end
# SlimTree-KIntersectionRange
0.000100	1437
0.000200	1547
0.000500	1704
0.001000	1860
0.002000	2047
0.005000	2406
0.010000	2829
0.020000	3562
end
# SlimTree-KORRange
0.000100	781
0.000200	859
0.000500	1000
0.001000	1156
0.002000	1359
0.005000	1734
0.010000	2156
0.020000	2907
end
# SlimTree-KUnionRange
0.000100	1437
0.000200	1531
0.000500	1703
0.001000	1875
0.002000	2078
0.005000	2484
0.010000	3047
0.020000	4281
end
# SeqScan-KAndRange
0.000100	3047
0.000200	3063
0.000500	3063
0.001000	3063
0.002000	3046
0.005000	3062
0.010000	3062
0.020000	3078
end
# SeqScan-KIntersectionRange
0.000100	6078
0.000200	6031
0.000500	6046
0.001000	6015
0.002000	6047
0.005000	6125
0.010000	6234
0.020000	6641
end
# SeqScan-KORRange
0.000100	3032
0.000200	3031
0.000500	3016
0.001000	3094
0.002000	3110
0.005000	3172
0.010000	3281
0.020000	3625
end
# SeqScan-KUnionRange
0.000100	6078
0.000200	6032
0.000500	6047
0.001000	6031
0.002000	6047
0.005000	6172
0.010000	6453
0.020000	7344
end

pause -1