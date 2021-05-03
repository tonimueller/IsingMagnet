#! /bin/sh

# importance sampling: time series 
# cp ../build/IsingMagnet/TimeSeries_IsingMagnet .
# samples=100
# N=20
# #./program nSamples LinearSizeLattice nIterations StepWide Temperature B-Field
# ./TimeSeries_IsingMagnet $samples $N 100 1 0.5 0
#importance sampling: 
samples=20
N=20
stepWide=20
nIterations=200
#total MCS=20*200=4000
B=0
cp ../build/IsingMagnet/IsingMagnet  .
./IsingMagnet $samples $N $nIterations $stepWide $B
