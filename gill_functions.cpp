#include "gill_functions.h"

#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <math.h>
#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>


using namespace std;

/*
1-Helper functions
2-Calculation of Ecosystem Service provision
3-Calculation of events' propensities
4-Initialization functions
5-ODEs and solver
*/


///////////////////////////////////////////////////////////////////////////////
// 1- Helper functions:
//       - getNeighbours
//       - getNeighboursState
///////////////////////////////////////////////////////////////////////////////

void getNeighbours(vector<unsigned int> &neighboursList, unsigned int i, unsigned int n)
{
  /*
  changes the vector neighboursList so that it contains the indexes of all the closest
  von neumann neighbours of cell i and considering periodic border conditions
  for a 2d landscape of size n
  */

  neighboursList.clear();

  /*
  going through all the possible cases. note: the 2d landscape is manipulated
  as a flattened 1d array
  */
  if (i==0) {neighboursList={n-1,n*(n-1),1,n}; }
  else if(i==n*n-1) {neighboursList={n*n-2,(n-1)*n-1,n*(n-1),n-1}; }
  else if(i==n-1) { neighboursList={n-2,n*n-1,0,2*n-1}; }
  else if(i==n*(n-1)) {neighboursList={n*n-1,n*(n-2),n*(n-1)+1,0}; }
  else if(i<n) {neighboursList={i-1,i+(n-1)*n,i+1,i+n}; }
  else if(i%n==0) {neighboursList={i+n-1,i-n,i+1,i+n}; }
  else if(i>(n-1)*n-1) {neighboursList={i-1,i-n,i+1,i-n*(n-1)};}
  else if( (i+1)%n==0 ) {neighboursList={i-1,i-n,i-(n-1),i+n};}
  else {neighboursList={i-1,i-n,i+1,i+n};}
  return;
}

void getNeighboursState(vector<unsigned int> &neighboursState, const vector<unsigned int> &landscape, unsigned int i, unsigned int state, unsigned int n)
{
  /*
  fills the vector neighboursState so that it contains the indexes of all the
  closest neighbours of i in a given state. the landscape is passed as a constant
  reference so that the vector cannot be modified by the function in main
  */

  /*
  getting the neighbours indexes in neighbour_list vector
  */
  vector<unsigned int> neighboursList;
  getNeighbours(neighboursList,i, n);
  /*
  getting the index of neighbours in the wanted state
  */
  unsigned long ix;
  for (ix=0 ; ix<neighboursList.size() ; ++ix){
    if (landscape[neighboursList[ix]] == state) {
      neighboursState.push_back( neighboursList[ix] );
    }
  }

  return;
}

////////////////////////////////////////////////////////////////////////////////
// 2- Calculation of Ecosystem Service provision:
//       - getNaturalConnectedComponents
//       - getEcosystemServiceProvision
//       - getAgriculturalProduction
////////////////////////////////////////////////////////////////////////////////

void getNaturalConnectedComponents(vector<vector<int>> &naturalComponents, unsigned int n, const vector<unsigned int> &landscape)
{
  /*
  fills a vector where each member is a vector containing the indexes of all the
  natural patches belonging to the same cluster
  */

  vector<unsigned int> naturalPatches;
  unsigned int manhattanDist;
  unsigned int i, j;
  int xi, xj, yi, yj;
  unsigned int dx, dy;

  // clearing natural components vector for refilling
  naturalComponents.clear();

  /*
  get the list of natural patches in the landscape
  */
  for(i=0 ; i<landscape.size() ; ++i){
    if (landscape[i]==0){
      naturalPatches.push_back(i);
    }
  }

  /*
  create an undirected graph with the set of natural patches to calculate
  the connected components. to estimate whether two patches are connected
  we calculate the manhattan distance between them
  */

  using namespace boost;
  {
    typedef adjacency_list< vecS, vecS, undirectedS > Graph;
    Graph G;


    for(i=0 ; i<naturalPatches.size() ; ++i){
      add_edge(i,i,G);//not sure on how to do this
      // converting 1-D coordinates to 2-D
      xi=naturalPatches[i]%n-1;
      yi=(int)naturalPatches[i]/n;
      for(j=0 ; j<i ; ++j){
        // converting 1-D coordinates to 2-D
        xj=naturalPatches[j]%n-1;
        yj=(int)naturalPatches[j]/n;
        // calculating manhattan distance between points
        dx=abs(xi-xj);
        dy=abs(yi-yj);
        // calculating cyclic distances to account for periodic borders
        if (dx>n/2){
          dx=n-dx;
        }
        if (dy>n/2){
          dy=n-dy;
        }
        //
        manhattanDist=dx+dy;
        if ( manhattanDist<2 ){
          add_edge(i, j, G);
        }
      }
    }

    /*
    initializing the vector containing the components and calculating components
    */
    vector<int> component(num_vertices(G));
    int num = connected_components(G, &component[0]);

    /*
    converting the nodes indexes into actual landscape coordinates
    */
    naturalComponents.resize(component.size());
    for (i=0 ; i<naturalComponents.size() ; ++i){
      naturalComponents[i].push_back(naturalPatches[i]);
      naturalComponents[i].push_back(component[i]);
    }
  }
  return;
}

