set title "MetricHisto Queries-page:8192"
set logscale xy
set xlabel "% dataset"
set ylabel "Total Time"
plot '-' title 'Generic Algorithms - Slim-Tree' with linespoints lt 1 lw 2 pt 1, '-' title 'Generic Algorithm - Seq-Scan' with linespoints lt 2 lw 2 pt 2, '-' title 'Basic Algorithms - Slim-Tree' with linespoints lt 3 lw 2 pt 3, '-' title 'Basic Algorithms - Seq-Scan' with linespoints lt 4 lw 2 pt 4, '-' title 'Range - Slim' with linespoints lt 5 lw 2 pt 5, '-' title 'Range - Seq-Scan' with linespoints lt 6 lw 2 pt 6, '-' title 'Nearest - Slim' with linespoints lt 7 lw 2 pt 7, '-' title 'Nearest - Seq-Scan' with linespoints lt 8 lw 2 pt 8, '-' title 'Single KAndRange - Slim' with linespoints lt 9 lw 2 pt 9, '-' title 'Single KAndRange - Seq-Scan' with linespoints lt 10 lw 2 pt 10, '-' title 'Single Nearest Intersection Range - Slim' with linespoints lt 11 lw 2 pt 11, '-' title 'Single Nearest Intersection Range - Seq-Scan' with linespoints lt 12 lw 2 pt 12

0.001000	0.281000
0.002000	0.297000
0.005000	0.422000
0.010000	0.625000
0.020000	0.656000
end
0.001000	4.235000
0.002000	4.594000
0.005000	4.297000
0.010000	4.328000
0.020000	4.313000
end
0.001000	3.812000
0.002000	4.031000
0.005000	4.063000
0.010000	4.656000
0.020000	17.344000
end
0.001000	8.578000
0.002000	8.906000
0.005000	8.906000
0.010000	9.250000
0.020000	20.047000
end
0.001000	0.062000
0.002000	0.094000
0.005000	0.125000
0.010000	0.250000
0.020000	4.875000
end
0.001000	1.438000
0.002000	1.484000
0.005000	1.469000
0.010000	1.437000
0.020000	5.968000
end
0.001000	1.031000
0.002000	1.031000
0.005000	1.016000
0.010000	1.078000
0.020000	1.016000
end
0.001000	1.437000
0.002000	1.453000
0.005000	1.453000
0.010000	1.422000
0.020000	1.437000
end
0.001000	0.078000
0.002000	0.078000
0.005000	0.125000
0.010000	0.172000
0.020000	0.188000
end
0.001000	1.422000
0.002000	1.454000
0.005000	1.422000
0.010000	1.438000
0.020000	1.422000
end
0.001000	1.110000
0.002000	1.140000
0.005000	1.172000
0.010000	1.265000
0.020000	5.937000
end
0.001000	2.953000
0.002000	3.031000
0.005000	2.875000
0.010000	2.860000
0.020000	7.422000
end

pause -1