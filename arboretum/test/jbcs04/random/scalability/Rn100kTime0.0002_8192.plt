set title "Random dataset:  page=8192,  k=0.0002"
set logscale xy
set xlabel "% Radius"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
0.000100	2281.000000
0.000200	2594.000000
0.000500	2766.000000
0.001000	2797.000000
0.002000	2812.000000
0.005000	2813.000000
0.010000	2828.000000
0.020000	2828.000000
end
# SlimTree-KIntersectionRange
0.000100	4531.000000
0.000200	5219.000000
0.000500	5718.000000
0.001000	6281.000000
0.002000	7047.000000
0.005000	8891.000000
0.010000	12016.000000
0.020000	21750.000000
end
# SlimTree-KORRange
0.000100	2469.000000
0.000200	2859.000000
0.000500	3265.000000
0.001000	3828.000000
0.002000	4625.000000
0.005000	6484.000000
0.010000	9766.000000
0.020000	20219.000000
end
# SlimTree-KUnionRange
0.000100	4516.000000
0.000200	5187.000000
0.000500	5735.000000
0.001000	6313.000000
0.002000	7234.000000
0.005000	9890.000000
0.010000	15984.000000
0.020000	37734.000000
end
# SeqScan-KAndRange
0.000100	15672.000000
0.000200	15734.000000
0.000500	15859.000000
0.001000	15938.000000
0.002000	15984.000000
0.005000	15969.000000
0.010000	16047.000000
0.020000	16047.000000
end
# SeqScan-KIntersectionRange
0.000100	30797.000000
0.000200	31000.000000
0.000500	31172.000000
0.001000	31282.000000
0.002000	31421.000000
0.005000	31953.000000
0.010000	33844.000000
0.020000	42484.000000
end
# SeqScan-KORRange
0.000100	15547.000000
0.000200	15797.000000
0.000500	15860.000000
0.001000	15875.000000
0.002000	16016.000000
0.005000	16531.000000
0.010000	18687.000000
0.020000	26906.000000
end
# SeqScan-KUnionRange
0.000100	30719.000000
0.000200	31000.000000
0.000500	31093.000000
0.001000	31344.000000
0.002000	31469.000000
0.005000	32938.000000
0.010000	38266.000000
0.020000	60188.000000
end

pause -1