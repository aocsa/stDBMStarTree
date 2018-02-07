set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	116.090000
0.002000	120.556000
0.005000	133.622000
0.010000	155.066000
0.020000	185.774000
0.050000	248.832000
end
####################
0.001000	132.286000
0.002000	134.262000
0.005000	138.528000
0.010000	158.748000
0.020000	177.582000
0.050000	229.206000
end
####################

pause -1