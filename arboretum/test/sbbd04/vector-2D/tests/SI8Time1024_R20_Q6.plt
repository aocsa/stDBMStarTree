set title "Vector2D - Disjuntive Complex Queries D= 1.830000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	62
0.002000	94
0.005000	109
0.010000	156
0.020000	281
0.050000	797
end
####################
0.001000	63
0.002000	63
0.005000	78
0.010000	110
0.020000	172
0.050000	375
end
####################

pause -1