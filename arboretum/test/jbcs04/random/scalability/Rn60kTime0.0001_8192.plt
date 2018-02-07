set title "Random dataset:  page=8192,  k=0.0001"
set logscale xy
set xlabel "% Radius"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, '-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, '-' title '(C) Slim-Tree: kOrRange' with linespoints 3, '-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, '-' title '(E) SeqScan: kAndRange' with linespoints 5, '-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, '-' title '(G) SeqScan: kOrRange' with linespoints 7, '-' title '(H) SeqScan: Union basic alg.' with linespoints 8

####################
# SlimTree-KAndRange
0.000100	1578
0.000200	1641
0.000500	1672
0.001000	1657
0.002000	1672
0.005000	1672
0.010000	1671
0.020000	1672
end
# SlimTree-KIntersectionRange
0.000100	3250
0.000200	3469
0.000500	3860
0.001000	4250
0.002000	4750
0.005000	5844
0.010000	7406
0.020000	11078
end
# SlimTree-KORRange
0.000100	1672
0.000200	1844
0.000500	2203
0.001000	2594
0.002000	3094
0.005000	4188
0.010000	5812
0.020000	9953
end
# SlimTree-KUnionRange
0.000100	3234
0.000200	3438
0.000500	3843
0.001000	4234
0.002000	4797
0.005000	6172
0.010000	8750
0.020000	16375
end
# SeqScan-KAndRange
0.000100	9375
0.000200	9359
0.000500	9375
0.001000	9390
0.002000	9375
0.005000	9391
0.010000	9407
0.020000	9421
end
# SeqScan-KIntersectionRange
0.000100	18750
0.000200	18781
0.000500	18875
0.001000	19078
0.002000	19078
0.005000	19219
0.010000	19969
0.020000	22156
end
# SeqScan-KORRange
0.000100	9015
0.000200	9016
0.000500	9203
0.001000	9203
0.002000	9265
0.005000	9578
0.010000	10563
0.020000	13188
end
# SeqScan-KUnionRange
0.000100	18781
0.000200	18750
0.000500	18907
0.001000	18922
0.002000	19109
0.005000	19703
0.010000	21453
0.020000	27782
end

pause -1