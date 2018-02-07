cd cities
make -s -f Cities.mak > outMake.txt
cd ..

cd corelHisto
make -s -f corelHisto.mak > outMake.txt
cd ..

cd metricHisto
make -s -f metricHisto.mak > outMake.txt
cd ..

cd vector-16D
make -s -f vector.mak > outMake.txt
cd ..

cd vector-2D
make -s -f vector.mak > outMake.txt
cd ..

cd vector-6D
make -s -f vector.mak > outMake.txt
cd ..

cd words
make -s -f words.mak > outMake.txt
cd ..
