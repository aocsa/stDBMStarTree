set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	156
0.002000	187
0.005000	266
0.010000	390
0.020000	671
0.050000	1844
end
####################
0.001000	141
0.002000	157
0.005000	187
0.010000	250
0.020000	360
0.050000	891
end
####################

pause -1