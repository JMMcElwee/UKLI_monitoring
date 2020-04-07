/* ---------------- totQ.cc ---------------- *
 * This will extract a variety of variables  * 
 * from the diffuser root files for the UK   *
 * light injection system.                   *
 *                                           *
 * SOFTWARE REQUIRED:                        *
 * ---> ROOT                                 *
 * ---> position.h                           *
 *                                           *
 *                jmmcelwee1@sheffield.ac.uk *
 * ------------------------- J. McElwee ---- */

#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TVector3.h"
#include "position.h"

int main(int argc, char const *argv[]){

  std::string injPos = "B5";
  TVector3 inj(1490.73, 768.14, injector(injPos));

  if (argc != 2){
    std::cout << "\033[1;31m[ERROR]\033[0m Incorrect number of arguments." << std::endl;
    return 0;
  }else{
    std::cout << "\033[1;34m[INFO]\033[0m Reading in ROOT file:" << std::endl;
  }

  TFile infile(argv[1],"READ");
  TTree *intree = 0;
  infile.GetObject("tqtree", intree);
  infile.ls();
  std::cout << "\033[1;34m[INFO]\033[0m Example event:" << std::endl;
  intree->Show(0);

  Int_t year = 0;
  Int_t month = 0;
  Int_t day = 0;
  Int_t hour = 0;
  Int_t minute = 0;
  Int_t second = 0;
  Int_t run = 0;
  Int_t subrun = 0;
  Int_t nev = 0;
  std::vector<int> *ihit_vec = 0;
  std::vector<int> *cable_vec = 0;
  std::vector<float> *charge_vec = 0;
  std::vector<double> *time_vec = 0;
  std::vector<double> *pmtx_vec = 0;
  std::vector<double> *pmty_vec = 0;
  std::vector<double> *pmtz_vec = 0;
  
  intree->SetBranchAddress("year", &year);
  intree->SetBranchAddress("month", &month);
  intree->SetBranchAddress("day", &day);
  intree->SetBranchAddress("hour", &hour);
  intree->SetBranchAddress("minute", &minute);
  intree->SetBranchAddress("second", &second);
  intree->SetBranchAddress("run", &run);
  intree->SetBranchAddress("subrun", &subrun);
  intree->SetBranchAddress("nev", &nev);
  intree->SetBranchAddress("ihit_vec", &ihit_vec);
  intree->SetBranchAddress("cable_vec", &cable_vec);
  intree->SetBranchAddress("charge_vec", &charge_vec);
  intree->SetBranchAddress("time_vec", &time_vec);
  intree->SetBranchAddress("pmtx_vec", &pmtx_vec);
  intree->SetBranchAddress("pmty_vec", &pmty_vec);
  intree->SetBranchAddress("pmtz_vec", &pmtz_vec);


  // Create and open file for pushing data to
  std::ofstream dataFile;
  dataFile.open("data.txt");
  std::cout << "\033[1;34m[INFO]\033[0m Creating file data.txt." << std::endl;
  dataFile << "run subrun month day hour minute second nev_tot nev_spot totQ spotQ\n";


  // Main Event loop over TTree
  for (Int_t evnt =0; evnt < intree->GetEntries(); ++evnt){

    intree->GetEntry(evnt);
    if ((evnt + 1) % 5000 == 0){
      std::cout << "\033[1;34m[INFO]\033[0m Processing event number: " << evnt + 1 << std::endl;
    }
     

    float nev_spot = 0;
    TVector3 pmt;
    float spotQ = 0;
    for (int count = 0; count < ihit_vec->size(); ++count){
      pmt.SetXYZ(pmtx_vec->at(count),pmty_vec->at(count),pmtz_vec->at(count));
      TVector3 a = pmt - inj;
      TVector3 b = -inj;

      float theta = a.Angle(b) * 180 / M_PI; 
      if (theta < 40.0){
      	nev_spot += 1;
	spotQ += charge_vec->at(count);
      }
      
    }


    float totQ = std::accumulate(charge_vec->begin(), charge_vec->end(), 0.0);
    float nev = ihit_vec->size();

    dataFile << run << " " << subrun << " " << year << " " << month << " " << day << " "
             << hour << " " << minute << " " << second << " " << nev << " " << nev_spot 
	     << " " << totQ << " " << spotQ << "\n";
  
  }

  std::cout << "\033[1;34m[INFO]\033[0m Closing data.txt." << std::endl;
  dataFile.close();

  return 0;
}
