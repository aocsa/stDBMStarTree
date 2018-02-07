set title "Vector2D - Disjuntive Complex Queries D= 1.810000  page=1024"
set xlabel "k"
set ylabel "AVG of Disk Access"
set logscale x
plot '-' title '(A) kOrRange()' with linespoints 1, '-' title '(B) Simple kOrRange()' with linespoints 2

####################
0.001000	119.048000
0.002000	127.588000
0.005000	149.946000
0.010000	171.662000
0.020000	203.192000
0.050000	270.564000
end
####################
0.001000	132.884000
0.002000	133.344000
0.005000	154.042000
0.010000	173.734000
0.020000	195.872000
0.050000	254.822000
end
####################

pause -1