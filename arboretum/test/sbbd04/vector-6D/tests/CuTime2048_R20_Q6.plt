set title "Vector2D - Disjuntive Complex Queries D= 2.600000  page=2048"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	16
0.002000	31
0.005000	47
0.010000	46
0.020000	78
0.050000	156
0.100000	297
end
####################
0.001000	31
0.002000	16
0.005000	31
0.010000	47
0.020000	62
0.050000	94
0.100000	203
end
####################

pause -1