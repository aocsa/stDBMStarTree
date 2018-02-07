set title "Cities - Disjuntive Complex Queries D= 1.810000  page=2048"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	170
0.002000	220
0.005000	331
0.010000	480
0.020000	771
0.050000	1753
0.100000	4006
end
####################
0.001000	160
0.002000	200
0.005000	260
0.010000	371
0.020000	540
0.050000	1091
0.100000	2423
end
####################

pause -1