set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	643.902000
0.002000	685.238000
0.005000	765.802000
0.010000	856.364000
0.020000	987.126000
0.050000	1249.886000
end
####################
0.001000	705.312000
0.002000	733.730000
0.005000	791.946000
0.010000	859.030000
0.020000	957.820000
0.050000	1165.652000
end
####################

pause -1