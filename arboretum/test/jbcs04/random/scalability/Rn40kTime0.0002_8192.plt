set title "Random dataset:  page=8192,  k=0.0002"
set logscale xy
set xlabel "% Radius"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
0.000100	1296.000000
0.000200	1454.000000
0.000500	1531.000000
0.001000	1531.000000
0.002000	1531.000000
0.005000	1500.000000
0.010000	1500.000000
0.020000	1500.000000
end
# SlimTree-KIntersectionRange
0.000100	2453.000000
0.000200	2891.000000
0.000500	3172.000000
0.001000	3453.000000
0.002000	3781.000000
0.005000	4484.000000
0.010000	5375.000000
0.020000	7359.000000
end
# SlimTree-KORRange
0.000100	1297.000000
0.000200	1484.000000
0.000500	1688.000000
0.001000	1969.000000
0.002000	2312.000000
0.005000	3015.000000
0.010000	3953.000000
0.020000	5985.000000
end
# SlimTree-KUnionRange
0.000100	2469.000000
0.000200	2797.000000
0.000500	3078.000000
0.001000	3360.000000
0.002000	3750.000000
0.005000	4610.000000
0.010000	6032.000000
0.020000	9938.000000
end
# SeqScan-KAndRange
0.000100	6625.000000
0.000200	6328.000000
0.000500	6844.000000
0.001000	6297.000000
0.002000	6688.000000
0.005000	6750.000000
0.010000	6312.000000
0.020000	6406.000000
end
# SeqScan-KIntersectionRange
0.000100	14516.000000
0.000200	18609.000000
0.000500	19500.000000
0.001000	17953.000000
0.002000	18110.000000
0.005000	15219.000000
0.010000	14828.000000
0.020000	16391.000000
end
# SeqScan-KORRange
0.000100	6094.000000
0.000200	6125.000000
0.000500	6140.000000
0.001000	6172.000000
0.002000	6235.000000
0.005000	6360.000000
0.010000	6687.000000
0.020000	7828.000000
end
# SeqScan-KUnionRange
0.000100	11937.000000
0.000200	12000.000000
0.000500	12062.000000
0.001000	12156.000000
0.002000	12265.000000
0.005000	12515.000000
0.010000	13390.000000
0.020000	18875.000000
end

pause -1