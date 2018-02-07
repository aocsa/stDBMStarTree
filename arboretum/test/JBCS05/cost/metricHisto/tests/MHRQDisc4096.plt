set title "metricHisto: Estimation of Disk Access"
set xlabel "% radius"
set ylabel "Avg Number of Disk Access"
set xrange [0.0001:0.1]
set logscale x
plot '-' title 'DBM-MM: Measured' with error lt 1 lw 2 pt 1, '-' title 'DBM-MM: Estimated' with linespoints lt 5 lw 2 pt 5, '-' title 'DBM-MS: Measured' with error lt 2 lw 2 pt 2, '-' title 'DBM-MS: Estimated' with linespoints lt 6 lw 2 pt 6, '-' title 'DBM-GMM: Measured' with error lt 3 lw 2 pt 3, '-' title 'DBM-GMM: Estimated' with linespoints lt 9 lw 2 pt 9, '-' title 'DBM-MST: Measured' with error lt 4 lw 2 pt 4, '-' title 'DBM-MST: Estimated' with linespoints lt 10 lw 2 pt 10

####################
# DBMTree: Real0
0.0001   66.276   41.0061  91.5459
0.000215443 66.366   41.0518  91.6802
0.000464159 66.604   41.2022  92.0058
0.001 66.92 41.3709  92.4691
0.00215443  67.822   41.9026  93.7414
0.00464159  69.76 43.1733  96.3467
0.01  74.128   45.8548  102.401
0.0215443   84.064   51.7512  116.377
0.0464159   108.72   67.106   150.334
0.1   172.372  108.96   235.784
end
# DBMTree: Ciaccia-Node Estimation0
0.0001   80.4808
0.000215443 80.5193
0.000464159 80.7408
0.001 81.3362
0.00215443  82.5423
0.00464159  84.816
0.01  90.1915
0.0215443   101.458
0.0464159   128.166
0.1   197.633
end
# DBMTree: Real1
0.0001   60.782   36.9488  84.6152
0.000215443 60.846   36.9844  84.7076
0.000464159 60.992   37.0894  84.8946
0.001 61.376   37.3339  85.4181
0.00215443  62.234   37.8738  86.5942
0.00464159  64.002   38.9808  89.0232
0.01  67.952   41.2811  94.6229
0.0215443   77.108   46.8197  107.396
0.0464159   99.176   60.3672  137.985
0.1   157.946  98.0939  217.798
end
# DBMTree: Ciaccia-Node Estimation1
0.0001   85.0594
0.000215443 85.1903
0.000464159 85.4038
0.001 86.06
0.00215443  87.7264
0.00464159  91.5446
0.01  98.9038
0.0215443   116.718
0.0464159   153.764
0.1   227.621
end
# DBMTree: Real2
0.0001   64.418   44.45 84.386
0.000215443 64.49 44.4786  84.5014
0.000464159 64.622   44.576   84.668
0.001 64.944   44.7923  85.0957
0.00215443  65.654   45.3048  86.0032
0.00464159  67.384   46.5003  88.2677
0.01  70.844   48.6338  93.0542
0.0215443   79.508   54.1751  104.841
0.0464159   100.566  67.3768  133.755
0.1   154.474  103.25   205.698
end
# DBMTree: Ciaccia-Node Estimation2
0.0001   67.3228
0.000215443 67.3424
0.000464159 67.443
0.001 67.7425
0.00215443  68.4967
0.00464159  70.0197
0.01  72.8427
0.0215443   80.4575
0.0464159   97.6501
0.1   149.124
end
# DBMTree: Real3
0.0001   68.87 48.6797  89.0603
0.000215443 68.932   48.7268  89.1372
0.000464159 69.088   48.8486  89.3274
0.001 69.402   49.0805  89.7235
0.00215443  70.038   49.6036  90.4724
0.00464159  71.306   50.6453  91.9667
0.01  74.442   53.1307  95.7533
0.0215443   81.894   58.875   104.913
0.0464159   100.236  72.3047  128.167
0.1   149.064  106.178  191.95
end
# DBMTree: Ciaccia-Node Estimation3
0.0001   78.705
0.000215443 78.7461
0.000464159 78.7555
0.001 79.104
0.00215443  79.7234
0.00464159  80.9326
0.01  83.803
0.0215443   90.7238
0.0464159   107.663
0.1   154.721
end


pause -1