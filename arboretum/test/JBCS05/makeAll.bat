cd cities
make -s -f Cities.mak > outMake.txt
cd ..

cd corelHisto
make -s -f corelHisto.mak > outMake.txt
cd ..

cd metricHisto
make -s -f metricHisto.mak > outMake.txt
cd ..

cd scalability-16D
make -s -f Scalar.mak > outMake.txt
cd ..

cd scalability-2D
make -s -f Scalar.mak > outMake.txt
cd ..

cd scalability-30D
make -s -f Scalar.mak > outMake.txt
cd ..

cd scalability-6D
make -s -f Scalar.mak > outMake.txt
cd ..

cd ShrinkCorelHisto
make -s -f corelHisto.mak > outMake.txt
cd ..

cd ShrinkVector-16D
make -s -f vector.mak > outMake.txt
cd ..

cd ShrinkVector-256D
make -s -f vector.mak > outMake.txt
cd ..

cd ShrinkVector-6D
make -s -f vector.mak > outMake.txt
cd ..

cd vector-16D
make -s -f vector.mak > outMake.txt
cd ..

cd vector-256D
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
