set title "Vector2D - Disjuntive Complex Queries D= 2.600000  page=2048"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	10.784000
0.002000	11.464000
0.005000	12.770000
0.010000	14.378000
0.020000	16.692000
0.050000	21.024000
0.100000	25.892000
end
####################
0.001000	15.242000
0.002000	12.646000
0.005000	14.090000
0.010000	15.624000
0.020000	18.268000
0.050000	22.956000
0.100000	28.266000
end
####################

pause -1