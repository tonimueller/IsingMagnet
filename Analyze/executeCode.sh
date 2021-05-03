#! /bin/sh

# importance sampling: time series 
# cp ../build/IsingMagnet/TimeSeries_IsingMagnet .
# samples=100
# N=20
# #./program nSamples LinearSizeLattice nIterations StepWide Temperature B-Field
# ./TimeSeries_IsingMagnet $samples $N 100 1 0.5 0
#importance sampling: 
samples=20
N=32
stepWide=20
nIterations=200
#total MCS=20*200=4000
B=0
cp ../build/IsingMagnet/IsingMagnet  .
./IsingMagnet $samples $N $nIterations $stepWide $B

# N=32
#                      total    time/(MCS*Sample*size)
# original Code needs: 192.852s 117.7ns
# XY-Lookup          : 169.464s 103.433ns
# Bitshift Refold    : 122.366s 74.6863ns 
# Energy calc with IF: 124.914s 76.2416ns (declined)
# E_tot for loop opti: 123.033s 75.0933ns (declined)

#N=16
#                      total    time/(MCS*Sample*size)
# original Code needs: 
# XY-Lookup          : 43.2275s 105.536ns
# Bitshift RND Number: 39.3425s 96.0511ns
# Bitshift Refold    : 30.5678s 74.6285ns
# Energy calc with IF: 31.898s  77.8759ns
#

