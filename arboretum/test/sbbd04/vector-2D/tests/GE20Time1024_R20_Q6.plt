set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	469
0.002000	562
0.005000	781
0.010000	1219
0.020000	2359
0.050000	8062
end
####################
0.001000	406
0.002000	453
0.005000	563
0.010000	719
0.020000	1141
0.050000	3313
end
####################

pause -1