set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	235
0.002000	281
0.005000	438
0.010000	844
0.020000	1797
0.050000	7031
end
####################
0.001000	219
0.002000	234
0.005000	265
0.010000	437
0.020000	796
0.050000	2813
end
####################

pause -1