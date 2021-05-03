#! /bin/sh
samples=100
N=20
# cp ../cpp/build/IsingMagnet/IsingMagnet  .
# ./IsingMagnet $samples $N 0 

cp ../cpp/build/IsingMagnet/TimeSeries_IsingMagnet .
./TimeSeries_IsingMagnet $samples $N 100 1 0.5 0
