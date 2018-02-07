set title "Vector2D - Disjuntive Complex Queries D= 1.929000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	219.680000
0.002000	233.758000
0.005000	262.812000
0.010000	298.028000
0.020000	352.554000
0.050000	472.238000
end
####################
0.001000	240.732000
0.002000	250.846000
0.005000	272.056000
0.010000	298.498000
0.020000	339.658000
0.050000	439.256000
end
####################

pause -1