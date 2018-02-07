set title "Vector2D - Disjuntive Complex Queries D= 5.400000  page=2048"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	5922
0.002000	6656
0.005000	8437
0.010000	11718
0.020000	21922
0.050000	93781
end
####################
0.001000	5406
0.002000	5890
0.005000	6891
0.010000	8344
0.020000	12172
0.050000	45438
end
####################

pause -1