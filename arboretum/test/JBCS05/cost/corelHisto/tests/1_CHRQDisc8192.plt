set title "colorHisto: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-MS: Measured' with error lt 2 lw 2 pt 2, '-' title 'DBM-MS: Estimated' with linespoints lt 6 lw 2 pt 6

####################
# DBMTree: Real1
0.0001	268.946	123.997	413.895
0.000215443	269.322	124.136	414.508
0.000464159	270.148	124.387	415.909
0.001	272.016	125.074	418.958
0.00215443	275.902	126.431	425.373
0.00464159	284.342	129.541	439.143
0.01	303.482	136.37	470.594
0.0215443	350.282	152.347	548.217
0.0464159	477.274	199.363	755.185
0.1	872.186	373.312	1371.06
end
# DBMTree: Ciaccia-Node Estimation1
0.0001	253.822
0.000215443	254.102
0.000464159	254.906
0.001	256.448
0.00215443	259.873
0.00464159	267.684
0.01	284.499
0.0215443	325.663
0.0464159	435.438
0.1	788.194
end

pause -1