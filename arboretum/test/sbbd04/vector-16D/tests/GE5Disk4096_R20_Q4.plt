set title "Vector2D - Disjuntive Complex Queries D= 7.044500  page=4096"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	130.072000
0.002000	133.656000
0.005000	139.298000
0.010000	145.320000
0.020000	154.958000
0.050000	189.856000
0.100000	349.722000
end
####################
0.001000	158.598000
0.002000	162.660000
0.005000	168.700000
0.010000	175.062000
0.020000	183.660000
0.050000	204.772000
0.100000	382.682000
end
####################

pause -1