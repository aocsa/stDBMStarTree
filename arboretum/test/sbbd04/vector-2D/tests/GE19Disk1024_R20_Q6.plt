set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	65.131800
0.002000	67.979100
0.005000	73.348550
0.010000	78.759250
0.020000	91.300950
0.050000	152.365100
end
####################
0.001000	73.307050
0.002000	75.501500
0.005000	79.766850
0.010000	84.148750
0.020000	89.456700
0.050000	122.386650
end
####################

pause -1