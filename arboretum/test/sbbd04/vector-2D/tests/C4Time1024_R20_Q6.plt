set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	78
0.002000	94
0.005000	125
0.010000	172
0.020000	265
0.050000	625
end
####################
0.001000	62
0.002000	78
0.005000	94
0.010000	109
0.020000	172
0.050000	344
end
####################

pause -1