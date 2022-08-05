/*

 Created by Evan Howington on 4/11/20.
 Using Dr. Mayes' "Yukawa3GenUpQuarks.cpp" and my python code as templates.  This
 research is seeking to predict neutrino masses and mixing angles from Dr. Mayes'
 work in string theory.

 This code seeks to search through numerical spaces to determine what values for certain
 free parameters within the model produce valid results. Dr. Mayes' original code calculates
 the values based off a single entry where he is seeking to fit the PMNS neutrino mixing
 parameters.  Here I am seeking to find which values fit the CKM mixing matrix for certain
 free parameters.  Then once a clear numerical space has been uncovered I will expand the
 conditional statements to include  satisfying the experimentally found CKM parameters
 and also the experimentally observed PMNS parameters.

 When conditions are met the data points are written to a csv file so further exploratory data
 analysis/science may be performed within a more user-friendly language, such as python.

 Currently, there are a lot of print statements that send results to the console/terminal/debug
 screen so that one may see what the code is producing and the number of iterations is set to 1.
 When this code is ran to search the numerical spaces the print statements will be commented out
 and the number of datasets to be created will be increased significantly.  The number of data sets
 desired can be changed by changing the value of "int setsOfData = 1;" on Line 77.


 The "eigen" Library comes from: https://spectralib.org/index.html
*/

// Pre-processor Directives
#include <iostream>
#include <random>
#include <cmath>
#include <fstream>
#include "eigen-3.3.9/Eigen/Dense"
#include "eigen-3.3.9/Eigen/Eigenvalues"
#include <chrono>
#include <thread>


using Eigen::MatrixXd;
using Eigen::Vector3d;
using Eigen::Matrix3d;
using Eigen::Matrix3f;

// Jacobi Theta Function with Wilson Lines set to Zero
double expsum(double delta, double kappa, double Tol)
{
    double Pik, DD, Value, ValueOld, ExpArg1, ExpArg2;
    int L;

    Pik = -3.141592653589793*kappa;
    DD = delta - (int)delta;
    L = 0;
    Value = exp(Pik*DD*DD);
    ValueOld = Value + 2.0*Tol;
    while (fabs(Value/ValueOld  - 1.0) > Tol){
        ValueOld = Value;
        L += 1;
        ExpArg1 = Pik*(DD + L)*(DD + L);
        ExpArg2 = Pik*(DD - L)*(DD - L);
        Value +=  exp(ExpArg1) + exp(ExpArg2);
    }

    return Value;
}

