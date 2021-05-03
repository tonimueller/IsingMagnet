
#include <cstdint>
#include <cstring>
#include <cmath>
#include <iostream>
#include <string>
#include "isingLattice.h"
#include "filewriter.h"
int main(int argc, char* argv[]){
    uint32_t N(20);
    uint32_t nSamples(5);
    auto nIterations=200;
    auto nSteps=20;
    double B(0.0);
    double temp(0.1);
    
    if(!(argc==6 || argc==7 )|| (argc==2 && strcmp(argv[1],"--help")==0 ))
	{
		std::string errormessage;
		errormessage="usage: ./isingMagnet numberOfSamples sizeOfLattice  nIterations nSteps temperature magneticFieldStrength \n";
		throw std::runtime_error(errormessage);
	}
	else
	{
		nSamples=atoi(argv[1]);
        N=atoi(argv[2]);
        nIterations=atoi(argv[3]);
        nSteps=atoi(argv[4]);
        temp=atof(argv[5]);
		if(argc==7) B=atof(argv[6]);
	}
    //instance of a lattice 
    IsingLattice lattice(N,1,B); 
    //Metropolis

    std::string outputM("TimeSeriesMagnet_ImportanceSampling.dat");
    std::string outputE("TimeSeriesEnergy_ImportanceSampling.dat");
    std::vector<std::vector<double> > mag(nSamples, std::vector<double>(nIterations,0.));
    std::vector<std::vector<double> > energy(nSamples, std::vector<double>(nIterations,0.));
    std::vector<double> time(nIterations,0.);

    for(auto n=0;n<nSamples;n++){
        std::cout << "Sample: " << n << std::endl;
        lattice.fillLattice();
        for(auto it=0;it<nIterations;it++){
            lattice.MCStep(temp,nSteps);
            double E(lattice.getEnergy());
            double M((lattice.getMagnetization()));
            mag[n][it]=M;
            energy[n][it]=E;
        }
    }
    for(auto it=0;it<nIterations;it++)
        time[it]=it*nSteps;
    FileWriter writer(outputM);
    std::vector<std::vector<double> > data=mag;
    data.insert(data.begin(),time);
    writer.writeData(data,"time M\n");

    data.resize(0);
    writer.setFilename(outputE);
    data=energy;
    data.insert(data.begin(),time);
    writer.writeData(data,"time E\n");

};