set title "Random dataset:  page=8192,  k=0.0001"
set logscale xy
set xlabel "% Radius"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
0.000100	2078
0.000200	2172
0.000500	2203
0.001000	2219
0.002000	2234
0.005000	2235
0.010000	2234
0.020000	2235
end
# SlimTree-KIntersectionRange
0.000100	4156
0.000200	4438
0.000500	4906
0.001000	5406
0.002000	6078
0.005000	7703
0.010000	10421
0.020000	18062
end
# SlimTree-KORRange
0.000100	2250
0.000200	2453
0.000500	2922
0.001000	3453
0.002000	4187
0.005000	5859
0.010000	8672
0.020000	16766
end
# SlimTree-KUnionRange
0.000100	4109
0.000200	4406
0.000500	4891
0.001000	5422
0.002000	6234
0.005000	8500
0.010000	13453
0.020000	30234
end
# SeqScan-KAndRange
0.000100	13750
0.000200	13797
0.000500	13797
0.001000	13781
0.002000	13797
0.005000	13812
0.010000	13844
0.020000	13859
end
# SeqScan-KIntersectionRange
0.000100	27625
0.000200	27906
0.000500	27860
0.001000	27234
0.002000	27157
0.005000	28547
0.010000	29735
0.020000	35563
end
# SeqScan-KORRange
0.000100	13578
0.000200	13609
0.000500	13688
0.001000	13750
0.002000	13907
0.005000	14391
0.010000	15890
0.020000	21797
end
# SeqScan-KUnionRange
0.000100	26844
0.000200	26859
0.000500	27016
0.001000	27109
0.002000	27360
0.005000	28640
0.010000	32329
0.020000	48062
end

pause -1