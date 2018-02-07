set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	156
0.002000	188
0.005000	266
0.010000	375
0.020000	688
0.050000	1922
end
####################
0.001000	140
0.002000	156
0.005000	203
0.010000	250
0.020000	375
0.050000	906
end
####################

pause -1