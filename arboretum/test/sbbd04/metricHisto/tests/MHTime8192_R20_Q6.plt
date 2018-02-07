set title "Brazilian Cities - Disjuntive Complex Queries D= 2.500000  page=8192"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.000100	1469
0.000200	1469
0.000500	2453
0.001000	2984
0.002000	3500
0.005000	4344
0.010000	5078
0.020000	6031
0.050000	7875
0.100000	10078
end
####################
0.000100	11219
0.000200	11234
0.000500	2922
0.001000	3094
0.002000	3734
0.005000	4828
0.010000	5734
0.020000	7031
0.050000	9687
0.100000	12187
end
####################

pause -1