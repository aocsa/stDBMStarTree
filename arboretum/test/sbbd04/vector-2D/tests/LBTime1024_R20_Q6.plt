set title "Vector2D - Disjuntive Complex Queries D= 1.929000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	610
0.002000	766
0.005000	1234
0.010000	2281
0.020000	5344
0.050000	25266
end
####################
0.001000	531
0.002000	593
0.005000	750
0.010000	1094
0.020000	2078
0.050000	8703
end
####################

pause -1