double findYukawaMatrices(double deltaQ, double deltaL, double tol)
{
    // Creating the csv file to write data to
    std::ofstream csv;
    csv.open("data.csv", std::ios::app);

    // DECLARE COUNTERS
    int small = 0;
    int good = 0;
    int large = 0;
    int setsOfData = 100000;
    int a = 0;


    // Declare variables
    double vu1, vu2, vu3, vu4, vu5, vu6, vd1, vd2, vd3, vd4, vd5, vd6;
    double Aq, Bq, Cq, Dq, Eq, Fq, kappa;

    // Declaring Variables of the upper and lower limits of mixing matrices
    Matrix3d ckmU, ckmL;

    // upper limit of CKM matrix
    ckmU(0,0) = 0.9754; ckmU(1,0) = 0.22496; ckmU(2,0) = 0.00377;
    ckmU(0,1) = 0.22482; ckmU(1,1) = 0.9749; ckmU(2,1) = 0.04290;
    ckmU(0,2) = 0.00920; ckmU(1,2) = 0.04207; ckmU(2,2) = 0.9995;

    // lower limit of CKM matrix
    ckmL(0,0) = 0.97436; ckmL(1,0) = 0.2205; ckmL(2,0) = 0.0026;
    ckmL(0,1) = 0.2203; ckmL(1,1) = 0.97348; ckmL(2,1) = 0.0318;
    ckmL(0,2) = 0.0075; ckmL(1,2) = 0.0311; ckmL(2,2) = 0.999073;


/*
################################ Quark Variable Declarations ##########################################
*/
    // Declare matrices for the yukawa up and down type quarks
    MatrixXd MatrixYukawaUpQuark(3,3), MatrixYukawaDownQuark(3,3);

    // Declare matrices for Up and Down Quark eigenvectors
    Matrix3d UpQVect, UpQVectTranspose, DownQVect;

    // Declare the CKM Matrix
    Matrix3d CKM, CKMabsolute;


/*
#################### Neutrino and Charged Lepton Variable Declarations ################################
*/
    // Declare Matrices for the Neutrinos and Charged Leptons
    MatrixXd MatrixYukawaNeutrino(3,3), MatrixYukawaChargedLepton(3,3);

    // Declare matrices for yukawa Neutrino and Charged Leptons
    Matrix3d NeutrinoVect, NeutrinoVectTranspose, LeptVect, ChargedLeptVectTranspose;

    // Declare the PMNS Matrix
    Matrix3d PMNS, PMNSabs;

    // Declare Neutrino matrices needed for calculated the PMNS
    Matrix3d NeutrinoYukawaTranspose, InvRightNeutrino, Degenerate, DegeneratePower, MajoranaMassNeutrino, MajoranaVect;
    MatrixXd MajoranaVal;

/*
#################### Random Value Generators #########################################################
*/
    // Random Seed
    std::random_device r;

    // Random value generator for Up Higgs VEVs within the given range (a,b)
    std::default_random_engine generator1(r());
    std::uniform_real_distribution<double> realDistribution1(0.0, 1.0);

    // Random value generator for Down Higgs VEVs within the given range (a,b)
    std::default_random_engine generator2(r());
    std::uniform_real_distribution<double> realDistribution2(0.0, 1.0);

    // Random value generator for Kappa within the given range (a,b)
    std::default_random_engine generator3(r());
    std::uniform_real_distribution<double> realDistribution3(0.0, 100.0);
/*
#################### Begin Loop searching for valid parameters ########################################
*/
    while (a < setsOfData)
    {
        // "a" is just a loop counter
        ++a;
        // std::cout << "\n The value of a is; " << a << "\n";

        // Give random values to Higgs VEVs up
        vu1 = realDistribution1(generator1);
        vu2 = realDistribution1(generator1);
        vu3 = realDistribution1(generator1);
        vu4 = realDistribution1(generator1);
        vu5 = realDistribution1(generator1);
        vu6 = realDistribution1(generator1);

//        vu1 = 0.0000142;
//        vu2 = 0.00002408185;
//        vu3 = 1.0;
//        vu4 = 0.000000345;
//        vu5 = 0.00404;
//        vu6 = 0.005960855;

        // Give random values to Higgs VEVs down
        vd1 = realDistribution1(generator2);
        vd2 = realDistribution1(generator2);
        vd3 = realDistribution1(generator2);
        vd4 = realDistribution1(generator2);
        vd5 = realDistribution1(generator2);
        vd6 = realDistribution1(generator2);

//        vd1 = 0.0028224;
//        vd2 = 0.045;
//        vd3 = 1.0;
//        vd4 = 0.0010105;
//        vd5 = 0.0266;
//        vd6 = 1.0;

        // Give random value to kappa
        kappa = realDistribution3(generator3);
//        kappa = 58.7;


        /*
        ###############################################################################################
        ################################ BEGIN QUARK SECTION ##########################################
        ###############################################################################################
        */

        // JACOBI THETA FUNCTIONS, FUNCTION CALL TO CREATE THE YUKAWA QUARK MATRICES
        Aq = expsum(deltaQ, kappa, tol);
        Bq = expsum(deltaQ + (1.0 / 3.0), kappa, tol);
        Cq = expsum(deltaQ - (1.0 / 3.0), kappa, tol);
        Dq = expsum(deltaQ + (1.0 / 6.0), kappa, tol);
        Eq = expsum(deltaQ + (1.0 / 2.0), kappa, tol);
        Fq = expsum(deltaQ - (1.0 / 6.0), kappa, tol);

        // Setting values for Yukawa Up Quark Elements
        MatrixYukawaUpQuark(0,0) = Aq * vu1 + Eq * vu4; MatrixYukawaUpQuark(1,0) = Bq * vu3 + Fq * vu6; MatrixYukawaUpQuark(2,0) = Cq * vu5 + Dq * vu2;
        MatrixYukawaUpQuark(0,1) = Cq * vu3 + Dq * vu6; MatrixYukawaUpQuark(1,1) = Aq * vu5 + Eq * vu2; MatrixYukawaUpQuark(2,1) = Bq * vu1 + Fq * vu4;
        MatrixYukawaUpQuark(0,2) = Bq * vu5 + Fq * vu2; MatrixYukawaUpQuark(1,2) = Cq * vu1 + Dq * vu4; MatrixYukawaUpQuark(2,2) = Aq * vu3 + Eq * vu6;
        // Setting values for Yukawa Down Quark Elements
        MatrixYukawaDownQuark(0,0) = Aq * vd1 + Eq * vd4; MatrixYukawaDownQuark(1,0) = Bq * vd3 + Fq * vd6; MatrixYukawaDownQuark(2,0) = Cq * vd5 + Dq * vd2;
        MatrixYukawaDownQuark(0,1) = Cq * vd3 + Dq * vd6; MatrixYukawaDownQuark(1,1) = Aq * vd5 + Eq * vd2; MatrixYukawaDownQuark(2,1) = Bq * vd1 + Fq * vd4;
        MatrixYukawaDownQuark(0,2) = Bq * vd5 + Fq * vd2; MatrixYukawaDownQuark(1,2) = Cq * vd1 + Dq * vd4; MatrixYukawaDownQuark(2,2) = Aq * vd3 + Eq * vd6;

        // Printing values of the Yukawa Up Quark Calculations
//        std::cout << "\nYukawa Up Quark Matrice\n" << MatrixYukawaUpQuark << std::endl;

        // Printing values of the Yukawa Down Quark Calculations
//        std::cout << "\nYukawa Down Quark Matrice\n" << MatrixYukawaDownQuark << std::endl;

        /*
         * Calling the Eigenvalue, Eigenvector solver found from Spectra mentioned at the beginning of this .cpp file
         * I denoted this one as "es1()" so I can call these same eigenvalues without have to clear them from memory.
         * When I want to find new eigenvalues I'll do so with "esN()", where N>1
         */

        Eigen::EigenSolver<MatrixXd> es1(MatrixYukawaUpQuark);
        UpQVect = es1.eigenvectors().real(); // THE ERROR COMES FROM HERE, AND IF THIS IS COMMENTED OUT THE CODE WORKS FINE IN GENERATING THE EIGENVECTORS & VALUES IN THE PRINT STATEMENTS

        // Printing the Up Quark Matrice values for the Eigenvectors, and Eigenvalues to the screen
//        std::cout << "\nThe eigenvalues of the Yukawa Up Quark Matrix are: " << std::endl << es1.eigenvalues() << std::endl;
//        std::cout << "\nThe Up Quark eigenvectors are:" << std::endl << UpQVect << std::endl;

        Eigen::EigenSolver<MatrixXd> es2(MatrixYukawaDownQuark);
        DownQVect = es2.eigenvectors().real(); // THIS WILL ALSO PRODUCE AN ERROR AS IT IS THE SAME PROBLEM FROM ABOVE

        // Printing the Up Quark Matrice values for the Eigenvectors, and Eigenvalues to the screen
//        std::cout << "\nThe eigenvalues of the Yukawa Down Quark Matrix are: " << std::endl << es2.eigenvalues() << std::endl;
//        std::cout << "\nThe Down Quark eigenvectors, V, is:" << std::endl << DownQVect << std::endl;

        UpQVectTranspose = UpQVect.transpose();
        CKM = DownQVect * UpQVectTranspose;
        CKMabsolute = CKM.cwiseAbs();
        std::cout << "\nThe absolute value of the CKM Matrix is: " << std::endl << CKMabsolute << std::endl;


        /*
        ###############################################################################################
        ##################### BEGIN Neutrino * Charged Leptons SECTION ################################
        ###############################################################################################
        */

        // Jacobi Theta Functions, Function call to create the Yukawa Neutrino & Charged Lepton Matrices
        Aq = expsum(deltaL, kappa, tol);
        Bq = expsum(deltaL + (1.0 / 3.0), kappa, tol);
        Cq = expsum(deltaL - (1.0 / 3.0), kappa, tol);
        Dq = expsum(deltaL + (1.0 / 6.0), kappa, tol);
        Eq = expsum(deltaL + (1.0 / 2.0), kappa, tol);
        Fq = expsum(deltaL - (1.0 / 6.0), kappa, tol);

        // Setting values for Yukawa Neutrino Elements
        MatrixYukawaNeutrino(0,0) = Aq * vu1 + Eq * vu4; MatrixYukawaNeutrino(1,0) = Bq * vu3 + Fq * vu6; MatrixYukawaNeutrino(2,0) = Cq * vu5 + Dq * vu2;
        MatrixYukawaNeutrino(0,1) = Cq * vu3 + Dq * vu6; MatrixYukawaNeutrino(1,1) = Aq * vu5 + Eq * vu2; MatrixYukawaNeutrino(2,1) = Bq * vu1 + Fq * vu4;
        MatrixYukawaNeutrino(0,2) = Bq * vu5 + Fq * vu2; MatrixYukawaNeutrino(1,2) = Cq * vu1 + Dq * vu4; MatrixYukawaNeutrino(2,2) = Aq * vu3 + Eq * vu6;
        // Setting values for Yukawa Charged Leptons Elements
        MatrixYukawaChargedLepton(0,0) = Aq * vd1 + Eq * vd4; MatrixYukawaChargedLepton(1,0) = Bq * vd3 + Fq * vd6; MatrixYukawaChargedLepton(2,0) = Cq * vd5 + Dq * vd2;
        MatrixYukawaChargedLepton(0,1) = Cq * vd3 + Dq * vd6; MatrixYukawaChargedLepton(1,1) = Aq * vd5 + Eq * vd2; MatrixYukawaChargedLepton(2,1) = Bq * vd1 + Fq * vd4;
        MatrixYukawaChargedLepton(0,2) = Bq * vd5 + Fq * vd2; MatrixYukawaChargedLepton(1,2) = Cq * vd1 + Dq * vd4; MatrixYukawaChargedLepton(2,2) = Aq * vd3 + Eq * vd6;

        // Printing values of the Yukawa Neutrino Calculations
//        std::cout << "\nYukawa Neutrino Matrice\n" << MatrixYukawaNeutrino << std::endl;

        // Printing values of the Yukawa Charged Leptons Calculations
//        std::cout << "\nYukawa Charged Lepton Matrice\n" << MatrixYukawaChargedLepton << std::endl;

        // Eigenvalues and Eigenvectors for the Yukawa Neutrino Matrice
        Eigen::EigenSolver<MatrixXd> es3(MatrixYukawaNeutrino);
//        NeutrinoVect = es3.eigenvectors().real();

        // Printing the Neutrino values for the Eigenvectors, and Eigenvalues to the screen
//        std::cout << "\nThe eigenvalues of the Yukawa Neutrino Matrix are: " << std::endl << es3.eigenvalues() << std::endl;
//        std::cout << "\nThe Yukawa Neutrino eigenvectors are:" << std::endl << NeutrinoVect << std::endl;

        // Eigenvalues and Eigenvectors for the Yukawa Charged Lepton Matrice
        Eigen::EigenSolver<MatrixXd> es4(MatrixYukawaChargedLepton);
        LeptVect = es4.eigenvectors().real();
        ChargedLeptVectTranspose = LeptVect.transpose();

        // Printing the Up Quark Matrice values for the Eigenvectors, and Eigenvalues to the screen
//        std::cout << "\nThe eigenvalues of the Yukawa Charged Leptons Matrix are: " << std::endl << es4.eigenvalues() << std::endl;
//        std::cout << "\nThe Yukawa Charged Leptons eigenvectors, V, is:" << std::endl << LeptVect << std::endl;

        // Setting Degenerate Values for the Elements
        Degenerate(0,0) = 0.9990; Degenerate(1,0) = 0; Degenerate(2,0) = 0;
        Degenerate(0,1) = 0; Degenerate(1,1) = 0.99939; Degenerate(2,1) =0;
        Degenerate(0,2) = 0; Degenerate(1,2) = 0; Degenerate(2,2) = 1.0;

        // Multiplying the Degenerate Matrice by a chosen power for the seesaw mechanism
        DegeneratePower = std::pow(1, -19) * Degenerate;

        // assigning the transpose of the Yukawa Neutrino matrix to use in finding the Majorana Mass matrix
        NeutrinoYukawaTranspose = MatrixYukawaNeutrino.transpose();

        // Calculating the Majorana Neutrino Mass Matrix with the Yukawa Neutrino matrices multiplied by the mass of the top quark of 173.4 GeV converted to eV
        MajoranaMassNeutrino = (-1) * std::pow(146, 9) * MatrixYukawaNeutrino * DegeneratePower * std::pow(146, 9) * NeutrinoYukawaTranspose;

        // Printing values of the Majorana Neutrino Mass Matrice Calculations
//        std::cout << "\nMajorana Neutrino Matrice\n" << MajoranaMassNeutrino << std::endl;

        // Eigenvalues and Eigenvectors for the Majorana Neutrino Matrice
        Eigen::EigenSolver<MatrixXd> es5(MajoranaMassNeutrino);
        MajoranaVect = es5.eigenvectors().real();
        MajoranaVal = es5.eigenvalues().real();

        // Printing values of the Majorana Neutrino Mass Matrice Calculations
//        std::cout << "\nMajorana Eigenvector Matrice\n" << MajoranaVect << std::endl;

        // Computing the PMNS Neutrino Mixing Matrice
        PMNS = ChargedLeptVectTranspose * MajoranaVect;
        PMNSabs = PMNS.cwiseAbs();

        // Printing values of the Majorana Neutrino Mass Matrice Calculations
        std::cout << "\nAbsolute value of the PMNS Neutrino Mixing Matrice\n" << PMNSabs << std::endl;


        // Printing the Majorana Eigenvalues, aka Neutrino masses
        std::cout << "\nThe eigenvalues of the Majorana Matrix are: " << std::endl << es5.eigenvalues() << std::endl;

        if (ckmL(0,0) > CKMabsolute(0,0) || ckmL(0,1) > CKMabsolute(0,1) ||
            ckmL(0,2) > CKMabsolute(0,2) || ckmL(1,0) > CKMabsolute(1,0) ||
            ckmL(1,1) > CKMabsolute(1,1) || ckmL(1,2) > CKMabsolute(1,2) ||
            ckmL(2,0) > CKMabsolute(2,0) || ckmL(2,1) > CKMabsolute(2,1) ||
            ckmL(2,2) > CKMabsolute(2,2))
        {
            ++small;
            std::cout << small << " are too small\n";
            std::cout << large << " are too large\n";
            std::cout << good << " are good\n";
            csv.open("data.csv", std::ios::app);
            csv << a << "," << kappa << ", small, "<< vu1 << ","  << vu2 << ","  << vu3 << ","  << vu4 << ","  << vu5
                << ","  << vu6 << ","  << vd1 << ","  << vd2 << ","  << vd3 << ","  << vd4 << ","  << vd5 << ","  << vd6
                << ","  << CKMabsolute(0,0) << "," << CKMabsolute(0,1) << "," << CKMabsolute(0,2)
                << "," << CKMabsolute(1,0) << "," << CKMabsolute(1,1) << "," << CKMabsolute(1,2)
                << "," << CKMabsolute(2,0) << "," << CKMabsolute(2,1) << "," << CKMabsolute(2,2)
                << "," << MajoranaVal(0,0) << "," << MajoranaVal(1,0) << "," << MajoranaVal(2,0)
                << "," << PMNSabs(0,0) << "," << PMNSabs(0,1) << "," << PMNSabs(0,2) << ","
                << PMNSabs(1,0) << "," << PMNSabs(1,1) << "," << PMNSabs(1,2) << ","
                << PMNSabs(2,0) << "," << PMNSabs(2,1) << "," << PMNSabs(2,2) << std::endl;

        }

        else if (CKMabsolute(0,0) > ckmU(0,0) || CKMabsolute(0,1) > ckmU(0,1) ||
                CKMabsolute(0,2) > ckmU(0,2) || CKMabsolute(1,0) > ckmU(1,0) ||
                CKMabsolute(1,1) > ckmU(1,1) || CKMabsolute(1,2) > ckmU(1,2) ||
                CKMabsolute(2,0) > ckmU(2,0) || CKMabsolute(2,1) > ckmU(2,1) ||
            CKMabsolute(2,2) > ckmU(2,2))
        {
            ++large;
            std::cout << small << " are too small\n";
            std::cout << large << " are too large\n";
            std::cout << good << " are good\n";
            csv.open("data.csv", std::ios::app);
            csv << a << "," << kappa << ", small, "<< vu1 << ","  << vu2 << ","  << vu3 << ","  << vu4 << ","  << vu5
                << ","  << vu6 << ","  << vd1 << ","  << vd2 << ","  << vd3 << ","  << vd4 << ","  << vd5 << ","  << vd6
                << ","  << CKMabsolute(0,0) << "," << CKMabsolute(0,1) << "," << CKMabsolute(0,2)
                << "," << CKMabsolute(1,0) << "," << CKMabsolute(1,1) << "," << CKMabsolute(1,2)
                << "," << CKMabsolute(2,0) << "," << CKMabsolute(2,1) << "," << CKMabsolute(2,2)
                << "," << MajoranaVal(0,0) << "," << MajoranaVal(1,0) << "," << MajoranaVal(2,0)
                << "," << PMNSabs(0,0) << "," << PMNSabs(0,1) << "," << PMNSabs(0,2) << ","
                << PMNSabs(1,0) << "," << PMNSabs(1,1) << "," << PMNSabs(1,2) << ","
                << PMNSabs(2,0) << "," << PMNSabs(2,1) << "," << PMNSabs(2,2) << std::endl;
        }

        else
        {
            ++good;
            std::cout << small << " are too small\n";
            std::cout << large << " are too large\n";
            std::cout << good << " are good\n";
            csv.open("data.csv", std::ios::app);
            csv << a << "," << kappa << ", small, "<< vu1 << ","  << vu2 << ","  << vu3 << ","  << vu4 << ","  << vu5
                << ","  << vu6 << ","  << vd1 << ","  << vd2 << ","  << vd3 << ","  << vd4 << ","  << vd5 << ","  << vd6
                << ","  << CKMabsolute(0,0) << "," << CKMabsolute(0,1) << "," << CKMabsolute(0,2)
                << "," << CKMabsolute(1,0) << "," << CKMabsolute(1,1) << "," << CKMabsolute(1,2)
                << "," << CKMabsolute(2,0) << "," << CKMabsolute(2,1) << "," << CKMabsolute(2,2)
                << "," << MajoranaVal(0,0) << "," << MajoranaVal(1,0) << "," << MajoranaVal(2,0)
                << "," << PMNSabs(0,0) << "," << PMNSabs(0,1) << "," << PMNSabs(0,2) << ","
                << PMNSabs(1,0) << "," << PMNSabs(1,1) << "," << PMNSabs(1,2) << ","
                << PMNSabs(2,0) << "," << PMNSabs(2,1) << "," << PMNSabs(2,2) << std::endl;
        }

        // Keeping track of how many loops, displayed when the program is executed
//        std::cout<< "\n You have completed: " << a << " loops\n\n";

        csv.close();

    }
    // 5 in the below printout represents the number of threads used.  NEED: set up a function to make the number of threads a max of the hardware
    std::cout<< "\nYou have created: " << 36 * setsOfData * 32 << " data points\n\n";
    return 0;
}

