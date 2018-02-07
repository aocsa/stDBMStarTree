set title "Vector2D - Disjuntive Complex Queries D= 4.670000  page=4096"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	2443
0.002000	2514
0.005000	2894
0.010000	3405
0.020000	4376
0.050000	8693
0.100000	20940
end
####################
0.001000	2273
0.002000	2363
0.005000	2584
0.010000	2894
0.020000	3485
0.050000	5748
0.100000	11497
end
####################

pause -1