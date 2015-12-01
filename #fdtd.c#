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
#include <string.h>

#define SIZE 200

int main()
{
  double ez[SIZE] = {0}, hy[SIZE]={0}, imp0=377.0;
  int qTime, maxTime=1000,mm;
  int d=0; //current step
  int menu_in, menu_in_plot; //input for menus
  char snap_file_type[4]=".dat";
  char snap_folder[10]="snapshots/";
  char snapdecade[10]; //Snapshot of decade input
  char snap[200]; //Used to configure which decade to snapshot
  char basename[4] = "sim", filename[100];
  int frame = 0;
  FILE *snapshot;
  FILE *p_results; //File pointer for results.dat

  /*INITIALIZING THINGS USER DOESN'T SEE */
  /*Create file for commands to run gnuplots*/
  FILE *gpcmd=fopen("gpcmd.gp","wt"); //File pointer for gnuplot commands
  FILE *gpsnap=fopen("gpsnap.gp","w+");
  fprintf(gpcmd, "plot '~/fdtd/results.dat' title 'Electric Field vs. spatial step' smooth csplines \n");
  fprintf(gpsnap, "plot '~/fdtd/snapshots/sim0.dat' title 'EField Snapshot' smooth csplines \n");
  fclose(gpcmd); //Close gpcmd file
  fclose(gpsnap); 
  

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
    //ez[0] = exp(-(qTime - 30) * (qTime - 30)/ 100);

    /*use additive source located at node 50*/
    ez[50] += exp(-(qTime-30)*(qTime-30)/100);
    /* output results to results.dat*/
    //Print index and current Efield to results.dat and start new line
    fprintf(p_results, "%4d   %g\n", d , ez[50]);

    /*Output for snapshots*/
    if (qTime % 10 ==0) {
      sprintf(filename, "snapshots/%s%d.dat", basename, frame++);
      snapshot=fopen(filename, "w");
      for (mm=0; mm<SIZE;mm++)
	fprintf(snapshot, "%4d %g\n", mm, ez[mm]);
      fclose(snapshot);
    }
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
  PLOT:do {
    printf("Output Menu\n");
    printf("1) Print results.dat\n");
    printf("2) Print snapshot at a decade\n");
    printf("9) Exit to Main Menu\n");
    printf("Command: ");
    scanf("%d", &menu_in_plot);

    switch(menu_in_plot) {
    case 1:
      /* Output results.dat file to GNu plot*/
      printf("Opening gnuplot to create pretty pictures.\n\nType exit to leave gnuplot and return to program.\n\n");
      system("gnuplot 'gpcmd.gp' - ");
      printf("Press [ENTER] key to continue\n");
      getchar();
      goto PLOT;
      break;
    case 2:
      //MENU FOR WHICH DECADE
      printf("Enter decade for snapshot to plot ex:'1'=10, '2'=20\n");
      printf("Decade: ");
      scanf("%10s", snapdecade);
      strcpy(snap,snap_folder);
      strcat(snap,basename);
      strcat(snap,snapdecade);
      strcat(snap,snap_file_type);
      printf("File to be printed: %s \n\n\n", snap);
      /*Change GNUplot command for user-defined decade */
      fopen("gpsnap.gp","w+");
      //fprintf(gpsnap, 
      fprintf(gpsnap, "plot '~/fdtd/%s' title 'EField Snapshot' smooth csplines \n",snap);
      fclose(gpsnap);
      system("gnuplot 'gpsnap.gp' - ");
      printf("Press [ENTER] key to continue\n");
      getchar();
      goto PLOT;
      break;
    case 9:
      goto MENU;
      break;
    default:
      printf("Enter a valid command.\n");
      goto PLOT;
      break;
    } //End of Switch statement for Plotting Menu
  } while(menu_in_plot !=9);//End of Plotting Menu Do Loop
  } while(menu_in !=9);  //End of Main Menu Do Loop
 END:return 0;
}

