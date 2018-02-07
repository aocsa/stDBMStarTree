set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	62
0.002000	78
0.005000	125
0.010000	172
0.020000	250
0.050000	610
end
####################
0.001000	63
0.002000	63
0.005000	94
0.010000	109
0.020000	157
0.050000	328
end
####################

pause -1