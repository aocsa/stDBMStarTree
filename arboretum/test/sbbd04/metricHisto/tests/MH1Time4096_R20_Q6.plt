set title "Cities - Disjuntive Complex Queries D= 3.200000  page=4096"
set xlabel "k"
set ylabel "Total Time"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	24536
0.002000	28200
0.005000	33899
0.010000	39187
0.020000	43973
0.050000	52515
0.100000	61369
end
####################
0.001000	25817
0.002000	29753
0.005000	37394
0.010000	45195
0.020000	54208
0.050000	69019
0.100000	83880
end
####################

pause -1