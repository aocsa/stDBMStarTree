set title "Cities - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	60.862000
0.002000	64.130000
0.005000	71.964000
0.010000	80.090000
0.020000	92.266000
0.050000	119.608000
0.100000	152.580000
end
####################
0.001000	67.922000
0.002000	71.062000
0.005000	75.830000
0.010000	82.582000
0.020000	91.820000
0.050000	112.898000
0.100000	139.192000
end
####################

pause -1