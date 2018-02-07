set title "Cities - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	60.882000
0.002000	64.144000
0.005000	71.990000
0.010000	80.112000
0.020000	92.306000
0.050000	119.738000
0.100000	152.788000
end
####################
0.001000	69.748000
0.002000	72.894000
0.005000	78.046000
0.010000	85.178000
0.020000	94.612000
0.050000	116.320000
0.100000	143.346000
end
####################

pause -1