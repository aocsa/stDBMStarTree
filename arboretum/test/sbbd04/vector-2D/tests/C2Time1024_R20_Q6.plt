set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	110
0.002000	125
0.005000	203
0.010000	265
0.020000	469
0.050000	1219
end
####################
0.001000	93
0.002000	94
0.005000	156
0.010000	203
0.020000	250
0.050000	593
end
####################

pause -1