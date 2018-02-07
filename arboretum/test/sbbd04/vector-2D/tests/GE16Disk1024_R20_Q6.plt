set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	127.426000
0.002000	134.860000
0.005000	152.560000
0.010000	173.832000
0.020000	204.792000
0.050000	269.814000
end
####################
0.001000	142.204000
0.002000	145.918000
0.005000	158.706000
0.010000	174.382000
0.020000	199.922000
0.050000	256.112000
end
####################

pause -1