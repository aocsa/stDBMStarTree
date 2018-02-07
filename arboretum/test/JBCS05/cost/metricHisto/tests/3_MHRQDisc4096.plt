set title "metricHisto: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-2CL: Measured' with error lt 4 lw 2 pt 4, '-' title 'DBM-2CL: Estimated' with linespoints lt 10 lw 2 pt 10

####################
# DBMTree: Real3
0.0001	68.922	48.7218	89.1222
0.000215443	69.068	48.8348	89.3012
0.000464159	69.366	49.0381	89.6939
0.001	69.942	49.519	90.365
0.00215443	71.136	50.5495	91.7225
0.00464159	73.956	52.7507	95.1613
0.01	80.764	58.0115	103.517
0.0215443	97.626	70.3825	124.869
0.0464159	141.996	101.326	182.666
0.1	265.772	195.908	335.636
end
# DBMTree: Ciaccia-Node Estimation3
0.0001	78.7738
0.000215443	78.8263
0.000464159	79.0106
0.001	79.5117
0.00215443	80.7804
0.00464159	84.0702
0.01	90.52
0.0215443	106.313
0.0464159	148.486
0.1	269.783
end


pause -1