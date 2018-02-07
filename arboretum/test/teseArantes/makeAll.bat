cd GenericNearest
call makeAll
cd ..

cd GenSimDNF
call makeAll
cd ..

cd RingRange
call makeAll
cd ..

cd scalability-30D
make -fscalar.mak > outMake.txt
cd ..

cd Seletividade
cd kVariado
call makeAll
cd ..
cd radiusVariado
call makeAll
cd ..
cd ..

cd Simples
call makeAll
cd ..

