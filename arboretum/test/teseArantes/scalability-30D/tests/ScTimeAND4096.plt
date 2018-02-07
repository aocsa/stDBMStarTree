set title "Scalability of the Synt30D dataset: k=15, rq=0.02"
set xlabel "Number of objects in the dataset (x1000)"
set ylabel "Total Time (s)"
plot '-' title '(A) Slim-Tree: KAndRange' with linespoints lt 1 lw 2 pt 1,'-' title '(B) Seq-Scan: KAndRange' with linespoints lt 3 lw 2 pt 2,'-' title '(C) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3,'-' title '(D) Seq-Scan: Nearest AND Range' with linespoints lt 8 lw 2 pt 4

####################
# SlimTree KAndRange
50	0.032
100	0.047
150	0.063
200	0.094
250	0.110
300	0.110
350	0.140
400	0.156
450	0.172
500	0.203
550	0.187
600	0.187
650	0.219
700	0.250
750	0.265
800	0.234
850	0.266
900	0.265
950	0.297
1000	0.297
end
# SeqScan KAndRange
50	0.437
100	1.140
150	1.718
200	2.313
250	2.937
300	3.531
350	4.078
400	4.688
450	5.265
500	5.828
550	6.235
600	6.781
650	7.343
700	7.906
750	8.360
800	8.813
850	9.437
900	9.969
950	11.094
1000	11.328
end
# SlimTree Intersection
50	0.078
100	0.141
150	0.188
200	0.218
250	0.282
300	0.265
350	0.328
400	0.359
450	0.359
500	0.375
550	0.390
600	0.422
650	0.469
700	0.500
750	0.515
800	0.515
850	0.531
900	0.547
950	0.594
1000	0.609
end
# SeqScan Intersection
50	0.735
100	2.000
150	3.015
200	4.047
250	5.125
300	6.094
350	7.094
400	8.391
450	9.422
500	9.938
550	10.829
600	11.781
650	12.766
700	13.922
750	14.391
800	15.532
850	16.375
900	17.344
950	18.859
1000	19.781
end

pause -1