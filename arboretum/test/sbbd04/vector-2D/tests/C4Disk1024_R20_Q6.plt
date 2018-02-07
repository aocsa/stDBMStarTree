set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	35.824000
0.002000	38.046000
0.005000	42.514000
0.010000	47.906000
0.020000	55.732000
0.050000	71.336000
end
####################
0.001000	40.354000
0.002000	42.292000
0.005000	45.942000
0.010000	50.518000
0.020000	57.868000
0.050000	73.786000
end
####################

pause -1