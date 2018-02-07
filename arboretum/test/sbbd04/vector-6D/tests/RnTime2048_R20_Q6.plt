set title "Vector2D - Disjuntive Complex Queries D= 6.000000  page=2048"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	3157
0.002000	3657
0.005000	5000
0.010000	7672
0.020000	16203
0.050000	71953
end
####################
0.001000	2812
0.002000	3187
0.005000	3750
0.010000	4687
0.020000	7406
0.050000	26500
end
####################

pause -1