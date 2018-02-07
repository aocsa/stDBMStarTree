set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	68.020000
0.002000	72.376000
0.005000	81.054000
0.010000	91.084000
0.020000	105.408000
0.050000	134.124000
end
####################
0.001000	75.730000
0.002000	79.384000
0.005000	86.224000
0.010000	94.578000
0.020000	107.218000
0.050000	134.102000
end
####################

pause -1