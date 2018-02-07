set title "Brazilian Cities - Disjuntive Complex Queries D= 2.500000  page=8192"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.000100	1469
0.000200	1484
0.000500	2469
0.001000	2985
0.002000	3532
0.005000	4375
0.010000	5109
0.020000	6078
0.050000	7860
0.100000	10188
end
####################
0.000100	10969
0.000200	10875
0.000500	3172
0.001000	3296
0.002000	3937
0.005000	5078
0.010000	6047
0.020000	7375
0.050000	9906
0.100000	12453
end
####################

pause -1