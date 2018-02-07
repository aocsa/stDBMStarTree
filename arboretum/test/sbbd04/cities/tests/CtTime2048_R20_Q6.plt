set title "Cities - Disjuntive Complex Queries D= 1.810000  page=2048"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	170
0.002000	220
0.005000	340
0.010000	481
0.020000	771
0.050000	1732
0.100000	3946
end
####################
0.001000	150
0.002000	181
0.005000	241
0.010000	340
0.020000	501
0.050000	1002
0.100000	2193
end
####################

pause -1