set title "Vector2D - Disjuntive Complex Queries D= 5.200000  page=2048"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	5109
0.002000	5734
0.005000	7359
0.010000	10547
0.020000	20313
0.050000	87344
end
####################
0.001000	4625
0.002000	5047
0.005000	5938
0.010000	7110
0.020000	10640
0.050000	38468
end
####################

pause -1