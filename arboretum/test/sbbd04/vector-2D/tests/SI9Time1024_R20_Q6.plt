set title "Vector2D - Disjuntive Complex Queries D= 1.830000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	250
0.002000	312
0.005000	469
0.010000	765
0.020000	1656
0.050000	6266
end
####################
0.001000	203
0.002000	235
0.005000	297
0.010000	422
0.020000	719
0.050000	2421
end
####################

pause -1