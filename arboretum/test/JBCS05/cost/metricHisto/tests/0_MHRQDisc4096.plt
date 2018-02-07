set title "metricHisto: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-MM: Measured' with error lt 1 lw 2 pt 1, '-' title 'DBM-MM: Estimated' with linespoints lt 5 lw 2 pt 5

####################
# DBMTree: Real0
0.0001	66.356	41.0401	91.6719
0.000215443	66.568	41.1893	91.9467
0.000464159	66.878	41.3357	92.4203
0.001	67.716	41.8373	93.5947
0.00215443	69.496	43.0047	95.9873
0.00464159	73.568	45.5607	101.575
0.01	82.71	50.9212	114.499
0.0215443	105.242	64.847	145.637
0.0464159	162.842	102.447	223.237
0.1	315.22	221.389	409.051
end
# DBMTree: Ciaccia-Node Estimation0
0.0001	77.465
0.000215443	77.5751
0.000464159	77.9703
0.001	78.5612
0.00215443	80.0571
0.00464159	83.562
0.01	92.1996
0.0215443	111.703
0.0464159	164.276
0.1	315.439
end

pause -1