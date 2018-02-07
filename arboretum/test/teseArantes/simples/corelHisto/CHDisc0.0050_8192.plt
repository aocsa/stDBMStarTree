set title "Conjunto de Dados: ColorHisto  page=8192,  k=0.0050"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Acesso a Disco"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, '-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, 