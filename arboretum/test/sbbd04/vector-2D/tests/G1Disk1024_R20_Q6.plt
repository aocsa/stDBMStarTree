set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	63.638000
0.002000	67.246000
0.005000	74.072000
0.010000	81.744000
0.020000	92.412000
0.050000	113.206000
end
####################
0.001000	71.314000
0.002000	74.552000
0.005000	80.082000
0.010000	86.794000
0.020000	96.346000
0.050000	115.884000
end
####################

pause -1