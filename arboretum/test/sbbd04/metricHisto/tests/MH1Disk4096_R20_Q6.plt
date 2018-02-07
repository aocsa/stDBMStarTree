set title "Cities - Disjuntive Complex Queries D= 3.200000  page=4096"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	236.610000
0.002000	253.812000
0.005000	281.538000
0.010000	304.178000
0.020000	330.492000
0.050000	371.048000
0.100000	409.370000
end
####################
0.001000	271.116000
0.002000	289.852000
0.005000	330.412000
0.010000	376.734000
0.020000	416.840000
0.050000	507.110000
0.100000	583.052000
end
####################

pause -1