double getEcosystemServiceProvision(const vector<vector<int>> &naturalComponents, const vector<unsigned int> &landscape, unsigned int i, unsigned int n, double ess)
{
  /*
  returns the exposure to the wanted state of patch i. currently it is only used
  for the exposure to nature. the exposure to nature scales with biodiversity
  hence like a SAR, where the area is the total natural area in contact with
  patch i
  */

  vector<int> componentMembership;
  vector<double> componentArea;
  double ecosystemServiceProvision=0;

  /*
  getting the state neighbours indexes in neighboursState vector
  */
  vector<unsigned int> neighboursState;
  getNeighboursState(neighboursState,landscape,i,0,n); // state 0 is natural

  /*
  identify cluster membership of each natural neighbour
  */
  unsigned long ix, jx;
  for (ix=0 ; ix<neighboursState.size() ; ++ix){
    jx=0;
    while(naturalComponents[jx][0]!=neighboursState[ix]){
      jx++;
    }
    componentMembership.push_back(naturalComponents[jx][1]);
  }

  /*
  calculate the area of each cluster
  */
  int area;
  for(ix=0 ; ix<componentMembership.size(); ++ix){
    area=0;
    for(jx=0 ; jx<naturalComponents.size() ; ++jx){
      if (componentMembership[ix]==naturalComponents[jx][1]){
        area++;
      }
    }
    componentArea.push_back(area);
  }

  for (ix=0 ; ix<componentArea.size(); ++ix){
    ecosystemServiceProvision+=0.25*pow(componentArea[ix]/(n*n),0.25*ess);
  }

  return ecosystemServiceProvision;
}

void getAgriculturalProduction(vector<double> &agriculturalProduction, const vector<unsigned int> &landscape, const vector<vector<int>> &naturalComponents, unsigned int n, double ys0, double yn0, double pSD, double ori, double ini, double ess, gsl_rng  *r)
{
  /*
  returns the total agricultural production for a given "landscape" and
  minimum yield "y". the minimum yield is for a cropped patch with only
  non natural neighbours. natural neighbours raise yield.
  */

  agriculturalProduction.clear();
  double syntheticInput; // this is determined by the intensification level
  double patchProduction;
  double ecosystemServices;
  double perturbation=gsl_ran_gaussian_tail(r, 0, pSD);

  unsigned long ix;
  for (ix=0 ; ix<landscape.size() ; ++ix){
    if(landscape[ix]==2){ // cropped patches
      syntheticInput = ori;
      ecosystemServices = getEcosystemServiceProvision(naturalComponents,landscape,ix,n,ess);
      patchProduction = max( 0.0, ( ys0*syntheticInput + yn0*ecosystemServices*(1-syntheticInput) )*( 1 - perturbation*(1 - ecosystemServices) ) );
    }
    else if(landscape[ix]==3){ //intense
      syntheticInput = ini;
      ecosystemServices = getEcosystemServiceProvision(naturalComponents,landscape,ix,n,ess);
      patchProduction = max( 0.0, ( ys0*syntheticInput + yn0*ecosystemServices*(1-syntheticInput) )*( 1 - perturbation*(1 - ecosystemServices) ) );
    }
    else{
      patchProduction=0;
    }
    agriculturalProduction.push_back(patchProduction);
  }

  return;
}

