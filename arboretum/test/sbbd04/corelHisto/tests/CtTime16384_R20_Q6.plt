set title "Vector2D - Disjuntive Complex Queries D= 0.682200  page=16384"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	71533
0.002000	77902
0.005000	89879
0.010000	113523
0.020000	198546
0.050000	718844
end
####################
0.001000	70611
0.002000	75969
0.005000	85233
0.010000	102337
0.020000	164526
0.050000	525986
end
####################

pause -1