//
#include <valarray>
#include <string>
#include <fstream> 
#include <unistd.h> // getopt
#include <cmath> // pow
#include <time.h> // time
#include <complex>
using std::complex;

#include "PureState.h"
#include "MixedState.h"
#include "display.h"


void usage( void ) {
    std::cout << "Usage: stepper [options]" << std::endl
         << "Where options are:" << std::endl
         << "-d prob-datafile " << std::endl
         << "-n num-steps"  << std::endl
         << "-o bures-datafile" << std::endl
         << "-q num-qubits"  << std::endl
         << "-s step-size"  << std::endl
         << "-u noise-threshold" << std::endl;
    exit(1);
}

int main( int argc, char* argv[] ) {

    int numQubits = 4;
    int numSteps = 500; 
    double stepSize = 0.0001;
    std::string outFileA = "output/Bures.out";
    std::string outFileB = "output/targetCoeff.out";
    double upperBound = 0.005; // biggest noise can get... kinda
                               // works between 0.001 and 0.01
    int opt = 0;
    while ( (opt = getopt( argc, argv, "d:n:o:q:s:u:" )) != -1 ) {
        switch ( opt ) {
        case 'd':
            outFileB = optarg;
            break;
        case 'n':
            numSteps = atoi(optarg);
            break;
        case 'o':
            outFileA = optarg;
            break;
        case 'q':
            numQubits = atoi(optarg);
            break;
        case 's':
            stepSize = atof(optarg);
            break;
        case 'u':
            upperBound = atof(optarg);
            break;
        default:
            usage();
        }
    }

    const int dimension = int( pow( 2, numQubits ) );

    Uniform<double> uniformGenerator;
    //uniformGenerator.seed( static_cast<unsigned int>( time(0) ) );

    // outputfile stuff
    char fileAppend[5 + sizeof(int) + 2*sizeof(double)] = "";
    sprintf( fileAppend, "-%d-n%f-s%f", numQubits, upperBound, stepSize );
    outFileA += fileAppend;
    outFileB += fileAppend;
    std::ofstream outFileStreamA( outFileA.c_str() );
    std::ofstream outFileStreamB( outFileB.c_str() );
    if ( !outFileStreamA || !outFileStreamB ) {
        std::cerr << "Oops!" << std::endl;
        exit(1);
    }

    std::cout << "Bures distance -v- time to " 
         <<  outFileA << std::endl;
    std::cout << "target state prob -v- time to " 
         <<  outFileB << std::endl;
    std::cout << "numQubits = " << numQubits << std::endl;
    std::cout << "numSteps = " << numSteps << std::endl;
    std::cout << "step size = " << stepSize << std::endl;
    std::cout << "upper bound = " << upperBound << std::endl;


    // initial conditions
    double t = 0.0;
    State* rho1 = new PureState(dimension);
    rho1->init();
    State* rho2 = new MixedState(dimension);
    rho2->init();

    try{
#ifdef TELL_ME
//        rho1->print(t);
//        rho2->print(t);
        printDiffs(outFileStreamA,t,rho1,rho2);
        printLeadingEVals(outFileStreamB,t,rho1,rho2);
#endif //TELL_ME

        int aHundredth = numSteps/100;
        for ( int i = 0; i < numSteps; i++ ){


            rho1->step( t, stepSize );
            rho2->step( t, stepSize );
            rho2->perturb( uniformGenerator, upperBound );
            t += stepSize;

            if ( 0 == i%aHundredth ) {
                //rho1->print(t);
                //rho2->print(t);
                printLeadingEVals(outFileStreamB,t,rho1,rho2);
                printDiffs(outFileStreamA,t,rho1,rho2);
            }
#ifdef TELL_ME
            showProgress(i,numSteps,numQubits);
            if ( i == numSteps - 1 ) {
//                rho1->print(t);
//                rho2->print(t);
                printDiffs(outFileStreamA,t,rho1,rho2);
                printLeadingEVals(outFileStreamB,t,rho1,rho2);
            }
//            char line[80];
//            cin.getline(line,80);
#endif //TELL_ME

        }//end of for

    }//end of try
    catch( const std::exception& ex ) {
        std::cerr << "exception " << ex.what() << std::endl;
    }

    delete rho1;
    delete rho2;

    outFileStreamA.close();
    outFileStreamB.close();

}

