set title "Vector2D - Disjuntive Complex Queries D= 5.200000  page=2048"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	4453
0.002000	4953
0.005000	6453
0.010000	9359
0.020000	19469
0.050000	84250
end
####################
0.001000	3891
0.002000	4312
0.005000	5031
0.010000	6078
0.020000	9359
0.050000	31375
end
####################

pause -1