set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	46.057550
0.002000	48.447250
0.005000	52.907450
0.010000	57.357050
0.020000	64.006600
0.050000	105.890200
end
####################
0.001000	51.850700
0.002000	53.926000
0.005000	57.986500
0.010000	62.289600
0.020000	67.651650
0.050000	91.612650
end
####################

pause -1