////////////////////////////////////////////////////////////////////////////////
// 3- Calculation of events' propensities:
//       - getConsumptionDeficit
//       - getSpontaneousPropensity
//       - getActionPropensity
//       - getAbandonmentPropensity
//       - getPropensityVector
////////////////////////////////////////////////////////////////////////////////

double getConsumptionDeficit(const vector<double> &agriculturalProduction, const vector<double> &population, const vector<double> &consumption)
{
  double totalAgriculturalProduction=0;
  unsigned long ix;
  for(ix=0;ix<agriculturalProduction.size();ix++){
    totalAgriculturalProduction+=agriculturalProduction[ix];
  }
  return population[0]*consumption[0] - totalAgriculturalProduction;
}

void getSpontaneousPropensity(vector<double> &recoveryPropensity, vector<double> &degradationPropensity, const vector<unsigned int> &landscape, const vector<vector<int>> &naturalComponents, unsigned int n, double Tr, double Td, double ess)
{
  /*
  fills the recoveryPropensity vector and the degradationPropensity vector
  */

  /*
  traverse the landscape and calculate the recovery propensity for the degraded
  patches and the degradation propensity for the natural patches
  */
  double ecosystemServices;
  unsigned long ix;
  for (ix=0 ; ix<landscape.size() ; ++ix){
    if (landscape[ix] == 1) { // if patch ix is degraded
      ecosystemServices=getEcosystemServiceProvision(naturalComponents,landscape,ix,n,ess);
      recoveryPropensity.push_back( ecosystemServices/Tr );
      degradationPropensity.push_back(0);
    }
    else if(landscape[ix] == 0){
      ecosystemServices=getEcosystemServiceProvision(naturalComponents,landscape,ix,n,ess);
      recoveryPropensity.push_back( 0 );
      degradationPropensity.push_back(1/Td*(1-ecosystemServices) );
    }
    else{
      recoveryPropensity.push_back( 0 );
      degradationPropensity.push_back( 0 );
    }
  }

  return;
}

void getActionPropensity(vector<double> &expansionPropensity, vector<double> &intensePropensity, const vector<unsigned int> &landscape, const vector<double> &agriculturalProduction, const vector<double> &population, const vector<double> &consumption, unsigned int n, double w, double a, double g)
{
  /*
  fills the cropping_propensity and restoring_propensity vector
  */

  // use them to store the accumulated probability in order to normalize afterwards
  int expansionCumSum = 0;
  int intenseCumSum = 0;

  /*
  first checking if there is a consumption deficit that justifys human action
  */
  double consumptionDeficit = getConsumptionDeficit(agriculturalProduction,population,consumption);
  if (consumptionDeficit<0){ // if humans are satisfied...
    unsigned long ix;
    for(ix=0 ; ix<landscape.size() ; ++ix){
      expansionPropensity.push_back( 0 ); // ... they do not transform the landscape
      intensePropensity.push_back( 0 ); // ... they do not transform the landscape
    }
  }
  else{ // if humans are not happy with they current resource access ...

    /*
    in this loop we calculate the probabilities of choosing one patch over other
    for cropping as a function of the clustering parameter w. we also signal
    all the degraded patches that can be restored. the restoration probability
    is uniform over space.
    */
    unsigned int ix;

    for (ix=0 ; ix<landscape.size() ; ++ix){

      if (landscape[ix] == 0){ // if patch is natural, hence can be converted to organic

        // get the indexes of the organic neighbours
        vector<unsigned int> organicNeighbours;
        getNeighboursState(organicNeighbours,landscape,ix, 2, n); // state 2 is organic
        // cropping probability expression is taken from bart's and dani's paper
        expansionPropensity.push_back( pow( max(0.1 , (double)organicNeighbours.size() ) , w ) );
        expansionCumSum += expansionPropensity.back();
        intensePropensity.push_back( 0 );

      }
      else if (landscape[ix] == 2 ){ // if patch is organic it can be intensifyed
        intensePropensity.push_back( 1/agriculturalProduction[ix] ); // the less productive organic are more likely to be intensifyed
        intenseCumSum += intensePropensity.back();
        expansionPropensity.push_back(0);

      }
      else{
        expansionPropensity.push_back(0);
        intensePropensity.push_back( 0 );
      }
    }

    /*
    now we normalize the previously obtained probabilities and get calculate the
    probability per unit time of action given the consumption deficit
    */

    if (expansionCumSum>0 && intenseCumSum>0){ // this is to avoid dividing by zero
      for (ix=0; ix<landscape.size() ; ++ix){
        expansionPropensity[ix]=expansionPropensity[ix]/expansionCumSum*g*consumptionDeficit*a;
        intensePropensity[ix]=intensePropensity[ix]/intenseCumSum*g*consumptionDeficit*(1-a);
      }
    }
    else{
      if (expansionCumSum>0){
        for (ix=0; ix<landscape.size() ; ++ix){
          expansionPropensity[ix]=expansionPropensity[ix]/expansionCumSum*g*consumptionDeficit;
        }
      }
      else if (intenseCumSum>0){
        for (ix=0; ix<landscape.size() ; ++ix){
          intensePropensity[ix]=intensePropensity[ix]/intenseCumSum*g*consumptionDeficit;
        }
      }
    }
  }
  return;
}

