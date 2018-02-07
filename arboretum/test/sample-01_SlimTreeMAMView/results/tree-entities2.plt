set title "Number of Objects vs Number of Nodes"
set xlabel "Number of objects in the tree"
set ylabel "Count"
plot '-' title 'Nodes' with linespoints

10000	166
20000	307
30000	459
40000	607
50000	759
60000	904
70000	1056
80000	1207
90000	1365
100000	1515
end

pause -1

set title "Number of Objects vs Number of Connections"
set xlabel "Number of objects in the tree"
set ylabel "Count"
plot '-' title 'Connections' with linespoints

10000	10163
20000	20301
30000	30450
40000	40596
50000	50745
60000	60887
70000	71037
80000	81185
90000	91340
100000	101487
end

pause -1

set title "Number of Objects vs Number of Entities"
set xlabel "Number of objects in the tree"
set ylabel "Count"
plot '-' title 'Entities' with linespoints

10000	20329
20000	40608
30000	60909
40000	81203
50000	101504
60000	121791
70000	142093
80000	162392
90000	182705
100000	203002
end

pause -1
