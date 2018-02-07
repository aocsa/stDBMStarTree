set title "Random dataset:  page=8192,  k=0.0002"
set logscale xy
set xlabel "% Radius"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
0.000100	422.000000
0.000200	516.000000
0.000500	531.000000
0.001000	547.000000
0.002000	547.000000
0.005000	531.000000
0.010000	547.000000
0.020000	547.000000
end
# SlimTree-KIntersectionRange
0.000100	828.000000
0.000200	1016.000000
0.000500	1110.000000
0.001000	1203.000000
0.002000	1297.000000
0.005000	1469.000000
0.010000	1672.000000
0.020000	1984.000000
end
# SlimTree-KORRange
0.000100	453.000000
0.000200	547.000000
0.000500	625.000000
0.001000	719.000000
0.002000	813.000000
0.005000	1015.000000
0.010000	1219.000000
0.020000	1547.000000
end
# SlimTree-KUnionRange
0.000100	844.000000
0.000200	1015.000000
0.000500	1109.000000
0.001000	1203.000000
0.002000	1297.000000
0.005000	1500.000000
0.010000	1750.000000
0.020000	2203.000000
end
# SeqScan-KAndRange
0.000100	1562.000000
0.000200	1531.000000
0.000500	1563.000000
0.001000	1531.000000
0.002000	1547.000000
0.005000	1578.000000
0.010000	1562.000000
0.020000	1563.000000
end
# SeqScan-KIntersectionRange
0.000100	3125.000000
0.000200	3140.000000
0.000500	3125.000000
0.001000	3109.000000
0.002000	3156.000000
0.005000	3203.000000
0.010000	3219.000000
0.020000	3453.000000
end
# SeqScan-KORRange
0.000100	1547.000000
0.000200	1563.000000
0.000500	1562.000000
0.001000	1562.000000
0.002000	1594.000000
0.005000	1625.000000
0.010000	1687.000000
0.020000	1844.000000
end
# SeqScan-KUnionRange
0.000100	3094.000000
0.000200	3141.000000
0.000500	3125.000000
0.001000	3125.000000
0.002000	3156.000000
0.005000	3204.000000
0.010000	3281.000000
0.020000	3797.000000
end

pause -1