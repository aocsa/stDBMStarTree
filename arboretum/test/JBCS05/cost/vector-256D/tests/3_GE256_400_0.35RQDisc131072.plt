set title "Synt256D: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-MST: Measured' with error lt 4 lw 2 pt 4, '-' title 'DBM-MST: Estimated' with linespoints lt 10 lw 2 pt 10

####################
# DBMTree: Real3
0.0001	35.194	29.9511	40.4369
0.000215443	35.274	30.0404	40.5076
0.000464159	35.446	30.1667	40.7253
0.001	35.874	30.5906	41.1574
0.00215443	36.86	31.6026	42.1174
0.00464159	38.896	33.5484	44.2436
0.01	43.128	37.7775	48.4785
0.0215443	51.104	45.7992	56.4088
0.0464159	62.742	56.9424	68.5416
0.1	73.836	70.029	77.643
end
# DBMTree: Ciaccia-Node Estimation3
0.0001	31.2822
0.000215443	31.3487
0.000464159	31.4736
0.001	31.8892
0.00215443	32.8736
0.00464159	34.6359
0.01	38.685
0.0215443	47.0828
0.0464159	59.8961
0.1	73.0768
end


pause -1