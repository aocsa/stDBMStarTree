set title "Vector2D - Disjuntive Complex Queries D= 5.200000  page=2048"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	1026.506000
0.002000	1102.930000
0.005000	1236.842000
0.010000	1376.210000
0.020000	1530.830000
0.050000	1726.964000
end
####################
0.001000	1143.250000
0.002000	1222.364000
0.005000	1360.028000
0.010000	1515.712000
0.020000	1700.724000
0.050000	1946.062000
end
####################

pause -1