//
#include <string>
#include <fstream> 
#include <unistd.h> // getopt
#include <cmath> // pow
#include <time.h> // time

#include "PureState.h"
#include "MixedState.h"
#include "display.h"


void usage( void ) {
    cout << "Usage: stepper [-d prob-datafile] [-n num-steps] [-o bures-datafile] "
         << "[-q num-qubits] [-s step-size] [-u noise-threshold] " 
         << endl;
    exit(1);
}

int main( int argc, char* argv[] ) {


    int numSteps = 500; 
    double stepSize = 0.0001;

    //double upperBound = 0.001; // biggest noise can get(???)
    //double upperBound = 0.0025; // biggest noise can get(???)
    double upperBound = 0.005; // biggest noise can get(???)
    //double upperBound = 0.0075; // biggest noise can get(???)
    //double upperBound = 0.01; // biggest noise can get(???)

    int opt = 0;
    int numQubits = 4;
    string outFileA = "output/Bures.out";
    string outFileB = "output/targetCoeff.out";
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
    char fileAppend[2 + sizeof(int) + sizeof(double)] = "";
    sprintf( fileAppend, "-%d-n%f-s%f", numQubits, upperBound, stepSize );
    outFileA += fileAppend;
    outFileB += fileAppend;
    ofstream outFileStreamA( outFileA.c_str() );
    ofstream outFileStreamB( outFileB.c_str() );
    if ( !outFileStreamA || !outFileStreamB ) {
        cerr << "Oops!" << endl;
        exit(1);
    }

    cout << "Bures distance -v- time to " 
         <<  outFileA << endl;
    cout << "target state prob -v- time to " 
         <<  outFileB << endl;
    cout << "numQubits = " << numQubits << endl;
    cout << "numSteps = " << numSteps << endl;
    cout << "step size = " << stepSize << endl;
    cout << "upper bound = " << upperBound << endl;


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
    catch( const exception& ex ) {
        cerr << "exception " << ex.what() << endl;
    }

    delete rho1;
    delete rho2;

    outFileStreamA.close();
    outFileStreamB.close();

}

