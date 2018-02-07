set title "Vector2D - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale xy 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
0.001000	14.506000	0.000000	31.075967
0.002000	29.322000	0.000000	62.239849
0.005000	71.636000	0.000000	149.405638
0.010000	142.790000	0.000000	298.629591
0.020000	286.318000	0.000000	594.231285
0.050000	706.172000	0.000000	1463.351964
0.100000	1419.198000	0.000000	2949.173503
end
####################
0.001000	116.578000	81.604600	151.551400
0.002000	162.138000	113.496600	210.779400
0.005000	251.526000	176.068200	326.983800
0.010000	351.774000	246.241800	457.306200
0.020000	493.300000	345.310000	641.290000
0.050000	772.542000	540.779400	1004.304600
0.100000	1071.324000	749.926800	1392.721200
end
####################

pause -1