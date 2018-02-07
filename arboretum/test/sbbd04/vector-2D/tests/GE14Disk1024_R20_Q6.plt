set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	103.902000
0.002000	106.456000
0.005000	117.288000
0.010000	139.830000
0.020000	168.088000
0.050000	230.796000
end
####################
0.001000	119.784000
0.002000	120.106000
0.005000	120.966000
0.010000	147.682000
0.020000	172.464000
0.050000	211.832000
end
####################

pause -1