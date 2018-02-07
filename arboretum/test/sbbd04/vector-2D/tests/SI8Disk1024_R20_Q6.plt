set title "Vector2D - Disjuntive Complex Queries D= 1.830000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	30.904000
0.002000	32.492000
0.005000	36.318000
0.010000	41.232000
0.020000	48.782000
0.050000	66.882000
end
####################
0.001000	34.744000
0.002000	35.938000
0.005000	38.758000
0.010000	42.354000
0.020000	48.610000
0.050000	63.510000
end
####################

pause -1