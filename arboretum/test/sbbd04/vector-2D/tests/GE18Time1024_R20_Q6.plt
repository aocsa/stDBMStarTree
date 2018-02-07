set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	5141
0.002000	6437
0.005000	10390
0.010000	18610
0.020000	41469
0.050000	189672
end
####################
0.001000	4250
0.002000	4938
0.005000	6891
0.010000	10781
0.020000	21781
0.050000	97984
end
####################

pause -1