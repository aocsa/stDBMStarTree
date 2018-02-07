set title "Vector2D - Disjuntive Complex Queries D= 7.044500  page=4096"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	1773
0.002000	1873
0.005000	2093
0.010000	2413
0.020000	3105
0.050000	6239
0.100000	16654
end
####################
0.001000	1772
0.002000	1853
0.005000	2002
0.010000	2243
0.020000	2704
0.050000	4125
0.100000	9404
end
####################

pause -1