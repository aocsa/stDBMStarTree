set title "MetricHisto Queries-page:8192"
set logscale xy
set xlabel "% dataset"
set ylabel "Total Time"
plot '-' title 'Generic Algorithms - Slim-Tree' with linespoints lt 1 lw 2 pt 1, '-' title 'Generic Algorithm - Seq-Scan' with linespoints lt 2 lw 2 pt 2, '-' title 'Basic Algorithms - Slim-Tree' with linespoints lt 3 lw 2 pt 3, '-' title 'Basic Algorithms - Seq-Scan' with linespoints lt 4 lw 2 pt 4, '-' title 'Range - Slim' with linespoints lt 5 lw 2 pt 5,