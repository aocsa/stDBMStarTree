set title "Cities - Disjuntive Complex Queries D= 1.810000  page=2048"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	170
0.002000	220
0.005000	331
0.010000	470
0.020000	771
0.050000	1733
0.100000	3965
end
####################
0.001000	150
0.002000	180
0.005000	250
0.010000	361
0.020000	510
0.050000	1051
0.100000	2274
end
####################

pause -1