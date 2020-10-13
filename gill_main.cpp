// to compile: c++ gill_main.cpp gill_functions.cpp cokus3.c -o gillespie-ses -lgsl -lgslcblas -lm -Wall -Weffc++

#include "gill_functions.h"

#include <sodium.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iostream> //Allows cin/cout
#include <sstream>
#include <stdlib.h> //Allows DOS Commands (I only use "CLS" to clear the screen)
#include <iterator>

#include <math.h>
#include <chrono>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

using namespace std;

extern double ranMT(void);
extern void seedMT(unsigned long int);
extern void seedMT2(void);

#define PI 3.14159265358979323846
#define LOAD_CONF 0

///////////////////////////////////////////////////////////////////////////////
// MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////////

// time at beginning
auto start = chrono::high_resolution_clock::now();
auto start2 = chrono::high_resolution_clock::now();

int main(int argc, const char * argv[]){

  // seeding the random double generator: used for gillespie
  seedMT2();
  // creating the random integer generator and seeding it
  gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);
  gsl_rng_set(r, 1425638);

  ///////////////////////////////////////////////////////////////////////////////
  // PARAMETER DECLARATION
  ///////////////////////////////////////////////////////////////////////////////

  int n;  // lenght of the sides of the square landscape: number of cells=n*n
  int SimTime; // total simulation time
  double dtp; // timestep for population dynamics
  double a0; //number of agricultural patches at beggining
  double cg0,r0,y0; // per capita consumption, population growth rate and baseline agricultural yield
  double a; // likelihood of restoring/converting
  double w; // agricultural clustering parameter
  double m; // maintenance cost of a cropped patch
  double g; // growth coefficient of action probability in function of consumption deficit
  double Ta; // mean abandonment time
  double phi; // relative contribution of natural land to agriculture
  double Tr,Td; // mean recovery and degradation time for max and min exposure to nature
  double dtsave; // timestep for saving data

  ///////////////////////////////////////////////////////////////////////////////
  // IMPORT PARAMETER VALUES
  ///////////////////////////////////////////////////////////////////////////////

  if (argc>1) {
        char * pEnd;

        SimTime = atoi(argv[1]);
        dtp = strtod(argv[2], &pEnd);
        n = atoi(argv[3]);
        a0 = strtod(argv[4],&pEnd);
        cg0 = strtod(argv[5], &pEnd);
        r0 = strtod(argv[6], &pEnd);
        y0 = strtod(argv[7], &pEnd);
        a = strtod(argv[8], &pEnd);
        w = strtod(argv[9], &pEnd);
        m = strtod(argv[10], &pEnd);
        g = strtod(argv[11], &pEnd);
        Ta = strtod(argv[12], &pEnd);
        phi = strtod(argv[13], &pEnd);
        Tr = strtod(argv[14], &pEnd);
        Td = strtod(argv[15], &pEnd);
        dtsave = strtod(argv[16], &pEnd);
  }

  /////////////////////////////////////////////////////////////////////////////
  // CREATION OF DATA FILES
  /////////////////////////////////////////////////////////////////////////////

  char filename[200];
  if(argc>1){

              strcpy(filename,"_T_"); strcat(filename, argv[1]);
              strcat(filename,"_dtp_"); strcat(filename, argv[2]);
              strcat(filename,"_n_"); strcat(filename, argv[3]);
              strcat(filename,"_a0_"); strcat(filename, argv[4]);
              strcat(filename,"_cg0_"); strcat(filename, argv[5]);
              strcat(filename,"_r0_"); strcat(filename, argv[6]);
              strcat(filename,"_y0_"); strcat(filename, argv[7]);
              strcat(filename,"_a_"); strcat(filename, argv[8]);
              strcat(filename,"_w_"); strcat(filename, argv[9]);
              strcat(filename,"_m_"); strcat(filename, argv[10]);
              strcat(filename,"_g_"); strcat(filename, argv[11]);
              strcat(filename,"_Ta_"); strcat(filename, argv[12]);
              strcat(filename,"_phi_"); strcat(filename, argv[13]);
              strcat(filename,"_Tr_"); strcat(filename, argv[14]);
              strcat(filename,"_Td_"); strcat(filename, argv[15]);
              strcat(filename,"_dtsave_"); strcat(filename, argv[16]);

              strcat(filename,".dat");
  }

  char filename_POPU[200];
  strcpy(filename_POPU,"DATA_POPU"); strcat(filename_POPU,filename);
  ofstream tofile_popu(filename_POPU);
  tofile_popu.precision(5);
  tofile_popu.setf(ios::scientific,ios::floatfield);

  char filename_LAND[200];
  strcpy(filename_LAND,"DATA_LAND"); strcat(filename_LAND,filename);
  ofstream tofile_land(filename_LAND);
  tofile_land.precision(5);
  tofile_land.setf(ios::scientific,ios::floatfield);

  char filename_EVNT[200];
  strcpy(filename_EVNT,"DATA_EVNT"); strcat(filename_EVNT,filename);
  ofstream tofile_evnt(filename_EVNT);
  tofile_evnt.precision(5);
  tofile_evnt.setf(ios::scientific,ios::floatfield);

  char filename_CLUS[200];
  strcpy(filename_CLUS,"DATA_CLUS"); strcat(filename_CLUS,filename);
  ofstream tofile_clus(filename_CLUS);
  tofile_clus.precision(5);
  tofile_clus.setf(ios::scientific,ios::floatfield);

  char filename_CONF[200];
  strcpy(filename_CONF,"DATA_CONF"); strcat(filename_CONF,filename);
  ofstream tofile_conf(filename_CONF);
  tofile_conf.precision(5);
  tofile_conf.setf(ios::scientific,ios::floatfield);

  /////////////////////////////////////////////////////////////////////////////
  // VARIABLE DECLARATION AND INITIALISATION
  /////////////////////////////////////////////////////////////////////////////

  double t=0;
  double t_save=0;
  double dtg;
  double dt=dtp;
  double x_rand;
  unsigned int reaction,patch;
  unsigned int i,j;
  double total_agricultural_production;
  double consumption_deficit;
  double population;
  // vector containing the landscape state
  vector<unsigned int> landscape;
  // vector containing the production of each patch
  vector<double> agricultural_production;
  // vector to store the number of events of each kind
  vector<unsigned int> count_events={0,0,0,0,0};
  // vector containing the natural connected components information
  vector<vector<int>> natural_components;
  // vector containing the event's propensities
  vector<double> propensity_vector;

  if (LOAD_CONF==1){
    cout << "Starting from conf file \n";
    ifstream conf_file("DATA_CONF_T_2000_dtp_0.1_n_40_p0_5_cg0_1_r0_1_y0_5_a_0.45_w_0_m_1_g_1_l_0.1_Ta_1_phi_3_Tr_1.5_Td_50_dtsave_1.dat");
    if(conf_file.is_open()) {

      // first extract the time and population
      if (!(conf_file >> t >> population)){
        cout << "Error: gill_main.cpp: time and population could not be loaded from CONF file. \n";
      }
      SimTime+=t;
      // extracting by token moves forward the pointer in the file
      // now extract the landscape
      unsigned int state;
      i=0;
      while(conf_file >> state){
        landscape.push_back(state);
        i+=1;
      }
    }
  }
  else{
    initializeLandscape(n,a0,r,landscape);
    initializeProduction(n,y0,phi,landscape,agricultural_production);
    population=initializePopulation(cg0,agricultural_production);
  }
  /////////////////////////////////////////////////////////////////////////////
  // BEGIN OF SIMULATION
  /////////////////////////////////////////////////////////////////////////////

  /*
  1- get all the natural connected components
  2- use it to calculate the agricultural production
  3- use the agricultural production to calculate the consumption deficit
  :: we now have all the information needed to estimate the probability
  per unit time of each possible stochastic event::
  4- calculate the propensity vector containing the probabilites per unit time
  5- calculate the time until next reaction dtg
  6- compare the time until next reaction dtg with the time-step dt for
  population dynamics. If dtg>dt then population grows before any event, else
  there is a transition in the landscape.
  7- save the data and go back to 1.
  */
  j=0;
  // entering the time loop
  while(t<SimTime){

    /*
    if (t>SimTime/5*j){
      auto stop1 = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::minutes>(stop1 - start);
      cout << "Simulation progress " << (int)t << " out of " << SimTime << " in " << duration.count() << "minutes" << "\n";
      j+=1;
    }*/
    // identifying all the natural connected components
    getNaturalCluster(n, landscape, natural_components);

    // calculating the agricultural production
    getAgriculturalProduction(n,y0,phi,landscape,natural_components,agricultural_production);

    // calculating the consumption deficit
    total_agricultural_production=0;
    for(j=0; j<agricultural_production.size(); ++j){
      total_agricultural_production+=agricultural_production[j];
    }
    consumption_deficit = population*cg0 - total_agricultural_production;

    // calculating the propensity vector
    getPropensityVector(n, Tr, Td, w, a, g, m, Ta,consumption_deficit, landscape, natural_components, agricultural_production, propensity_vector);

    // calculating the time until next reaction
    dtg=-1/propensity_vector.back()*log(ranMT());

    // checking whether population or the landscape changes
    if (dtg>dt && population>0){
      // update the population value
      population=RungeKutta4(r0,cg0,dtp,population,total_agricultural_production);
      // update the time and the timestep for population
      t+=dt;
      dt=dtp;
    }
    else{
      // compute random number to select next reaction
      x_rand = ranMT()*propensity_vector.back();
      // traverse the propensity vector and stop once reaching the selceted cell
      i=0;
      while(x_rand>propensity_vector[i]){
        i++;
      }
      // calculate the corresponding reaction and patch from the selected index i
      reaction=(int)i/(n*n); //result from euclidian division
      patch=i%(n*n); // remainder from euclidian division

      // transform the landscape according to reaction and patch
      if (reaction==0){landscape[patch]=0;count_events[0]+=1;}
      else if(reaction==1) {landscape[patch]=2;count_events[1]+=1;}
      else if(reaction==2) {landscape[patch]=1;count_events[2]+=1;}
      else if(reaction==3) {landscape[patch]=0;count_events[3]+=1;}
      else if(reaction==4) {landscape[patch]=2;count_events[4]+=1;}
      else {cout << "Error: gill_main.cpp this reaction does not exist.";}

      // update the time and timestep for population
      t+=dtg;
      dt-=dtg;
    }

    // save the data
    if(t>=t_save){

      tofile_popu << t << " " << population << "\n";
      tofile_land << t << " ";
      tofile_evnt << t << " ";
      tofile_clus << t << "\n";

      for(i=0 ; i<landscape.size() ; i++){
        tofile_land << landscape[i] << " ";
      }
      for(i=0 ; i<count_events.size() ; i++){
        tofile_evnt << count_events[i] << " ";
      }
      for(i=0 ; i<natural_components.size() ; i++){
        tofile_clus << natural_components[i][0] << " " << natural_components[i][1] << "\n";
      }

      tofile_land << "\n";
      tofile_evnt << "\n";

      t_save+=dtsave;
    }
  }

  // saving CONF file to re start other simulations from this point
  tofile_conf << t << " " << population;
  for(i=0 ; i<landscape.size() ; i++){
    tofile_conf << " " << landscape[i];
  }
  tofile_conf << "\n";

  /* //print landscape to check
  for(i=0  ; i<n ; i++)
  {
    for(j=0 ; j<n ; j++)
    {
      cout << landscape[j+i*n] << " ";
    }
    cout << "\n";
  }
  for(i=0 ; i<natural_components.size() ; i++)
  {
    cout << "patch " << natural_components[i][0] << " is in cluster " << natural_components[i][1] <<  "\n";
    cout << "state of patch " << natural_components[i][0] << " is " << landscape[natural_components[i][0]] << "\n";
  }
  for(i=0  ; i<landscape.size() ; i++)
  {
    cout << "patch " << i << " is in state " << landscape[i] << "\n";
  }*/
  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::minutes>(stop - start);
  cout << "total execution time " << duration.count() << endl;
  return 0;
}
