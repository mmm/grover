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
    cout << "Usage: stepper [-q num-qubits] [-n num-steps]" 
         << endl;
    exit(1);
}

int main( int argc, char* argv[] ) {

    // some setup

    //const int numSteps = 250; 
    //double stepSize = 0.0002;

    //const int numSteps = 500; 
    //double stepSize = 0.0001;

    //const int numSteps = 1000; 
    //double stepSize = 0.00005;

    

    const int numSteps = 1000; 
    double stepSize = 0.0001;






    Uniform<double> uniformGenerator;
    //uniformGenerator.seed( static_cast<unsigned int>( time(0) ) );

    //const double upperBound = 0.0001; // biggest noise can get(???)
    //const double upperBound = 0.001; // biggest noise can get(???)
    const double upperBound = 0.01; // biggest noise can get(???)

    int opt,
        numQubits = 4;
    string outFile = "output/stepper.out";
    while ( (opt = getopt( argc, argv, "n:o:q:" )) != -1 ) {
        switch ( opt ) {
        case 'n':
            //const_cast<int>(numSteps) = optarg;
            cout << "numSteps = " << optarg << endl;
            break;
        case 'o':
            outFile = optarg;
            cout << "outFile = " << optarg << endl;
            break;
        case 'q':
            numQubits = atoi(optarg);
            cout << "numQubits = " << optarg << endl;
            break;
        default:
            usage();
        }
    }

    const int dimension = int( pow( 2, numQubits ) );

    // outputfile stuff
    char fileBase[2 + sizeof(int) + sizeof(double)] = "";
    sprintf( fileBase, "-%d-n%f-s%f", numQubits, upperBound, stepSize );
    outFile += fileBase;
    cout << "outFile = " << outFile << endl;
    ofstream outFileStream( outFile.c_str() );
    if ( !outFileStream ) {
        cerr << "Oops!" << endl;
        exit(1);
    }


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
        printDiffs(outFileStream,t,rho1,rho2);
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
                //printLeadingEVals(outFileStream,t,rho1,rho2);
                printDiffs(outFileStream,t,rho1,rho2);
            }
#ifdef TELL_ME
            showProgress(i,numSteps,numQubits);
            if ( i == numSteps - 1 ) {
//                rho1->print(t);
//                rho2->print(t);
                printDiffs(outFileStream,t,rho1,rho2);
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

    outFileStream.close();

}

