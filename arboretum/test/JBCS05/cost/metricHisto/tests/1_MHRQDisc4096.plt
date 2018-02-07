set title "metricHisto: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-MS: Measured' with error lt 2 lw 2 pt 2, '-' title 'DBM-MS: Estimated' with linespoints lt 6 lw 2 pt 6

####################
# DBMTree: Real1
0.0001	60.836	36.9699	84.7021
0.000215443	60.97	37.0681	84.8719
0.000464159	61.31	37.2774	85.3426
0.001	62.142	37.8204	86.4636
0.00215443	63.794	38.8325	88.7555
0.00464159	67.45	41.0261	93.8739
0.01	75.788	45.9824	105.594
0.0215443	95.996	58.3709	133.621
0.0464159	149.16	92.1125	206.208
0.1	293.056	205.157	380.955
end
# DBMTree: Ciaccia-Node Estimation1
0.0001	69.7779
0.000215443	69.9551
0.000464159	70.1726
0.001	71.023
0.00215443	72.6373
0.00464159	76.0821
0.01	83.2579
0.0215443	101.977
0.0464159	150.725
0.1	290.381
end

pause -1