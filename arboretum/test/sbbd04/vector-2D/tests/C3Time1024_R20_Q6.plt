set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	46
0.002000	79
0.005000	94
0.010000	156
0.020000	250
0.050000	610
end
####################
0.001000	63
0.002000	46
0.005000	78
0.010000	94
0.020000	141
0.050000	328
end
####################

pause -1