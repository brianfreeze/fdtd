/*Finite Dimension Time Domain Simulation
Created by: Brian Morrison (brianfreeze@github
Email: Brian_Morrison@student.uml.edu
Date Created: November 19,2015
Date Modified: November 19,2015
Description: This program is to simulate the expected electric and magnetic fields within an anechoic chamber using the FDTD method.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define SIZE 200

int main()
{
  double ez[SIZE] = {0}, hy[SIZE]={0}, imp0=377.0;
  int qTime, maxTime=1000,mm;
  int d=0; //current step
  int menu_in; //input for main menu

  FILE *p_results; //File pointer for results.dat

  /*INITIALIZING THINGS USER DOESN'T SEE */
  /*Create file for commands to run gnuplots*/
  FILE *gpcmd=fopen("gpcmd.gp","wt"); //File pointer for gnuplot commands
  fprintf(gpcmd, "plot '~/fdtd/results.dat' title 'Electric Field vs. spatial step' smooth csplines \n");
  fclose(gpcmd); //Close gpcmd file
  

  /*MAIN MENU */
  MENU:do {
    system("clear");
    printf("Anechoic Chamber FDTD Simulator\n");
    printf("Main Menu:\n");
    printf("1) Set Parameters \n");
    printf("2) Run Simulations\n");
    printf("3) Show Results\n");
    printf("9) Exit\n\n");
    printf("Command: ");
    scanf("%d", &menu_in);

    switch(menu_in) {
    case 1:
      goto PARAMETERS;
      break;

    case 2:
      goto SIMULATION;
      break;

    case 3:
      goto PLOT;
      break;

    case 9:
      printf("\nGoodbye!\n");
      goto END;
      
    default:
      printf("Incorrect input. Please input 1,2,3 or 9 \n");
      break;
    }
    goto MENU;
  /* PARAMETERS */
  PARAMETERS:printf("Parameters is currently unavailable. Returning to menu\n");
    goto MENU;

  /*SIMULATION */

  /*Open results.dat file for writing*/
  SIMULATION:printf("\n Establishing parameters for simulation:\n");
  printf("Creating results.dat file\n");
  p_results=fopen("results.dat","w"); //open results.dat to write values

  /*Error check for opening results.dat, exit program if can't open results*/
  if (p_results==NULL){
    printf("Could not open results.dat for writing.\n");
    exit(0);
  }
  else {
    printf("results.dat file successfully created!\n\n");
  }

  printf("Beginning calculations...this may take some time....\n\n");

  /*do time stepping*/
  for (qTime=0; qTime< maxTime; qTime++) {

    /*update magnetic field*/
    for (mm=0; mm<SIZE-1;mm++)
      hy[mm] = hy[mm] + (ez[mm+1]-ez[mm])/imp0;

    /*update electric field*/
    for (mm=1; mm<SIZE;mm++)
      ez[mm]=ez[mm]+(hy[mm]-hy[mm-1])*imp0;

    /*hardwired source e^-((qTime-30)*(qTime-30)/100) */
    ez[0] = exp(-(qTime - 30) * (qTime - 30)/ 100);

    /* output results to results.dat*/

    //Print index and current Efield to results.dat and start new line
    fprintf(p_results, "%4d   %g\n", d , ez[50]);

    //Increment current step
    d++;
  } //End for loop

  /*Close Results File */
  fclose(p_results); //Close results.dat file
  printf("results.dat file successfully closed.\n\n");

  /*Wait for User Input before clearing screen and returning to Main Menu*/
  printf("Press any key to continue.\n");
  getchar();
  goto MENU;
     
  /*PLOTTING */
  /*Output results.dat to gnuplot*/
  PLOT:printf("Opening gnuplot to create pretty pictures.\n\nType exit to leave gnuplot and return to program.\n\n");
  system("gnuplot 'gpcmd.gp' - ");
  printf("Press [ENTER] key to continue\n");
  getchar();
  goto MENU;
  } while(menu_in !=9);  //End of Menu Do Loop
 END:return 0;
}

