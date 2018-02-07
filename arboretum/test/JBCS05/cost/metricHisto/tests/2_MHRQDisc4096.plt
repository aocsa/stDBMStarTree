set title "metricHisto: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-GMM: Measured' with error lt 3 lw 2 pt 3, '-' title 'DBM-GMM: Estimated' with linespoints lt 9 lw 2 pt 9

####################
# DBMTree: Real2
0.0001	64.474	44.4684	84.4796
0.000215443	64.608	44.5594	84.6566
0.000464159	64.898	44.7493	85.0467
0.001	65.556	45.2319	85.8801
0.00215443	67.2	46.3633	88.0367
0.00464159	70.346	48.3303	92.3617
0.01	78.31	53.3903	103.23
0.0215443	97.628	65.452	129.804
0.0464159	146.492	97.7638	195.22
0.1	281.424	202.27	360.578
end
# DBMTree: Ciaccia-Node Estimation2
0.0001	78.3867
0.000215443	78.5208
0.000464159	78.7899
0.001	79.5932
0.00215443	80.8437
0.00464159	83.9455
0.01	90.9651
0.0215443	109.193
0.0464159	155.443
0.1	293.048
end

pause -1