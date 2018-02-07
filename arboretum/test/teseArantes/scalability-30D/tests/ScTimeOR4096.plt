set title "Scalability of the Synt30D dataset: k=15, rq=0.02"
set xlabel "Number of objects in the dataset (x1000)"
set ylabel "Total Time (ms)"
plot '-' title '(A) Slim-Tree: KOrRange' with linespoints lt 1 lw 2 pt 1,'-' title '(B) Seq-Scan: KORRange' with linespoints lt 3 lw 2 pt 2,'-' title '(C) Slim-Tree: Nearest OR Range' with linespoints lt 6 lw 2 pt 3,'-' title '(D) Seq-Scan: Nearest OR Range' with linespoints lt 8 lw 2 pt 4

####################
# SlimTree KAndRange
50	0.062
100	0.094
150	0.110
200	0.141
250	0.171
300	0.156
350	0.203
400	0.265
450	0.235
500	0.234
550	0.234
600	0.250
650	0.281
700	0.281
750	0.281
800	0.297
850	0.297
900	0.312
950	0.344
1000	0.344
end
# SeqScan KAndRange
50	0.438
100	1.140
150	1.719
200	2.328
250	2.922
300	3.469
350	4.110
400	4.735
450	5.187
500	5.672
550	6.156
600	6.719
650	7.281
700	7.922
750	8.172
800	8.718
850	9.328
900	9.828
950	10.687
1000	11.453
end
# SlimTree Intersection
50	0.078
100	0.141
150	0.171
200	0.219
250	0.266
300	0.281
350	0.312
400	0.375
450	0.360
500	0.391
550	0.391
600	0.406
650	0.469
700	0.485
750	0.500
800	0.500
850	0.532
900	0.547
950	0.610
1000	0.657
end
# SlimTree
50	0.734
100	2.015
150	3.032
200	4.062
250	5.125
300	6.063
350	7.188
400	8.250
450	9.062
500	9.953
550	10.812
600	11.797
650	12.766
700	13.859
750	14.359
800	15.391
850	16.390
900	17.860
950	18.703
1000	19.640
end

pause -1