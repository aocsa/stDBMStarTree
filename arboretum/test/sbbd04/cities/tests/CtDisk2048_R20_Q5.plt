set title "Cities - Disjuntive Complex Queries D= 1.810000  page=2048"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	22.070000
0.002000	23.438000
0.005000	26.496000
0.010000	29.840000
0.020000	34.466000
0.050000	45.166000
0.100000	57.880000
end
####################
0.001000	25.266000
0.002000	26.530000
0.005000	29.148000
0.010000	32.360000
0.020000	36.576000
0.050000	46.682000
0.100000	59.128000
end
####################

pause -1