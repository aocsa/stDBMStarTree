set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	182.478000
0.002000	193.064000
0.005000	214.126000
0.010000	237.678000
0.020000	271.470000
0.050000	339.044000
end
####################
0.001000	203.518000
0.002000	212.112000
0.005000	229.494000
0.010000	249.956000
0.020000	280.058000
0.050000	344.698000
end
####################

pause -1