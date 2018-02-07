set title "Vector2D - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale xy 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
0.001000	0.832000	0.000000	2.523626
0.002000	2.336000	0.000000	6.253148
0.005000	11.052000	0.000000	26.714502
0.010000	36.554000	0.000000	84.469960
0.020000	126.488000	0.000000	285.539821
0.050000	670.320000	0.000000	1491.974919
end
####################
0.001000	0.844000	0.590800	1.097200
0.002000	2.438000	1.706600	3.169400
0.005000	12.040000	8.428000	15.652000
0.010000	40.274000	28.191800	52.356200
0.020000	139.838000	97.886600	181.789400
0.050000	743.118000	520.182600	966.053400
end
####################

pause -1