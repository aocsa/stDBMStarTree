set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	328
0.002000	390
0.005000	578
0.010000	969
0.020000	1984
0.050000	7329
end
####################
0.001000	266
0.002000	297
0.005000	391
0.010000	531
0.020000	891
0.050000	2937
end
####################

pause -1