void getAbandonmentPropensity(vector<double> &organicAbandonPropensity, vector<double> &intenseAbandonPropensity, const vector<unsigned int> &landscape, const vector<double> &agriculturalProduction, double Ta, double ori, double ini,double m0, double m)
{
  /*
  fills the abandonment_propensity vector. the probability per unit time is
  proportional to the maintenance deficit, which is the difference between
  a patch's maintenance cost and its production
  */

  unsigned int local=0;

  unsigned int ix;
  double maintenanceDeficit=0;

  if (local==1){

    for (ix=0; ix<landscape.size(); ++ix){
      if (landscape[ix]==2){ // organic patch
        intenseAbandonPropensity.push_back(0);
        maintenanceDeficit = m0*(1+m*ori) - agriculturalProduction[ix];
        organicAbandonPropensity.push_back(max(0.0, maintenanceDeficit/Ta));

      }
      else if(landscape[ix]==3){ //intensive patch
        organicAbandonPropensity.push_back(0);
        maintenanceDeficit = m0*(1+m*ini) - agriculturalProduction[ix];
        intenseAbandonPropensity.push_back(max(0.0,maintenanceDeficit/Ta));
      }
      else{ // non cropped patches
        organicAbandonPropensity.push_back(0);
        intenseAbandonPropensity.push_back(0);
      }
    }
  }
  else{

    double totalMaintenanceDeficit=0;
    vector<double> maintenanceDeficit;

    // calculate global maintenance deficit
    for (ix=0; ix<landscape.size(); ++ix){
      if (landscape[ix]==2){
        maintenanceDeficit.push_back(m0*(1+m*ori)-agriculturalProduction[ix]);
        totalMaintenanceDeficit+=maintenanceDeficit.back();
      }
      else if(landscape[ix]==3){
        maintenanceDeficit.push_back(m0*(1+m*ini)-agriculturalProduction[ix]);
        totalMaintenanceDeficit+=maintenanceDeficit.back();
      }
      else{
        maintenanceDeficit.push_back(0);
      }
    }

    if (totalMaintenanceDeficit>0){
      for(ix=0; ix<landscape.size(); ++ix){
        if (landscape[ix]==2){ // organic
          organicAbandonPropensity.push_back(max(0.0,maintenanceDeficit[ix]/Ta));
          intenseAbandonPropensity.push_back(0);
        }
        else if (landscape[ix]==3){//intense
          organicAbandonPropensity.push_back(0);
          intenseAbandonPropensity.push_back(max(0.0,maintenanceDeficit[ix]/Ta));
        }
        else{//non cropped
          organicAbandonPropensity.push_back(0);
          intenseAbandonPropensity.push_back(0);
        }
      }
    }
    else{ // no maintenance deficit
      for (ix=0; ix<landscape.size(); ++ix){
        organicAbandonPropensity.push_back(0);
        intenseAbandonPropensity.push_back(0);
      }
    }
  }
  return;
}

