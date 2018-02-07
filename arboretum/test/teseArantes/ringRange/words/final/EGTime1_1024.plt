set title "Conjunto de Dados: Words  page=1024, ratio (outer/inner) =1.00"
set logscale y
set xlabel "% raio"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
2	38.063000
3	48.703000
4	59.859000
5	78.813000
6	105.875000
7	123.250000
end
# SlimTree-RingRange Intersection
2	63.110000
3	86.547000
4	120.750000
5	303.719000
6	1642.141000
7	6405.938000
end
# SlimTree-Range
2	38.078000
3	49.047000
4	67.968000
5	152.000000
6	480.719000
7	1433.047000
end
# SeqScan-RingRange
2	59.609000
3	60.016000
4	63.719000
5	77.625000
6	101.359000
7	116.859000
end
# SeqScan-RingRange Intersection
2	118.968000
3	119.750000
4	136.297000
5	309.812000
6	1692.906000
7	6679.484000
end
# SeqScan-Range
2	59.625000
3	60.313000
4	71.610000
5	150.578000
6	479.484000
7	1474.453000
end

pause -1