set terminal win
set key left Left
set title "Correlation Fractal Dimension of Cities"
set xlabel "log(r)"
set ylabel "log(N# of Pairs within r)"
plot 1.81*x + 12.2, '-'title 'Fractal Dimension of Cities' with linespoints 3,'-' title 'Frac-kNNQ' with linespoints 4
#Number of Points in Distance graphic: 18
3.002971 	16.441294
2.309824 	15.515685
1.616677 	14.733760
0.923529 	13.667834
0.230382 	12.616426
-0.462765 	11.422114
-1.155912 	10.265349
-1.849059 	9.364434
-2.542206 	8.107720
-3.235354 	6.492240
-3.928501 	4.762174
-4.621648 	3.610918
-5.314795 	2.639057
-6.007942 	1.386294
-6.701090 	1.098612
-7.394237 	1.098612
-8.087384 	1.098612
-8.780531 	1.098612
-9.473678 	0.000000
# Total summations=    23095249
end

#----------------------------------------
-0.850327       5.70378
0.46434 	8.08333
1.04785 	9.13949
1.42772 	9.82704
1.70987 	10.3377
1.93443 	10.7442
2.12097 	11.0818
2.28053 	11.3706
2.41992 	11.6229
2.54368 	11.8469
end

pause -1 
