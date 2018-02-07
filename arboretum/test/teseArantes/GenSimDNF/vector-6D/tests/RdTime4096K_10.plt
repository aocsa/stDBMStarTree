set title "MetricHisto Queries-page:4096"
set logscale xy
set xlabel "% dataset"
set ylabel "Total Time"
plot '-' title 'Generic Algorithms - Slim-Tree' with linespoints lt 1 lw 2 pt 1, '-' title 'Generic Algorithm - Seq-Scan' with linespoints lt 2 lw 2 pt 2, '-' title 'Basic Algorithms - Slim-Tree' with linespoints lt 3 lw 2 pt 3, '-' title 'Basic Algorithms - Seq-Scan' with linespoints lt 4 lw 2 pt 4, '-' title 'Range - Slim' with linespoints lt 5 lw 2 pt 5, '-' title 'Range - Seq-Scan' with linespoints lt 6 lw 2 pt 6, '-' title 'Nearest - Slim' with linespoints lt 7 lw 2 pt 7, '-' title 'Nearest - Seq-Scan' with linespoints lt 8 lw 2 pt 8, '-' title 'Single KAndRange - Slim' with linespoints lt 9 lw 2 pt 9, '-' title 'Single KAndRange - Seq-Scan' with linespoints lt 10 lw 2 pt 10, '-' title 'Single Nearest Intersection Range - Slim' with linespoints lt 11 lw 2 pt 11, '-' title 'Single Nearest Intersection Range - Seq-Scan' with linespoints lt 12 lw 2 pt 12

0.001000	0.532000
0.002000	0.547000
0.005000	0.594000
0.010000	0.594000
0.020000	0.641000
0.050000	0.797000
0.100000	1.172000
end
0.001000	34.859000
0.002000	35.359000
0.005000	34.953000
0.010000	34.500000
0.020000	34.265000
0.050000	34.171000
0.100000	34.094000
end
0.001000	13.922000
0.002000	13.938000
0.005000	14.062000
0.010000	14.218000
0.020000	15.985000
0.050000	13.860000
0.100000	14.219000
end
0.001000	72.453000
0.002000	71.453000
0.005000	70.469000
0.010000	70.219000
0.020000	70.297000
0.050000	68.890000
0.100000	69.297000
end
0.001000	0.172000
0.002000	0.188000
0.005000	0.187000
0.010000	0.187000
0.020000	0.203000
0.050000	0.281000
0.100000	0.375000
end
0.001000	11.359000
0.002000	11.922000
0.005000	11.735000
0.010000	12.094000
0.020000	11.422000
0.050000	11.422000
0.100000	11.828000
end
0.001000	4.328000
0.002000	5.078000
0.005000	4.469000
0.010000	4.687000
0.020000	4.328000
0.050000	4.328000
0.100000	4.422000
end
0.001000	11.297000
0.002000	12.484000
0.005000	12.484000
0.010000	12.219000
0.020000	11.406000
0.050000	11.703000
0.100000	11.266000
end
0.001000	0.172000
0.002000	0.188000
0.005000	0.187000
0.010000	0.203000
0.020000	0.219000
0.050000	0.281000
0.100000	0.375000
end
0.001000	11.172000
0.002000	12.047000
0.005000	11.954000
0.010000	11.891000
0.020000	11.281000
0.050000	11.360000
0.100000	11.156000
end
0.001000	4.484000
0.002000	4.593000
0.005000	4.703000
0.010000	4.640000
0.020000	4.531000
0.050000	4.562000
0.100000	4.672000
end
0.001000	23.156000
0.002000	24.016000
0.005000	24.672000
0.010000	23.657000
0.020000	23.032000
0.050000	23.156000
0.100000	22.953000
end

pause -1