cd corelHisto
make -s -f corelHisto.mak > outMake.txt
cd ..

cd vector-16D
make -s -f vector.mak > outMake.txt
cd ..


cd vector-256D
make -s -f vector.mak > outMake.txt
cd ..