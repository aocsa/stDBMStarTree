set title "Cities - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	291
0.002000	350
0.005000	501
0.010000	681
0.020000	1052
0.050000	2263
0.100000	4927
end
####################
0.001000	290
0.002000	331
0.005000	410
0.010000	521
0.020000	691
0.050000	1232
0.100000	2484
end
####################

pause -1