/*
 * threading() below this comment needs to be live if using threading() inside int main()
 * */
double threading(double delta, double kappa, double tol)
{
    std::thread t1(findYukawaMatrices, delta, kappa, tol);
    std::thread t2(findYukawaMatrices, delta, kappa, tol);
    std::thread t3(findYukawaMatrices, delta, kappa, tol);
    std::thread t4(findYukawaMatrices, delta, kappa, tol);
    std::thread t5(findYukawaMatrices, delta, kappa, tol);
    std::thread t6(findYukawaMatrices, delta, kappa, tol);
    std::thread t7(findYukawaMatrices, delta, kappa, tol);
    std::thread t8(findYukawaMatrices, delta, kappa, tol);
    std::thread t9(findYukawaMatrices, delta, kappa, tol);
    std::thread t10(findYukawaMatrices, delta, kappa, tol);
    std::thread t11(findYukawaMatrices, delta, kappa, tol);
    std::thread t12(findYukawaMatrices, delta, kappa, tol);
    std::thread t13(findYukawaMatrices, delta, kappa, tol);
    std::thread t14(findYukawaMatrices, delta, kappa, tol);
    std::thread t15(findYukawaMatrices, delta, kappa, tol);
    std::thread t16(findYukawaMatrices, delta, kappa, tol);
    std::thread t17(findYukawaMatrices, delta, kappa, tol);
    std::thread t18(findYukawaMatrices, delta, kappa, tol);
    std::thread t19(findYukawaMatrices, delta, kappa, tol);
    std::thread t20(findYukawaMatrices, delta, kappa, tol);
    std::thread t21(findYukawaMatrices, delta, kappa, tol);
    std::thread t22(findYukawaMatrices, delta, kappa, tol);
    std::thread t23(findYukawaMatrices, delta, kappa, tol);
    std::thread t24(findYukawaMatrices, delta, kappa, tol);
    std::thread t25(findYukawaMatrices, delta, kappa, tol);
    std::thread t26(findYukawaMatrices, delta, kappa, tol);
    std::thread t27(findYukawaMatrices, delta, kappa, tol);
    std::thread t28(findYukawaMatrices, delta, kappa, tol);
    std::thread t29(findYukawaMatrices, delta, kappa, tol);
    std::thread t30(findYukawaMatrices, delta, kappa, tol);
    std::thread t31(findYukawaMatrices, delta, kappa, tol);
    std::thread t32(findYukawaMatrices, delta, kappa, tol);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();
    t11.join();
    t12.join();
    t13.join();
    t14.join();
    t15.join();
    t16.join();
    t17.join();
    t18.join();
    t19.join();
    t20.join();
    t21.join();
    t22.join();
    t23.join();
    t24.join();
    t25.join();
    t26.join();
    t27.join();
    t28.join();
    t29.join();
    t30.join();
    t31.join();
    t32.join();

    return 0;
}

int main()
{
    auto start = std::chrono::steady_clock::now();

    std::ofstream csv;
    csv.open("data.csv", std::ios::app);
    csv << "loopRun, kappa, LargeGoodSmall, vu1, vu2, vu3, vu4, vu5, vu6, vd1, vd2, vd3, vd4, vd5, vd6, CKMabsolute(11), "
           "CKMabsolute(12), CKMabsolute(13), CKMabsolute(21), CKMabsolute(22), CKMabsolute(23), CKMabsolute(31), CKMabsolute(32), "
           "CKMabsolute(33), MajoranaEigenVal 1, MajoranaEigenVal 2, MajoranaEigenVal 3, PMNS(11), PMNS(12), PMNS(13), "
           "PMNS(21), PMNS(22), PMNS(23), PMNS(31), PMNS(32), PMNS(33)" << std::endl;
    csv.close();

    threading(0.0, 0.5, 0.0000001); // Creates 32 threads

//    findYukawaMatrices(0.0, 0.5, 0.0000001);


    auto end = std::chrono::steady_clock::now();

    std::cout << "Elapsed time in seconds : " << std::chrono::duration_cast < std::chrono::seconds>(end - start).count()<< " sec\n\n";

    return 0;

}


