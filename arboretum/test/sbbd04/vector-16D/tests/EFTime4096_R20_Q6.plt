set title "Vector2D - Disjuntive Complex Queries D= 4.670000  page=4096"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	2304
0.002000	2504
0.005000	2894
0.010000	3435
0.020000	4546
0.050000	8622
0.100000	20770
end
####################
0.001000	2103
0.002000	2253
0.005000	2504
0.010000	2794
0.020000	3495
0.050000	5468
0.100000	10755
end
####################

pause -1