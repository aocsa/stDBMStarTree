set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	281
0.002000	328
0.005000	515
0.010000	906
0.020000	1985
0.050000	7407
end
####################
0.001000	250
0.002000	266
0.005000	313
0.010000	453
0.020000	828
0.050000	2843
end
####################

pause -1