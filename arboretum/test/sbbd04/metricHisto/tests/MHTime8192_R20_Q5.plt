set title "Brazilian Cities - Disjuntive Complex Queries D= 2.500000  page=8192"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.000100	1469
0.000200	1469
0.000500	2453
0.001000	2969
0.002000	3515
0.005000	4359
0.010000	5094
0.020000	6031
0.050000	7781
0.100000	10109
end
####################
0.000100	11266
0.000200	11250
0.000500	3032
0.001000	3172
0.002000	3813
0.005000	4906
0.010000	5843
0.020000	7156
0.050000	9781
0.100000	12282
end
####################

pause -1