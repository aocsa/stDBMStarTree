set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	31.316000
0.002000	33.832000
0.005000	42.108000
0.010000	45.300000
0.020000	52.342000
0.050000	67.696000
end
####################
0.001000	35.178000
0.002000	35.568000
0.005000	46.860000
0.010000	48.652000
0.020000	54.720000
0.050000	68.590000
end
####################

pause -1