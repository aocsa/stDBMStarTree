set title "Conjunto de Dados: metricHisto  page=8192, ratio (outer/inner) =0.40"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. M�dio de C�lculo de Dist�ncia"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	123.970000
0.002000	139.680000
0.005000	185.980000
0.010000	262.412000
0.020000	417.184000
0.050000	915.548000
0.100000	1850.728000
end
# SlimTree-RingRange Intersection
0.001000	238.774000
0.002000	260.744000
0.005000	325.820000
0.010000	433.386000
0.020000	649.942000
0.050000	1341.468000
0.100000	2649.450000
end
# SlimTree-Range
0.001000	124.030000
0.002000	139.742000
0.005000	186.078000
0.010000	262.666000
0.020000	418.132000
0.050000	923.336000
0.100000	1902.182000
end
# SeqScan-RingRange
0.001000	4247.000000
0.002000	4247.000000
0.005000	4247.000000
0.010000	4247.000000
0.020000	4247.000000
0.050000	4247.000000
0.100000	4247.000000
end
# SeqScan-RingRange Intersection
0.001000	8494.000000
0.002000	8494.000000
0.005000	8494.000000
0.010000	8494.000000
0.020000	8494.000000
0.050000	8494.000000
0.100000	8494.000000
end
# SeqScan-Range
0.001000	4247.000000
0.002000	4247.000000
0.005000	4247.000000
0.010000	4247.000000
0.020000	4247.000000
0.050000	4247.000000
0.100000	4247.000000
end

pause -1