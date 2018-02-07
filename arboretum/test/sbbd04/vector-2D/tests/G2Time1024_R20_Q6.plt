set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	2047
0.002000	2688
0.005000	5390
0.010000	13016
0.020000	43343
0.050000	245468
end
####################
0.001000	1766
0.002000	2000
0.005000	2750
0.010000	4719
0.020000	12672
0.050000	76875
end
####################

pause -1