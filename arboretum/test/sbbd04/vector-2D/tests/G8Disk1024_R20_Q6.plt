set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	66.188000
0.002000	69.868000
0.005000	76.758000
0.010000	84.958000
0.020000	96.486000
0.050000	121.420000
end
####################
0.001000	74.250000
0.002000	77.690000
0.005000	83.012000
0.010000	89.960000
0.020000	100.158000
0.050000	121.154000
end
####################

pause -1