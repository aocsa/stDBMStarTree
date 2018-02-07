set title "Synt256D: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-MM: Measured' with error lt 1 lw 2 pt 1, '-' title 'DBM-MM: Estimated' with linespoints lt 5 lw 2 pt 5, '-' title 'DBM-MS: Measured' with error lt 2 lw 2 pt 2, '-' title 'DBM-MS: Estimated' with linespoints lt 6 lw 2 pt 6, '-' title 'DBM-GMM: Measured' with error lt 3 lw 2 pt 3, '-' title 'DBM-GMM: Estimated' with linespoints lt 9 lw 2 pt 9, '-' title 'DBM-MST: Measured' with error lt 4 lw 2 pt 4, '-' title 'DBM-MST: Estimated' with linespoints lt 10 lw 2 pt 10

####################
# DBMTree: Real0
0.0001	21.998	17.2245	26.7715
0.000215443	22.056	17.276	26.836
0.000464159	22.238	17.3951	27.0809
0.001	22.626	17.769	27.483
0.00215443	23.436	18.4454	28.4266
0.00464159	25.358	20.3045	30.4115
0.01	29.252	24.5547	33.9493
0.0215443	35.656	32.4973	38.8147
0.0464159	40.966	38.4195	43.5125
0.1	46.656	44.7456	48.5664
end
# DBMTree: Ciaccia-Node Estimation0
0.0001	18.3963
0.000215443	18.4695
0.000464159	18.5654
0.001	18.9732
0.00215443	19.3725
0.00464159	20.6473
0.01	23.8282
0.0215443	30.8094
0.0464159	39.5172
0.1	46.2929
end
# DBMTree: Real1
0.0001	17.966	12.8383	23.0937
0.000215443	18.054	12.895	23.213
0.000464159	18.228	13.0295	23.4265
0.001	18.644	13.3675	23.9205
0.00215443	19.552	14.1769	24.9271
0.00464159	21.334	15.9471	26.7209
0.01	24.944	19.9168	29.9712
0.0215443	30.196	26.9345	33.4575
0.0464159	33.978	31.3716	36.5844
0.1	37.766	35.2586	40.2734
end
# DBMTree: Ciaccia-Node Estimation1
0.0001	14.7043
0.000215443	14.7775
0.000464159	14.9137
0.001	15.1414
0.00215443	15.5732
0.00464159	16.8026
0.01	19.9304
0.0215443	26.5057
0.0464159	33.7992
0.1	37.6125
end
# DBMTree: Real2
0.0001	26.836	21.6528	32.0192
0.000215443	26.938	21.7605	32.1155
0.000464159	27.164	21.9959	32.3321
0.001	27.548	22.3158	32.7802
0.00215443	28.466	23.1578	33.7742
0.00464159	30.566	25.0464	36.0856
0.01	34.774	29.3756	40.1724
0.0215443	42.212	37.523	46.901
0.0464159	49.662	44.9397	54.3843
0.1	55.732	52.1959	59.2681
end
# DBMTree: Ciaccia-Node Estimation2
0.0001	23.1887
0.000215443	23.2425
0.000464159	23.3437
0.001	23.5981
0.00215443	24.5578
0.00464159	26.2425
0.01	29.7658
0.0215443	37.6241
0.0464159	48.192
0.1	55.5282
end
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