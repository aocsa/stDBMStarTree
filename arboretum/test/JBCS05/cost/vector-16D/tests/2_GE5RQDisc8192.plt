set title "Synt16D: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-GMM: Measured' with error lt 3 lw 2 pt 3, '-' title 'DBM-GMM: Estimated' with linespoints lt 9 lw 2 pt 9

####################
# DBMTree: Real2
0.0001	16.418	11.2606	21.5754
0.000215443	16.458	11.302	21.614
0.000464159	16.538	11.3828	21.6932
0.001	16.698	11.4808	21.9152
0.00215443	16.968	11.6986	22.2374
0.00464159	17.672	12.3076	23.0364
0.01	19.132	13.5504	24.7136
0.0215443	22.34	16.4909	28.1891
0.0464159	28.81	23.6214	33.9986
0.1	36.076	33.2536	38.8984
end
# DBMTree: Ciaccia-Node Estimation2
0.0001	13.7131
0.000215443	13.7672
0.000464159	13.8436
0.001	13.9665
0.00215443	14.1926
0.00464159	14.777
0.01	15.8992
0.0215443	18.7244
0.0464159	24.7841
0.1	34.2571
end

pause -1