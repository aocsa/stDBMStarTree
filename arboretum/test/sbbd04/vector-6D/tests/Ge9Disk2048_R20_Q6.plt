set title "Vector2D - Disjuntive Complex Queries D= 5.200000  page=2048"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	904.434000
0.002000	967.308000
0.005000	1077.290000
0.010000	1198.274000
0.020000	1373.360000
0.050000	1621.600000
end
####################
0.001000	999.078000
0.002000	1062.198000
0.005000	1169.136000
0.010000	1283.832000
0.020000	1492.040000
0.050000	1796.938000
end
####################

pause -1