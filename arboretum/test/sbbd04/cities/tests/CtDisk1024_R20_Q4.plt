set title "Cities - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	60.894000
0.002000	64.166000
0.005000	72.020000
0.010000	80.154000
0.020000	92.400000
0.050000	120.026000
0.100000	153.226000
end
####################
0.001000	72.676000
0.002000	75.934000
0.005000	81.338000
0.010000	88.856000
0.020000	98.830000
0.050000	121.476000
0.100000	149.758000
end
####################

pause -1