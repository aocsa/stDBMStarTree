set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	30.540000
0.002000	31.682000
0.005000	36.090000
0.010000	42.238000
0.020000	51.384000
0.050000	65.996000
end
####################
0.001000	34.902000
0.002000	35.400000
0.005000	37.818000
0.010000	42.462000
0.020000	50.750000
0.050000	67.246000
end
####################

pause -1