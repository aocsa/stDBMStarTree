set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	49.286000
0.002000	53.344000
0.005000	65.458000
0.010000	70.698000
0.020000	81.578000
0.050000	104.912000
end
####################
0.001000	54.940000
0.002000	55.702000
0.005000	72.516000
0.010000	75.678000
0.020000	83.702000
0.050000	105.534000
end
####################

pause -1