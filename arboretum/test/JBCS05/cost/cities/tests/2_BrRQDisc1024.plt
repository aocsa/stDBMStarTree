set title "Cities: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-GMM: Measured' with error lt 3 lw 2 pt 3, '-' title 'DBM-GMM: Estimated' with linespoints lt 9 lw 2 pt 9

####################
# DBMTree: Real2
0.0001	4.602	3.542	5.662
0.000215443	4.612	3.54361	5.68039
0.000464159	4.636	3.57416	5.69784
0.001	4.674	3.61962	5.72838
0.00215443	4.794	3.72462	5.86338
0.00464159	5.018	3.8806	6.1554
0.01	5.43	4.24126	6.61874
0.0215443	6.536	5.07974	7.99226
0.0464159	9.116	6.858	11.374
0.1	15.126	11.1098	19.1422
end
# DBMTree: Ciaccia-Node Estimation2
0.0001	6.61151
0.000215443	6.62824
0.000464159	6.62824
0.001	6.64813
0.00215443	6.73538
0.00464159	7.00071
0.01	7.45731
0.0215443	8.55107
0.0464159	11.2784
0.1	17.4769
end

pause -1