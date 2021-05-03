
#include <stdlib.h>
#include <vector>
#ifndef ISING_LATTICE_H
#define ISING_LATTICE_H


class IsingLattice{
public:
    //!constructor of the class 
    IsingLattice(const uint32_t N_=100, double J_=1, double B_=0 ):
    N(N_),J(J_),B(B_),size(N*N),energy(0.),magnetization(0.){srand(time(NULL));};
    //!fill lattice with spins 
    void fillLattice(){
        Lattice.resize(0);
        Lattice.resize(size);
        for (auto i=0; i < size ; i++)
            Lattice[i]=getRandomSpin();
    }
    //! get magnetization per lattice site 
    double const  getMagnetization(){calcMagnetization(); return magnetization;}
    //! get energy per lattice site 
    double const  getEnergy(){ calcEnergy(); return energy;}
    //!get the lattice entry by x and y coordinate 
    int const getLatticeEntry(uint32_t x, uint32_t y ){ return Lattice[x+y*N]; }
    int const getLatticeEntry(uint32_t i ){ return Lattice[i]; }
    //!set amplitude of the magnetic field
    void setField(double B_){B=B_;}
    //!print lattice  to stdout
    void printLattice(){
        for(auto x=0;x<N;x++){
            for(auto y=0;y<N;y++)
                std::cout << getLatticeEntry(x,y) << " ";
            std::cout << "\n";
        }
    }
    //!MCStep
    uint32_t MCStep(double temp, uint32_t steps){
        uint32_t acceptedMoves(0);
        for(auto i=0; i<steps;i++){
            for(auto j=0;j<size; j++){
                auto id(getRandomIndex());
                double e(singleSpinEnergy(getX(id),getY(id)));
                double p(exp(2.0*e/temp));
                double rnd(static_cast<double>(rand()) / RAND_MAX);
                if( e>0 ){
                    acceptedMoves++;
                    Lattice[id]*=-1.;
                }else if (  rnd<p  ){
                    acceptedMoves++;
                    Lattice[id]*=-1.;
                }
            }
        }
        // std::cout << "Accpected Moves = " << acceptedMoves << std::endl;
        return acceptedMoves;
    }
private:
    
    int setLatticeEntry(uint32_t x, uint32_t y, int value  ){ return Lattice[x+y*N]=value; }
    int setLatticeEntry(uint32_t idx, int value  ){ return Lattice[idx]=value; }
    double singleSpinEnergy(const uint32_t x, const uint32_t y){
        auto s=  getLatticeEntry(refold(x+1),y)
                +getLatticeEntry(refold(x-1),y)
                +getLatticeEntry(x,refold(y-1))
                +getLatticeEntry(x,refold(y+1));
        return -1.0*getLatticeEntry(x,y)*(J*0.5*s+B);
    }
    void calcEnergy(){
        energy=0;
        for(auto i=0;i<size;i++)
            energy+=singleSpinEnergy(getX(i),getY(i));
        energy/=(2.*static_cast<double>(size));
    }
    void calcMagnetization(){
        magnetization=0;
        for(auto i=0;i<size;i++)
            magnetization+=getLatticeEntry(i);
        magnetization/=static_cast<double>(size);
    }

    uint32_t getX(int ID){ return ID % N;}
    uint32_t getY(int ID){ return (ID - getX(ID))/N ;}
    //refold coordinate to linear size 
    int refold(int x){return x % N; };
    //! get a random index of the lattice 
    uint32_t getRandomIndex(){return rand()%size;}
    //!get random spin (up=1, down =-1)
    int getRandomSpin(){ return 2*(rand()%2)-1;  }
    // int getRandomSpin(){ return -1;  }
    //!linear size of the lattice 
    uint32_t N;
    //!square size of the lattice 
    uint32_t size;
    //!next neighbor interaction 
    double J; 
    //!magnetic field strenght 
    double B; 
    //!spin lattice 
    std::vector<int> Lattice; 
    //!magnetic energy per spin 
    double energy;
    //!magnetization of the lattice 
    double magnetization; 
};

#endif /*ISING_LATTICE_H*/