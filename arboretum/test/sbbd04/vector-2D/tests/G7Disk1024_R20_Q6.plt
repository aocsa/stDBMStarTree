set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	69.316000
0.002000	73.562000
0.005000	81.594000
0.010000	90.534000
0.020000	103.090000
0.050000	129.166000
end
####################
0.001000	77.152000
0.002000	80.716000
0.005000	87.378000
0.010000	95.118000
0.020000	106.740000
0.050000	131.006000
end
####################

pause -1