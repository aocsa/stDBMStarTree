set title "Cities - Disjuntive Complex Queries D= 3.200000  page=4096"
set xlabel "k"
set ylabel "AVG of Distance Function"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	1197.176000
0.002000	1383.508000
0.005000	1670.310000
0.010000	1898.932000
0.020000	2160.972000
0.050000	2537.548000
0.100000	2859.780000
end
####################
0.001000	1246.738000
0.002000	1449.064000
0.005000	1835.422000
0.010000	2227.904000
0.020000	2622.538000
0.050000	3410.140000
0.100000	4092.266000
end
####################

pause -1