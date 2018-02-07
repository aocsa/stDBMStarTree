set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	281
0.002000	359
0.005000	594
0.010000	984
0.020000	2047
0.050000	7485
end
####################
0.001000	250
0.002000	250
0.005000	375
0.010000	531
0.020000	891
0.050000	2984
end
####################

pause -1