void getPropensityVector(vector<double> &propensityVector, const vector<unsigned int> &landscape, const vector<vector<int>> &naturalComponents, const vector<double> &agriculturalProduction, const vector<double> &population, const vector<double> &consumption, unsigned int n, double Tr, double Td, double w, double a, double g, double Ta, double ori, double ini, double ess, double m0, double m)
{
  /*
  calls all the functions to calculate the propensity of each event and merges
  them in a single propensity vector that can be used to run the gillespie algo
  */

  vector<double> recoveryPropensity;
  vector<double> degradationPropensity;
  vector<double> expansionPropensity;
  vector<double> intensePropensity;
  vector<double> organicAbandonPropensity;
  vector<double> intenseAbandonPropensity;

  getSpontaneousPropensity(recoveryPropensity,degradationPropensity,landscape,naturalComponents,n,Tr,Td,ess);
  getActionPropensity(expansionPropensity,intensePropensity,landscape,agriculturalProduction,population,consumption,n,w,a,g);
  getAbandonmentPropensity(organicAbandonPropensity,intenseAbandonPropensity,landscape,agriculturalProduction,Ta,ori,ini,m0,m);

  // clearing the previous propensity vector to refill it
  propensityVector.clear();

  // making sure the vector is not empty to avoid bad behaviour in next loop
  propensityVector.push_back(recoveryPropensity[0]);
  unsigned long ix;
  // over these loops the cumulative sum of each propensity vector is added to
  // the total propensity vector
  for (ix=1 ; ix<recoveryPropensity.size() ; ++ix){
    propensityVector.push_back(propensityVector.back()+recoveryPropensity[ix]);
  }
  for (ix=0 ; ix<degradationPropensity.size() ; ++ix){
    propensityVector.push_back(propensityVector.back()+degradationPropensity[ix]);
  }
  for (ix=0 ; ix<expansionPropensity.size() ; ++ix){
    propensityVector.push_back(propensityVector.back()+expansionPropensity[ix]);
  }
  for (ix=0 ; ix<intensePropensity.size() ; ++ix){
    propensityVector.push_back(propensityVector.back()+intensePropensity[ix]);
  }
  for (ix=0 ; ix<organicAbandonPropensity.size() ; ++ix){
    propensityVector.push_back(propensityVector.back()+organicAbandonPropensity[ix]);
  }
  for (ix=0 ; ix<intenseAbandonPropensity.size() ; ++ix){
    propensityVector.push_back(propensityVector.back()+intenseAbandonPropensity[ix]);
  }

  return;
}

////////////////////////////////////////////////////////////////////////////////
// 4- Initialization functions:
//       - initializeLandscape
//       - initializePopulation
//       - initializeSES
////////////////////////////////////////////////////////////////////////////////

void initializeLandscape( vector<unsigned int> &landscape, unsigned int n, double ao0, double ai0, gsl_rng  *r)
{
  /*
  initializes the landscape given a fraction of initial agricultural patches a0
  */

  //unsigned int number_cropped_patches = 1;
  unsigned long ix;
  unsigned int ix_land4crop;
  unsigned int ix_landscape;
  // this vector contains the indexes of all the natural patches
  vector<unsigned int> land4crop;

  // first build a completely natural landscape with n*n patches
  for (ix=0 ; ix<n*n; ++ix){
    landscape.push_back(0);
    land4crop.push_back(ix);
  }

  unsigned int nao0=(unsigned int) (ao0*n*n);
  unsigned int nai0=(unsigned int) (ai0*n*n);
  for (ix=0 ; ix<nao0 ; ++ix){
    // selecting random location for initial cropped organic patches
    ix_land4crop = gsl_rng_uniform_int(r, land4crop.size() );
    ix_landscape = land4crop[ix_land4crop];
    landscape[ix_landscape]=2; // cropping selected patch with organic agriculture
    land4crop.erase(land4crop.begin()+ix_land4crop); // removing the selected patch so it cannot be selected again
  }
  for (ix=0 ; ix<nai0 ; ++ix){
    // selecting random location for initial cropped intense patches
    ix_land4crop = gsl_rng_uniform_int(r, land4crop.size() );
    ix_landscape = land4crop[ix_land4crop];
    landscape[ix_landscape]=3; // cropping selected patch with intense agriculture
    land4crop.erase(land4crop.begin()+ix_land4crop); // removing the selected patch so it cannot be selected again
  }

  return;
}

