set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	141
0.002000	171
0.005000	250
0.010000	360
0.020000	625
0.050000	1812
end
####################
0.001000	140
0.002000	157
0.005000	188
0.010000	234
0.020000	360
0.050000	844
end
####################

pause -1