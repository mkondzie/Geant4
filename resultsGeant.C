#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include <fstream>
using namespace std;

void resultsGeant(){
  TFile *f=new TFile("output.root"); // opens the root file
  TTree *tr=(TTree*)f->Get("Scattering"); // creates the TTree object
  tr->Scan(); // prints the content on the screen

  double a,b,c; // create variables of the same type as the branches you want to access

  tr->SetBranchAddress("fTheta",&a); // for all the TTree branches you need this
  tr->SetBranchAddress("fpreMomentum",&b);
  tr->SetBranchAddress("fpostMomentum",&c);

  ofstream myfile;
  myfile.open ("example.txt");
  myfile << "fTheta fpreMomentum fpostMomentum\n";

  for (int i=0;i<tr->GetEntries();i++){
    // loop over the tree
    tr->GetEntry(i);
    cout << a << " " << b << " "<< c << endl; //print to the screen
    myfile << a << " " << b << " "<< c<<"\n"; //write to file
  }
  myfile.close();
}