void initializePopulation( vector<double> &population, const vector<double> &consumption, const vector<double> &agriculturalProduction)
{
  /*given an agricultural production, it sets the population at an equilibrium
  level
  */
  unsigned int ix;
  double totalAgriculturalProduction=0;
  for(ix=0; ix<agriculturalProduction.size(); ++ix){
    totalAgriculturalProduction+=agriculturalProduction[ix];
  }

  population.push_back(totalAgriculturalProduction/consumption[0]);

  return;
}

void initializeSES( vector<unsigned int> &landscape, vector<double> &population, vector<double> &consumption, vector<vector<int>> &naturalComponents, vector<double> &agriculturalProduction, double c0, unsigned int n, double ao0, double ai0, gsl_rng  *r, double ys0, double yn0, double pSD, double ori, double ini, double ess)
{

  consumption.push_back(c0);
  initializeLandscape(landscape,n,ao0,ai0,r);
  getNaturalConnectedComponents(naturalComponents,n,landscape);
  getAgriculturalProduction(agriculturalProduction,landscape,naturalComponents,n,ys0,yn0,pSD,ori,ini,ess,r);
  initializePopulation(population,consumption,agriculturalProduction);

  return;

}

////////////////////////////////////////////////////////////////////////////////
// 5- ODEs and solver:
//       - populationEquation
//       - consumptionEquation
//       - rungeKutta4
////////////////////////////////////////////////////////////////////////////////

double populationEquation(double population, double consumption, double agriculturalProduction, double r0)
{
  /*
  returns the expression of the population ODE
  */

  return r0*population*(1-consumption*population/agriculturalProduction);

}

double consumptionEquation(double population, double consumption, double agriculturalProduction, double kg, double kd, double minimumConsumption)
{
  /*
  returns the expression of the consumption ODE, the growing and decreasing rates
  are different.
  */
  double res;

  if( consumption < agriculturalProduction/population){
    res = (agriculturalProduction/population - consumption)*kg ;
  }
  else if(consumption> agriculturalProduction/population && consumption>minimumConsumption){
    res = (agriculturalProduction/population - consumption)*kd*kg ;
  }
  else{
    res = 0;
  }

  return res;
}

void rungeKutta4(vector<double> &population, vector<double> &consumption, vector<double> &agriculturalProduction, double dt, double r0, double kg, double kd, double minimumConsumption)
{
  /*
  returns the actualized population after solving the ODE with runge kutta 4 method
  */

  double totalAgriculturalProduction=0;
  unsigned long ix;
  for(ix=0;ix<agriculturalProduction.size();ix++){
    totalAgriculturalProduction+=agriculturalProduction[ix];
  }

  double k1p,k2p,k3p,k4p,k1c,k2c,k3c,k4c;
  double p1,p2,p3,c1,c2,c3;
  double deltaP, deltaC;

  k1p=populationEquation(population[0],consumption[0],totalAgriculturalProduction,r0);
  k1c=consumptionEquation(population[0],consumption[0],totalAgriculturalProduction,kg,kd,minimumConsumption);
  p1=population[0]+0.5*k1p*dt;
  c1=consumption[0]+0.5*k1c*dt;

  k2p=populationEquation(p1,c1,totalAgriculturalProduction,r0);
  k2c=consumptionEquation(p1,c1,totalAgriculturalProduction,kg,kd,minimumConsumption);
  p2=population[0]+0.5*k2p*dt;
  c2=consumption[0]+0.5*k2c*dt;

  k3p=populationEquation(p2,c2,totalAgriculturalProduction,r0);
  k3c=consumptionEquation(p2,c2,totalAgriculturalProduction,kg,kd,minimumConsumption);
  p3=population[0]+k3p*dt;
  c3=consumption[0]+k3c*dt;

  k4p=populationEquation(p3,c3,totalAgriculturalProduction,r0);
  k4c=consumptionEquation(p3,c3,totalAgriculturalProduction,kg,kd,minimumConsumption);

  deltaP=dt*(k1p+2*k2p+2*k3p+k4p)/6;
  deltaC=dt*(k1c+2*k2c+2*k3c+k4c)/6;

  population[0]+=deltaP;
  consumption[0]+=deltaC;

  return;
}
