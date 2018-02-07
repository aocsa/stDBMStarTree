set title "Cities - Disjuntive Complex Queries D= 1.810000  page=2048"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	22.068000
0.002000	23.432000
0.005000	26.490000
0.010000	29.818000
0.020000	34.432000
0.050000	45.100000
0.100000	57.740000
end
####################
0.001000	24.606000
0.002000	25.888000
0.005000	28.334000
0.010000	31.402000
0.020000	35.536000
0.050000	45.308000
0.100000	57.360000
end
####################

pause -1