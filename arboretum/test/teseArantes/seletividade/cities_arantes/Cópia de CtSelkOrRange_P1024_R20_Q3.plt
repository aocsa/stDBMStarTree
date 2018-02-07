set title "Cidades Brasileiras - Estimativa de Seletividade  page=1024"
set xlabel "k"
set ylabel "Estimativa de Seletividade - Cardinalidade "
set logscale y 
plot '-' title '(A) Cardinalidade usando Seletividade XX' with linespoints 1, '-' title '(B) Cardinalidade Real' with linespoints 2, '-' title '(C) Erro Acima' with linespoints 3, '-' title '(D) Erro Abaixo' with linespoints 4

####################
25	67.067064
81	128.460630
137	182.461263
193	235.811771
249	289.337710
305	342.330825
361	394.932370
417	447.184235
473	499.623944
529	552.759594
end
####################
25	28.436000
81	92.994000
137	156.246000
193	218.620000
249	284.252000
305	352.088000
361	416.696000
417	479.042000
473	542.578000
529	605.080000
end
####################
25	87.187184
81	166.998819
137	237.199642
193	306.555302
249	376.139024
305	445.030072
361	513.412082
417	581.339505
473	649.511127
529	718.587472
end
####################
25	46.946945
81	89.922441
137	127.722884
193	165.068240
249	202.536397
305	239.631577
361	276.452659
417	313.028964
473	349.736761
529	386.931716
end
####################

pause -1