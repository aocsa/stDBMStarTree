set title "Vector16D - Seletividade"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale xy 
plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, '-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8

####################
0.001000	0.328000	0.000000	0.994537
0.002000	0.328000	0.000000	0.994537
0.005000	0.328000	0.000000	0.994537
0.010000	0.328000	0.000000	0.994537
0.020000	0.334000	0.000000	1.015337
0.050000	0.492000	0.000000	1.478979
0.100000	3.466000	0.000000	8.465838
end
####################
0.001000	0.328000	0.229600	0.426400
0.002000	0.328000	0.229600	0.426400
0.005000	0.328000	0.229600	0.426400
0.010000	0.328000	0.229600	0.426400
0.020000	0.330000	0.231000	0.429000
0.050000	0.418000	0.292600	0.543400
0.100000	0.908000	0.635600	1.180400
end
####################

pause -1