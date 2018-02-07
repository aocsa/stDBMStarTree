set title "Vector2D - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale xy 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
0.001000	0.640000	0.000000	1.843993
0.002000	1.898000	0.000000	4.845679
0.005000	10.512000	0.000000	24.526469
0.010000	37.546000	0.000000	84.104641
0.020000	131.756000	0.000000	285.783741
0.050000	685.836000	0.000000	1428.892804
end
####################
0.001000	0.642000	0.449400	0.834600
0.002000	1.984000	1.388800	2.579200
0.005000	11.536000	8.075200	14.996800
0.010000	41.628000	29.139600	54.116400
0.020000	146.346000	102.442200	190.249800
0.050000	760.526000	532.368200	988.683800
end
####################

pause -1