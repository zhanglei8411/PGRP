

#include "stdafx.h"
#include "PGRP.h"
#include <iostream.h> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream.h>
#include <time.h>
/*====Algorithm Description====*/
/*
1.Initiate the map information
2.Initiate the plant information
3.Calculation the light idensity for each bud, and combine the gravity vector to obtain the growing vector
4.Calculate the auxin value.
5.Calculate the growing rate of each bud.
6.Growing each bud with corresponding rate.
7.Judge whether the target reached or not. 
8.Post-processing the route information.

*/

	/*====Globle Variable Definition====*/ 
	/*Calculation Control Para*/
	F32		g_BranOff_Ramdon=0.2;
	UT016	g_Age_BranOff=8;
	UT016	g_Search_Range=10;
	F32		g_K_LI_Block=0.5;
	F32		g_K_Vec_Current_LI=2.0;
	F32		g_K_Vec_Gravity=0.1;
	F32		g_K_Vec_Last_LI=0.1;
	/*Path Information*/
	 UT016	g_Iteration_Times=0;
	 UT016	g_Target_Bud_Num;
	 UT016	g_Path_Length[MAX_PATH_NUM];
	 UT016	g_Path_Point_Array[MAX_PATH_LENGTH];/*value is plant cell number*/
	 UT016	g_Path_Point_X[MAX_PATH_LENGTH];
	 UT016	g_Path_Point_Y[MAX_PATH_LENGTH];
	/*Map Information*/
	 CString g_Map_Name;
	 UT8  	g_Map[MAP_WIDTH][MAP_HEIGHT];

	/*Plant Information*/
	 UT016	g_Plant_Cell_Total_Num;
	 UT016	g_Bud_Total_Num;
	 UT016	g_Bud_Array[MAX_BUD_NUM];
	 UT016	g_Bud_Alive[MAX_BUD_NUM];
	 F32	g_Bud_Light_Idensity_Vec_Row[MAX_BUD_NUM][BEST_LI_QUANTITY];	
	 F32	g_Bud_Light_Idensity_Vec_Theta[MAX_BUD_NUM][BEST_LI_QUANTITY];
	 F32	g_Bud_Alpha[MAX_BUD_NUM];
	 F32	g_Bud_Li_Growing_Vec_Row[MAX_BUD_NUM];
	 F32	g_Bud_Growing_Vec_Row[MAX_BUD_NUM];
	 F32	g_Bud_Growing_Vec_Theta[MAX_BUD_NUM];
	 F32	g_Bud_Auxin[MAX_BUD_NUM];
	 UT016	g_Bud_Cell_Age[MAX_BUD_NUM];
	 UT016	g_Bud_Branch_Age[MAX_BUD_NUM];
	 UT016	g_Max_Cell_Age;
	 UT16	g_Parents_Array[MAX_PLANT_CELL_NUM];
	 UT16	g_Location_X[MAX_PLANT_CELL_NUM];
	 UT16	g_Location_Y[MAX_PLANT_CELL_NUM];
	/*Light Idensity Information*/
	 F32		g_Light_Idensity[MAP_WIDTH][MAP_HEIGHT];
	/*Gravity Information*/
	 F32		g_Gravity_Vec_Row;
	 F32		g_Gravity_Vec_Theta;

/*====Function Declaration====*/ 
	 void Plant_Grow(UT08 pathfinderID,UT016 startX, UT016 startY, UT016 targetX, UT016 targetY);
	 void Post_Process(UT016 Path_Num, UT16 startX, UT16 startY);
	 void LoadMapData(void);
	 void ShowMap(void);
	 void SaveMap(CString FileName);
	 void Show_All_Path(UT08 Total_Path);
	 void InitMapDataArray(void);
	 void InitPlantDataArray(void);
	 void InitLightDataArray(void);
	 void InitPathDataArray(void);
	 UT08 Check_Bud_Is_All_Dead(void);
	 void Generate_The_First_Bud(UT16 startX, UT16 startY);
	 void Calculate_Light_Idensity (UT016 Current_Bud_Num, UT08 Search_Range, UT16 Target_X, UT16 Target_Y);
	 void Reference_Trans_Descartes_To_Polar(F32 D_X,F32 D_Y,UT016 O_X,UT016 O_Y,F32 Alpha,F32 * New_P_Row_Theta);
	 void Set_New_Plant_Cell(UT016 Bud_Num, UT16 Location_X, UT16 Location_Y);
	 void Set_New_Bud_Cell(UT016 Last_Bud_Num);
	 void Delete_Dead_Bud(UT016 Dead_Bud_Num);
	 void Get_Target(UT016 Bud_Num, UT16 Location_X, UT16 Location_Y);


//-----------------------------------------------------------------------------
// Name: Plant_Grow
// Desc: Main function of the program
//-----------------------------------------------------------------------------
void Plant_Grow(UT08 pathfinderID,UT016 startX, UT016 startY, UT016 targetX, UT016 targetY)
{
	UT16	i=0,j=0,gap_x=0,gap_y=0,bud_dead=0;
	UT016	which_x=0,which_y=0;
	UT016 	Current_Plant_Cell_Num=0;
	UT016 	Current_Bud_Num=0;
	UT016	Current_Path_Num=0;
	UT16 	Current_Cell_X=0;
	UT16 	Current_Cell_Y=0;
	UT016 	Current_Growing_Vector_K=0;
	UT016	Current_Cell_Age=0;
	UT016	Current_Branch_Age=0;
	UT016	New_Add_Bud_Num=0;
	UT16	New_Bud_X=0;
	UT16	New_Bud_Y=0;
	F32		New_Growing_X=0;
	F32		New_Growing_Y=0;
	F32		temp_x=0.0;
	F32		temp_y=0.0;
	F32		temp_rou_theta[2];
	F32		Flag_Random=0.0;
	UT32	Rand_Num=0;
	UT016	Iterate_Times=0;
	F32		Bud_Distance=0.0;
	F32		Last_Grow_Vec_Rou=0.0;
	

	UT08	temp=0;
	UT08	test_times=0;
	UT08	Flag_New_Bud=0;
	UT08	Flag_Bud_Dead=0;
	UT08	Flag_Find_Target=0;
	UT08	Flag_Get_New_Growing_Vector=0;

	
/*1.Initiate the map information*/
//	InitMapDataArray();
	InitLightDataArray();
	InitPathDataArray();
//	LoadMapData();
	
/*2.Initiate the plant information*/
	InitPlantDataArray();
	Generate_The_First_Bud(startX,startY);
	g_Map[targetX][targetY]=CELL_IS_TARGET;
	Current_Bud_Num=1;/*The first bud*/
	/*Definition the first bud growing vector as the line from start to target*/
	if( (targetX-startX)>SMALL_VALUE){	/*for avoiding the divide 0*/
		g_Bud_Growing_Vec_Row[Current_Bud_Num]=1;
		if(targetX-startX>0)
			g_Bud_Growing_Vec_Theta[Current_Bud_Num]=(F32)(atan((F32)(targetY-startY)/(F32)(targetX-startX)));
		else if (targetX-startX<0)
			g_Bud_Growing_Vec_Theta[Current_Bud_Num]=(F32)(Pi+atan((F32)(targetY-startY)/(F32)(targetX-startX)));
	}
	else{
		g_Bud_Growing_Vec_Row[Current_Bud_Num]=1.0;
		if(targetX-startX>0)
			g_Bud_Growing_Vec_Theta[Current_Bud_Num]=(F32)(atan((F32)(targetY-startY)/SMALL_VALUE));
		else if (targetX-startX>0)
			g_Bud_Growing_Vec_Theta[Current_Bud_Num]=(F32)(Pi+atan((F32)(targetY-startY)/SMALL_VALUE));
	}

	/*Get the Gravity Vector*/
	g_Gravity_Vec_Theta=g_Bud_Growing_Vec_Theta[1];
	g_Gravity_Vec_Row=GRAVITY;

	Flag_Find_Target=NOT_FIND;/*open the cycle*/
	Iterate_Times=0;
	while(!Flag_Find_Target){	/*Iteration until find the route to target*/


/*3.Calculation the light idensity for each bud, and combine the gravity vector to obtain the growing vector*/	
	Current_Bud_Num=g_Bud_Total_Num;

	Flag_Bud_Dead=Check_Bud_Is_All_Dead();
	if(Flag_Bud_Dead==1){
		printf("\nAll Bud is Dead! Program Over!\n");
		ShowMap();
		break;/*exit the program with fail rezult*/
	}

	for(i=1;i<=Current_Bud_Num;i++){
		if(g_Bud_Alive[i]==BUD_IS_ALIVE){
			Calculate_Light_Idensity(i, g_Search_Range,targetX,targetY);
		}
	}
/*4.Judge the Branch off condition*/
	for(i=1;i<=Current_Bud_Num;i++){
		if(g_Bud_Alive[i]==BUD_IS_ALIVE){
			if(g_Bud_Branch_Age[i]>=g_Age_BranOff+(F32)(g_Bud_Cell_Age[i])/AGE_FOR_BRAN_OFF_K){
				srand( (unsigned)time( NULL ) );
				Rand_Num=rand();
				Flag_Random=(F32)(Rand_Num%100)/100.0;
				if(Flag_Random<g_BranOff_Ramdon){
					printf("\n--->Bud:[%d] generate the New Bud!",i);
					Set_New_Bud_Cell(i);
				}
			}
		}
	}
	Current_Bud_Num=g_Bud_Total_Num;
/*5.Calculate the auxin value.*/
	for(i=1;i<=Current_Bud_Num;i++){
		if(g_Bud_Alive[i]==BUD_IS_ALIVE){
			if(K_AUXIN_1*g_Bud_Light_Idensity_Vec_Row[i][0]>BEST_AC_FOR_BUD){
				g_Bud_Auxin[i]=BEST_AC_FOR_BUD+K_AUXIN_2*(F32)(g_Max_Cell_Age-g_Bud_Cell_Age[i]);
			}
			else{
				g_Bud_Auxin[i]=K_AUXIN_1*g_Bud_Light_Idensity_Vec_Row[i][0]+K_AUXIN_2*(F32)(g_Max_Cell_Age-g_Bud_Cell_Age[i]);/*get the concentration of auxin*/
				printf("\n--->Bud:[%d] auxin is %.3f",i,g_Bud_Auxin[i]);
			}
		}
	}
	
/*6.Calculate the growing vector of each bud.*/

	/*Calculate the growing rate of each bud*/
	for(i=1;i<=Current_Bud_Num;i++){
		if(g_Bud_Alive[i]==BUD_IS_ALIVE){
			if((g_Bud_Auxin[i]<=BEST_AC_FOR_BUD)&&(g_Bud_Auxin[i]>=0)){
				g_Bud_Li_Growing_Vec_Row[i]=K_Grow_1*g_Bud_Auxin[i]+K_Grow_2;
			}
			else if (g_Bud_Auxin[i]>BEST_AC_FOR_BUD){
				g_Bud_Li_Growing_Vec_Row[i]=K_Grow_3*g_Bud_Auxin[i]+(K_Grow_1*BEST_AC_FOR_BUD+K_Grow_2)-K_Grow_3*BEST_AC_FOR_BUD;
				printf("\n===>Bud:[%d] It is restricted!!",i);
			}

			/*Calculate the growing vector with gravity vector and former growing vector*/
			Last_Grow_Vec_Rou=g_Bud_Growing_Vec_Row[i];
			temp_x=(F32)(g_K_Vec_Current_LI*g_Bud_Li_Growing_Vec_Row[i]*cos(g_Bud_Light_Idensity_Vec_Theta[i][0]+g_Bud_Alpha[i])+g_K_Vec_Gravity*g_Gravity_Vec_Row*cos(g_Gravity_Vec_Theta)+g_K_Vec_Last_LI*g_Bud_Growing_Vec_Row[i]*cos(g_Bud_Growing_Vec_Theta[i]+g_Bud_Alpha[i]));
			temp_y=(F32)(g_K_Vec_Current_LI*g_Bud_Li_Growing_Vec_Row[i]*sin(g_Bud_Light_Idensity_Vec_Theta[i][0]+g_Bud_Alpha[i])+g_K_Vec_Gravity*g_Gravity_Vec_Row*sin(g_Gravity_Vec_Theta)+g_K_Vec_Last_LI*g_Bud_Growing_Vec_Row[i]*sin(g_Bud_Growing_Vec_Theta[i]+g_Bud_Alpha[i]));

			Reference_Trans_Descartes_To_Polar(temp_x,temp_y, 0, 0, g_Bud_Alpha[i],temp_rou_theta);
			g_Bud_Growing_Vec_Row[i]=temp_rou_theta[0];
			g_Bud_Growing_Vec_Theta[i]=temp_rou_theta[1];
			/*modify the grow rate just refer to the lihgt idensity*/
			g_Bud_Growing_Vec_Row[i]=g_Bud_Li_Growing_Vec_Row[i];
			printf("\n--->Bud:[%d] Total[%.3f]=G_L:[%.3f]+G_Gra[%.3f]+G_F[%.3f]",i,g_Bud_Growing_Vec_Row[i],g_Bud_Li_Growing_Vec_Row[i],g_Gravity_Vec_Row,Last_Grow_Vec_Rou);
		}
	}

	
	
/*7.Growing each bud with corresponding rate.*/
	for(i=1;i<=Current_Bud_Num;i++){
		if(Flag_Find_Target==FIND)
			break;
		if(g_Bud_Alive[i]==BUD_IS_ALIVE){
			Flag_New_Bud=FLASE;
			test_times=0;	
			Bud_Distance=0.95*sqrt(pow((targetX-g_Location_X[g_Bud_Array[i]]),2)+pow((targetY-g_Location_Y[g_Bud_Array[i]]),2));
			/*Avoid jumping over the target*/
			if(Bud_Distance<=g_Bud_Growing_Vec_Row[i]){
				New_Bud_X=targetX;
				New_Bud_Y=targetY;
				printf("\n--->Bud:[%d] NewX[%d];NewY[%d]--->Nearly Get Target!!\n",i,New_Bud_X,New_Bud_Y);
			}
			else{
				while(Flag_New_Bud!=OK){
					New_Bud_X=floor((F32)(g_Location_X[g_Bud_Array[i]])+g_Bud_Growing_Vec_Row[i]*cos(g_Bud_Growing_Vec_Theta[i]+g_Bud_Alpha[i])+0.5);
					New_Bud_Y=floor((F32)(g_Location_Y[g_Bud_Array[i]])+g_Bud_Growing_Vec_Row[i]*sin(g_Bud_Growing_Vec_Theta[i]+g_Bud_Alpha[i])+0.5);
					if(g_Map[New_Bud_X][New_Bud_Y]==CELL_IS_TARGET){
						break;
					}
					else if(g_Map[New_Bud_X][New_Bud_Y]==CELL_IS_OBSTACLE||g_Map[New_Bud_X][New_Bud_Y]==CELL_IS_PLANT_BUD||g_Map[New_Bud_X][New_Bud_Y]==CELL_IS_PLANT_STEM){
						g_Bud_Growing_Vec_Row[i]=g_Bud_Growing_Vec_Row[i]*0.75;
						Flag_New_Bud=FLASE;
						printf("\n===>Bud:[%d] New Bud Is Unwalkable!G_R is [%.3f] Now!",i,g_Bud_Growing_Vec_Row[i]);
						test_times++;
					}
					else
						Flag_New_Bud=OK;
					if(test_times>2){
						break;
					}		
				}
				printf("\n--->Bud:[%d] NewX[%d];NewY[%d]",i,New_Bud_X,New_Bud_Y);
			}
			gap_x=New_Bud_X-g_Location_X[g_Bud_Array[i]];
			gap_y=New_Bud_Y-g_Location_Y[g_Bud_Array[i]];
			/*complete the single bud growing task*/
			bud_dead=0;/*init the bud state*/
			if(New_Bud_X>(MAP_WIDTH-1)||New_Bud_X<=0||New_Bud_Y>(MAP_HEIGHT-1)||New_Bud_Y<=0)
				bud_dead=1;
			while((gap_x!=0||gap_y!=0)&&bud_dead==0){
				if(fabs(gap_y)>fabs(gap_x)){
					which_x=g_Location_X[g_Bud_Array[i]];
					which_y=g_Location_Y[g_Bud_Array[i]]+gap_y/fabs(gap_y);
					temp=g_Map[which_x][which_y];
					/*Judge the target*/
					if(temp==CELL_IS_TARGET){
						Flag_Find_Target=FIND;
						Get_Target(i,which_x,which_y);
						break;
						}
					/*Judge the cell is not obstacle or plant*/
					if(temp==CELL_IS_BLANK){
						Set_New_Plant_Cell(i,which_x,which_y);
						gap_y=gap_y-gap_y/fabs(gap_y);
					}
					else{
						/*gradient direction*/
						if(gap_x==0)
							which_x=g_Location_X[g_Bud_Array[i]];
						else if(gap_y==0)
							which_y=g_Location_Y[g_Bud_Array[i]];
						else{
							which_x=g_Location_X[g_Bud_Array[i]]+gap_x/fabs(gap_x);
							which_y=g_Location_Y[g_Bud_Array[i]]+gap_y/fabs(gap_y);
						}
						temp=g_Map[which_x][which_y];
						/*Judge the target*/
						if(temp==CELL_IS_TARGET){
							Flag_Find_Target=FIND;
							Get_Target(i,which_x,which_y);
							break;
							}
						if(temp==CELL_IS_BLANK){
							Set_New_Plant_Cell(i,which_x,which_y);
							gap_x=gap_x-gap_x/fabs(gap_x);
							gap_y=gap_y-gap_y/fabs(gap_y);
							}
						else{
							/*the other vertical direction*/
							if(gap_x==0)
								which_x=g_Location_X[g_Bud_Array[i]];
							else{
								which_x=g_Location_X[g_Bud_Array[i]]+gap_x/fabs(gap_x);
								which_y=g_Location_Y[g_Bud_Array[i]];
							}
							temp=g_Map[which_x][which_y];
							/*Judge the target*/
							if(temp==CELL_IS_TARGET){
								Flag_Find_Target=FIND;
								Get_Target(i,which_x,which_y);
								break;
								}
							if(temp==CELL_IS_BLANK){
								Set_New_Plant_Cell(i,which_x,which_y);
								gap_x=gap_x-gap_x/fabs(gap_x);
								}
							else
								bud_dead=1;/*No way to go*/
						}
					}	
				}
				else if(fabs(gap_y)<fabs(gap_x)){
					which_x=g_Location_X[g_Bud_Array[i]]+gap_x/fabs(gap_x);
					which_y=g_Location_Y[g_Bud_Array[i]];
					temp=g_Map[which_x][which_y];
					/*Judge the target*/
					if(temp==CELL_IS_TARGET){
						Flag_Find_Target=FIND;
						Get_Target(i,which_x,which_y);
						break;
					}
					/*Judge the cell is not obstacle or plant*/
					if(temp==CELL_IS_BLANK){
						Set_New_Plant_Cell(i,which_x,which_y);
						gap_x=gap_x-gap_x/fabs(gap_x);
					}
					else {
						if(gap_x==0)
							which_x=g_Location_X[g_Bud_Array[i]];
						else if(gap_y==0)
							which_y=g_Location_Y[g_Bud_Array[i]];
						else{
							which_x=g_Location_X[g_Bud_Array[i]]+gap_x/fabs(gap_x);
							which_y=g_Location_Y[g_Bud_Array[i]]+gap_y/fabs(gap_y);
						}
						temp=g_Map[which_x][which_y];
						/*Judge the target*/
						if(temp==CELL_IS_TARGET){
							Flag_Find_Target=FIND;
							Get_Target(i,which_x,which_y);
							break;
							}
						if(temp==CELL_IS_BLANK){
							Set_New_Plant_Cell(i,which_x,which_y);
							gap_x=gap_x-gap_x/fabs(gap_x);
							gap_y=gap_y-gap_y/fabs(gap_y);
							}
						else{
							if(gap_y==0)
								which_y=g_Location_Y[g_Bud_Array[i]];
							else{
								which_x=g_Location_X[g_Bud_Array[i]];
								which_y=g_Location_Y[g_Bud_Array[i]]+gap_y/fabs(gap_y);
							}
							temp=g_Map[which_x][which_y];
							/*Judge the target*/
							if(temp==CELL_IS_TARGET){
								Flag_Find_Target=FIND;
								Get_Target(i,which_x,which_y);
								break;
							}
							if(temp==CELL_IS_BLANK){
								Set_New_Plant_Cell(i,which_x,which_y);
								gap_y=gap_y-gap_y/fabs(gap_y);
							}
							else
								bud_dead=1;/*No way to go*/
						}
					}
				}
				else if(fabs(gap_y)==fabs(gap_x)){
					which_x=g_Location_X[g_Bud_Array[i]]+gap_x/fabs(gap_x);
					which_y=g_Location_Y[g_Bud_Array[i]]+gap_y/fabs(gap_y);
					temp=g_Map[which_x][which_y];
					/*Judge the target*/
					if(temp==CELL_IS_TARGET){
						Flag_Find_Target=FIND;
						Get_Target(i,which_x,which_y);
						break;
					}
					/*Judge the cell is not obstacle or plant*/
					if(temp==CELL_IS_BLANK){
						Set_New_Plant_Cell(i,which_x,which_y);
						gap_x=gap_x-gap_x/fabs(gap_x);
						gap_y=gap_y-gap_y/fabs(gap_y);
					}
					else {
						which_x=g_Location_X[g_Bud_Array[i]]+gap_x/fabs(gap_x);
						which_y=g_Location_Y[g_Bud_Array[i]];
						temp=g_Map[which_x][which_y];
						/*Judge the target*/
						if(temp==CELL_IS_TARGET){
							Flag_Find_Target=FIND;
							Get_Target(i,which_x,which_y);
							break;
							}
						if(temp==CELL_IS_BLANK){
							Set_New_Plant_Cell(i,which_x,which_y);
							gap_x=gap_x-gap_x/fabs(gap_x);
							}
						else{
							which_x=g_Location_X[g_Bud_Array[i]];
							which_y=g_Location_Y[g_Bud_Array[i]]+gap_y/fabs(gap_y);
							temp=g_Map[which_x][which_y];
							/*Judge the target*/
							if(temp==CELL_IS_TARGET){
								Flag_Find_Target=FIND;
								Get_Target(i,which_x,which_y);
								break;
							}
							if(temp==CELL_IS_BLANK){
								Set_New_Plant_Cell(i,which_x,which_y);
								gap_y=gap_y-gap_y/fabs(gap_y);
							}
							else
								bud_dead=1;/*No way to go*/
						}
					}
				}
			}

		/*Dead bud treatment*/
			if (bud_dead==1){
				//Delete_Dead_Bud(i);
				g_Bud_Alive[i]=BUD_IS_DEAD;
				g_Map[g_Location_X[g_Bud_Array[i]]][g_Location_Y[g_Bud_Array[i]]]=CELL_IS_DEAD_BUD;
				printf("\nDead Bud:[%d]",i);
			}
			else if ((Flag_Find_Target==NOT_FIND)&&(g_Location_X[g_Bud_Array[i]]==New_Bud_X)&&(g_Location_Y[g_Bud_Array[i]]==New_Bud_Y)){
					/*show the success of the bud growing*/
			}
		}
	}

		
/*7.Judge whether the target reached or not. */
	if(Flag_Find_Target==FIND){
		g_Iteration_Times=Iterate_Times;
		break;
	}
	Iterate_Times++;

	printf("\nIterate Total Times is: %d\n",Iterate_Times);
	}

	
/*8.Post-processing the route information.*/	
	if(Flag_Find_Target==FIND){
		Current_Path_Num=pathfinderID;
		Post_Process(Current_Path_Num,startX,startY);
	}
	
}


//-----------------------------------------------------------------------------
// Name: Check_Bud_Is_All_Dead
// Desc: Check bud is all dead or not
//-----------------------------------------------------------------------------
void Post_Process(UT016 Path_Num, UT16 startX, UT16 startY)
{
	UT16 	Current_Plant_Cell_Num=0;
	UT16	i=0;
	
	g_Path_Length[Path_Num]=0;
	Current_Plant_Cell_Num=g_Plant_Cell_Total_Num;
	for(i=1;i<=MAX_PATH_LENGTH;i++){
		g_Path_Point_Array[i]=Current_Plant_Cell_Num;
		g_Path_Point_X[i]=g_Location_X[Current_Plant_Cell_Num];
		g_Path_Point_Y[i]=g_Location_Y[Current_Plant_Cell_Num];
		if((g_Path_Point_X[i]==startX)&&(g_Path_Point_Y[i]==startY)){
			break;
		}
		Current_Plant_Cell_Num=g_Parents_Array[Current_Plant_Cell_Num];
	}
	g_Path_Length[Path_Num]=i;
	
	for(i=1;i<=g_Path_Length[Path_Num];i++){
		if(i!=1&&i!=g_Path_Length[Path_Num])
			g_Map[g_Path_Point_X[g_Path_Length[Path_Num]-i+1]][g_Path_Point_Y[g_Path_Length[Path_Num]-i+1]]=CELL_IS_PATH;
		printf("\n***The Path Point [%d] is:<%d><%d>***",i,g_Path_Point_X[g_Path_Length[Path_Num]-i+1],g_Path_Point_Y[g_Path_Length[Path_Num]-i+1]);
	}
}

//-----------------------------------------------------------------------------
// Name: Check_Bud_Is_All_Dead
// Desc: Check bud is all dead or not
//-----------------------------------------------------------------------------
UT08 Check_Bud_Is_All_Dead(void)
{
	UT016	i=0;
	for(i=1;i<=g_Bud_Total_Num;i++){
		if(g_Bud_Alive[i]==BUD_IS_ALIVE)
			return 0;			
	}
	return 1;
}
//-----------------------------------------------------------------------------
// Name: Generate_The_First_Bud
// Desc: Generate the first bud properties
//-----------------------------------------------------------------------------
void Generate_The_First_Bud(UT16 startX, UT16 startY)
{
	UT016 	Current_Plant_Cell_Num=0;
	UT016 	Current_Bud_Num=0;
	UT16	Current_Cell_X=0;
	UT16	Current_Cell_Y=0;

	g_Plant_Cell_Total_Num=1; /*Creat the 1st plant cell point*/
	g_Bud_Total_Num=1; /*Creat the 1st bud point*/
	g_Max_Cell_Age=1;/*The cell age begin with 1*/
	
	Current_Plant_Cell_Num=g_Plant_Cell_Total_Num;
	Current_Bud_Num=g_Bud_Total_Num;
	Current_Cell_X=startX;
	Current_Cell_Y=startY;

	/*generate the new plant-bud information*/
	g_Location_X[Current_Plant_Cell_Num]=Current_Cell_X;
	g_Location_Y[Current_Plant_Cell_Num]=Current_Cell_Y;
	g_Parents_Array[Current_Plant_Cell_Num]=0;/*The first cell bud have no parent */;
	g_Bud_Cell_Age[Current_Bud_Num]=1;/*the age of the first bud is 1*/
	g_Bud_Branch_Age[Current_Bud_Num]=1;
	g_Bud_Array[Current_Bud_Num]=Current_Plant_Cell_Num;
	/*Update the map information*/
	g_Map[Current_Cell_X][Current_Cell_Y]=CELL_IS_PLANT_BUD;

}



//-----------------------------------------------------------------------------
// Name: Get_Target
// Desc: Store the information of the state of the plant
//-----------------------------------------------------------------------------
void Get_Target(UT016 Bud_Num, UT16 Location_X, UT16 Location_Y)
{	UT016 	Last_Plant_Cell_Num=0;
	UT016 	Current_Plant_Cell_Num=0;
	UT16 	Last_Bud_X=0;
	UT16 	Last_Bud_Y=0;
	UT16 	Current_Bud_X=0;
	UT16 	Current_Bud_Y=0;

	Last_Plant_Cell_Num=g_Plant_Cell_Total_Num;
	g_Plant_Cell_Total_Num=g_Plant_Cell_Total_Num+1;
	Current_Plant_Cell_Num=g_Plant_Cell_Total_Num;
	Last_Bud_X=g_Location_X[g_Bud_Array[Bud_Num]];
	Last_Bud_Y=g_Location_Y[g_Bud_Array[Bud_Num]];
	Current_Bud_X=Location_X;
	Current_Bud_Y=Location_Y;
	/*Update the new plant-bud information*/
	g_Location_X[Current_Plant_Cell_Num]=Current_Bud_X;
	g_Location_Y[Current_Plant_Cell_Num]=Current_Bud_Y;
	g_Parents_Array[Current_Plant_Cell_Num]=g_Bud_Array[Bud_Num];/*The last Bud cell Num set as parent of New bud */;
	g_Bud_Cell_Age[Bud_Num]=g_Bud_Cell_Age[Bud_Num]+1;
	g_Bud_Array[Bud_Num]=Current_Plant_Cell_Num;
	/*Update the map information*/
	g_Map[Last_Bud_X][Last_Bud_Y]=CELL_IS_PLANT_STEM;
//	printf("\n");
//	printf("[Cell:%d<%d><%d><%d>]",Last_Plant_Cell_Num,Last_Bud_X,Last_Bud_Y,g_Map[Last_Bud_X][Last_Bud_Y]);
	g_Target_Bud_Num=Bud_Num;
	printf("\nGet Target!!The Bud is [%d]",g_Target_Bud_Num);
}

//-----------------------------------------------------------------------------
// Name: Set_New_Bud_Cell
// Desc: add a new bud with the same positon of last bud
//-----------------------------------------------------------------------------
void Set_New_Bud_Cell(UT016 Last_Bud_Num)
{	
	UT16 	Last_Bud_X=0;
	UT16 	Last_Bud_Y=0;
	UT016	i=0;
	UT016	New_Bud_Num=0;
	UT08	Flag_Random=0;
	UT32	Rand_Num=0;

	srand( (unsigned)time( NULL ) );
	Rand_Num=rand();
	Flag_Random=(Rand_Num%10);
	Flag_Random=floor(((F32)Flag_Random/10.0)*(F32)(BEST_LI_QUANTITY-1)+0.5);


	Last_Bud_X=g_Location_X[g_Bud_Array[Last_Bud_Num]];
	Last_Bud_Y=g_Location_Y[g_Bud_Array[Last_Bud_Num]];
	g_Bud_Total_Num=g_Bud_Total_Num+1;
	New_Bud_Num=g_Bud_Total_Num;
	/*Add the new bud information with the same position*/
	g_Bud_Array[New_Bud_Num]=g_Bud_Array[Last_Bud_Num];/*The same cell*/
	g_Bud_Light_Idensity_Vec_Row[New_Bud_Num][0]=g_Bud_Light_Idensity_Vec_Row[Last_Bud_Num][Flag_Random+1];	/*Second best Li derection*/
	g_Bud_Light_Idensity_Vec_Theta[New_Bud_Num][0]=g_Bud_Light_Idensity_Vec_Theta[Last_Bud_Num][Flag_Random+1];
	g_Bud_Alpha[New_Bud_Num]=g_Bud_Alpha[Last_Bud_Num];
	g_Bud_Growing_Vec_Row[New_Bud_Num]=0;
	g_Bud_Growing_Vec_Theta[New_Bud_Num]=0;
	g_Bud_Cell_Age[New_Bud_Num]=g_Bud_Cell_Age[Last_Bud_Num];
      	g_Bud_Branch_Age[New_Bud_Num]=1;
	g_Bud_Branch_Age[Last_Bud_Num]=1;/*return to 1*/

}

//-----------------------------------------------------------------------------
// Name: Set_New_Plant_Cell
// Desc: update the properties of the new cell and map information
//-----------------------------------------------------------------------------
void Set_New_Plant_Cell(UT016 Bud_Num, UT16 Location_X, UT16 Location_Y)
{	
	UT016 	Last_Plant_Cell_Num=0;
	UT016 	Current_Plant_Cell_Num=0;
	UT16 	Last_Bud_X=0;
	UT16 	Last_Bud_Y=0;
	UT16 	Current_Bud_X=0;
	UT16 	Current_Bud_Y=0;

	if(Location_X>(MAP_WIDTH-1)||Location_X<=0||Location_Y>(MAP_HEIGHT-1)||Location_Y<=0)
		printf("\nbud [%d] out of range\n",Bud_Num);
	
	Last_Plant_Cell_Num=g_Plant_Cell_Total_Num;
	g_Plant_Cell_Total_Num=g_Plant_Cell_Total_Num+1;
	Current_Plant_Cell_Num=g_Plant_Cell_Total_Num;
	Last_Bud_X=g_Location_X[g_Bud_Array[Bud_Num]];
	Last_Bud_Y=g_Location_Y[g_Bud_Array[Bud_Num]];
	Current_Bud_X=Location_X;
	Current_Bud_Y=Location_Y;
	/*Update the new plant-bud information*/
	g_Location_X[Current_Plant_Cell_Num]=Current_Bud_X;
	g_Location_Y[Current_Plant_Cell_Num]=Current_Bud_Y;
	g_Parents_Array[Current_Plant_Cell_Num]=g_Bud_Array[Bud_Num];/*The last Bud cell Num set as parent of New bud */;
	g_Bud_Cell_Age[Bud_Num]=g_Bud_Cell_Age[Bud_Num]+1;
	g_Bud_Branch_Age[Bud_Num]=g_Bud_Branch_Age[Bud_Num]+1;
	g_Bud_Array[Bud_Num]=Current_Plant_Cell_Num;
	/*Update the map information*/
	g_Map[Last_Bud_X][Last_Bud_Y]=CELL_IS_PLANT_STEM;
//	printf("\n");
//	printf("[Cell:%d<%d><%d>[%d]]",Last_Plant_Cell_Num,Last_Bud_X,Last_Bud_Y,g_Map[Last_Bud_X][Last_Bud_Y]);
	g_Map[Current_Bud_X][Current_Bud_Y]=CELL_IS_PLANT_BUD;
//	printf("[Cell:%d<%d><%d>[%d]]\n",Current_Plant_Cell_Num,Current_Bud_X,Current_Bud_Y,g_Map[Current_Bud_X][Current_Bud_Y]);
	/*update the max cell age*/
	if (g_Max_Cell_Age<g_Bud_Cell_Age[Bud_Num]){
		g_Max_Cell_Age=g_Bud_Cell_Age[Bud_Num];
	}

}


//-----------------------------------------------------------------------------
// Name: Calculate_Light_Idensity
// Desc: Calculate the light idensity of the field round the bud, for the new growing vector define. And creat the new bud points
//-----------------------------------------------------------------------------
void Calculate_Light_Idensity (UT016 Current_Bud_Num, UT08 Search_Range, UT16 Target_X, UT16 Target_Y)
{
	UT16 	Bud_Point_X=0;
	UT16 	Bud_Point_Y=0;
	F32		Bud_Point_K=0.0;
	F32		Alpha=0.0;
	UT08	Flag_Bud_K_Cal=OK;
	UT16	which_x=0,which_y=0;
	UT16	shadow_x=0,shadow_y=0;
	UT16	sub_x=0,sub_y=0,up_x=0,up_y=0;
	UT16	i=0,j=0,p=0,q=0,gap_x=0,gap_y=0;
	F32 		Polar_row_theta[2];	
	F32		which_rou=0.0;
	F32		which_theta=0.0;
	F32		Li[13];
	UT08	Li_Num[13];
	UT08	Li_Array[13];
	UT08	Temp_Li_Array=0;
	UT8		type=0,sign_K=0;
	F32		Search_Range_K=1.0;
	UT08	Temp_Search_Range=0;
	

	for(i=0;i<13;i++){
		Li[i]=0.0;
		Li_Num[i]=0;
		Li_Array[i]=i;
	}
	Polar_row_theta[0]=0.0;
	Polar_row_theta[1]=0.0;

	Bud_Point_X=g_Location_X[g_Bud_Array[Current_Bud_Num]];
	Bud_Point_Y=g_Location_Y[g_Bud_Array[Current_Bud_Num]];
	
	/*Check for avoiding devide 0*/
	if(fabs((F32)(Target_X-Bud_Point_X))<SMALL_VALUE){
		if ((F32)(Target_X-Bud_Point_X)>0)
			Bud_Point_X=Target_X-SMALL_VALUE;
		else if((F32)(Target_X-Bud_Point_X)<0)
			Bud_Point_X=Target_X+SMALL_VALUE;
		else
			Flag_Bud_K_Cal=FAIL;
	}
	
	/*Calculate the Alpha and the Bud point K*/
	if(Flag_Bud_K_Cal==OK){
		Bud_Point_K=(F32)(Target_Y-Bud_Point_Y)/(F32)(Target_X-Bud_Point_X);
		if((Target_X-Bud_Point_X)>0)
			Alpha=atan((F32)(Target_Y-Bud_Point_Y)/(F32)(Target_X-Bud_Point_X));
		else if ((Target_X-Bud_Point_X)<0)
			Alpha=Pi+atan((F32)(Target_Y-Bud_Point_Y)/(F32)(Target_X-Bud_Point_X));
	}	
	else
	{
		if((F32)(Target_Y-Bud_Point_Y)>0){
			Bud_Point_K=MAX_VLAUE;
			Alpha=(F32)(Pi/2);
		}
		else if((F32)(Target_Y-Bud_Point_Y)<0){
			Bud_Point_K=(-MAX_VLAUE);
			Alpha=(F32)(3/2*Pi);
		}
	}

	sign_K=Bud_Point_K/(fabs(Bud_Point_K));

	g_Bud_Alpha[Current_Bud_Num]=Alpha;		/*For using of cell growing in step 6*/
		
	
	/*Search the Square Field,and Calculate the light idensity of blank cells*/
	for (i=0;i<=(2*Search_Range);i++){
		which_x=(Bud_Point_X-Search_Range)+i;	
		if(which_x<(MAP_WIDTH-1)&&which_x>0){
			for (j=0;j<=(2*Search_Range);j++){
				/*Current Search Point Position*/
				which_y=(Bud_Point_Y-Search_Range)+j;
				if(which_y<(MAP_HEIGHT-1)&&which_y>0){
					/*Reference frame tansfer*/
					Reference_Trans_Descartes_To_Polar(which_x,which_y,Bud_Point_X,Bud_Point_Y,Alpha,Polar_row_theta);
					which_rou=Polar_row_theta[0];
					which_theta=Polar_row_theta[1];
					/*Judge in the half circle*/
					if ((0<=which_rou&&which_rou<=Search_Range)&&(((-Pi/2)<=which_theta)&&((Pi/2)>=which_theta))){
						/*Judge Cell Type*/
						type=g_Map[which_x][which_y];
						if(type==CELL_IS_BLANK){
							g_Light_Idensity[which_x][which_y]=K_LIGHT_IDENSITY_1/(pow((which_x-Target_X),2)+pow((which_y-Target_Y),2))*(pow((Target_X-Bud_Point_X),2)+pow((Target_Y-Bud_Point_Y),2));
						}
						else if (type==CELL_IS_TARGET){
							Temp_Search_Range=Search_Range;
							Search_Range=floor(sqrt(pow((which_x-Bud_Point_X),2)+pow((which_y-Bud_Point_Y),2))+0.5);	
							Search_Range_K=(F32)(Search_Range)/(F32)(Temp_Search_Range);
							//printf("\nK=%.3f",Search_Range_K);
							printf("\n===>Serch Range Adjust [%d]->[%d]",Temp_Search_Range,Search_Range);
						}
					}
				}
			}
		}
	}
	
	/*Search the Square Field,and Calculate shadow for obstacle*/
	for (i=0;i<=(2*Search_Range);i++){
		which_x=(Bud_Point_X-Search_Range)+i;
		if(which_x<(MAP_WIDTH-1)&&which_x>0){
			for (j=0;j<=(2*Search_Range);j++){
				/*Current Search Point Position*/
				which_y=(Bud_Point_Y-Search_Range)+j;
				if(which_y<(MAP_HEIGHT-1)&&which_y>0){
					/*Reference frame tansfer*/
					Reference_Trans_Descartes_To_Polar(which_x,which_y,Bud_Point_X,Bud_Point_Y,Alpha,Polar_row_theta);
					which_rou=Polar_row_theta[0];
					which_theta=Polar_row_theta[1];
					/*Judge in the half circle*/
					if ((0<=which_rou&&which_rou<=Search_Range)&&(((-Pi/2)<=which_theta)&&((Pi/2)>=which_theta))){
						/*Judge Cell Type*/
						type=g_Map[which_x][which_y];
						if(type==CELL_IS_OBSTACLE||type==CELL_IS_PLANT_BUD||type==CELL_IS_PLANT_STEM){
							sub_x=floor((((F32)(Target_X)*(Bud_Point_K*(F32)(Bud_Point_Y)-Bud_Point_K*(F32)(which_y)+(F32)Bud_Point_X)-(F32)which_x*(F32)Bud_Point_Y*Bud_Point_K-(F32)which_x*(F32)Bud_Point_X+Bud_Point_K*(F32)Target_Y*(F32)which_x)/(Bud_Point_K*(F32)(Target_Y-which_y)+(F32)(Target_X-which_x)))+0.5);
							/*x axis shadow length*/
							if(sub_x>(MAP_WIDTH-1))
								sub_x=(MAP_WIDTH-1);
							else if(sub_x<=0)
								sub_x=1;
							gap_x=(which_x-1)-sub_x;
							if(gap_x>0){
								/*The 1st shadow x axis point*/
								shadow_x=sub_x;
								for(p=0;p<=gap_x;p++){
									shadow_x=sub_x+p;
									/*Calculate the shadow y axis length for current shadow x*/
									sub_y=floor((((F32)(which_y-Target_Y)/(F32)(which_x-Target_X))*((F32)shadow_x-0.5*sign_K)+((F32)which_x*(F32)Target_Y-(F32)which_y*(F32)Target_X)/((F32)which_x-(F32)Target_X))+0.5);
									up_y=floor((((F32)(which_y-Target_Y)/(F32)(which_x-Target_X))*((F32)shadow_x+0.5*sign_K)+((F32)which_x*(F32)Target_Y-(F32)which_y*(F32)Target_X)/((F32)which_x-(F32)Target_X))+0.5);
									gap_y=up_y-sub_y;
									/*The 1st shadow y axis point*/
									shadow_y=sub_y;
									for(q=0;q<=gap_y;q++){
										shadow_y=sub_y+q;
										type=g_Map[shadow_x][shadow_y];
										if(type==CELL_IS_BLANK){
											g_Light_Idensity[shadow_x][shadow_y]=g_Light_Idensity[shadow_x][shadow_y]*(1-g_K_LI_Block);
											//printf("\nObs:[%d][%d],Shad:[%d][%d]",which_x,which_y,shadow_x,shadow_y);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	/*Sum the Light idensity of each section*/
	for (i=0;i<=(2*Search_Range);i++){
		which_x=(Bud_Point_X-Search_Range)+i;
		if(which_x<(MAP_WIDTH-1)&&which_x>0){
			for (j=0;j<=(2*Search_Range);j++){
				/*Current Search Point Position*/
				which_y=(Bud_Point_Y-Search_Range)+j;
				if(which_y<(MAP_HEIGHT-1)&&which_y>0){
					type=g_Map[which_x][which_y];
					if(type==CELL_IS_BLANK){
						/*Reference frame tansfer*/
						Reference_Trans_Descartes_To_Polar(which_x,which_y,Bud_Point_X,Bud_Point_Y,Alpha,Polar_row_theta);
						which_rou=Polar_row_theta[0];
						which_theta=Polar_row_theta[1];
						/*Judge in the which section*/
						if ((5*Pi/12)<=which_theta&&(Pi/2)>=which_theta){
							Li_Num[1]=Li_Num[1]+1;
							Li[1]=Li[1]+g_Light_Idensity[which_x][which_y];}
						else if ((4*Pi/12)<=which_theta&&(5*Pi/12)>=which_theta){
							Li_Num[2]=Li_Num[2]+1;
							Li[2]=Li[2]+g_Light_Idensity[which_x][which_y];}
						else if ((3*Pi/12)<=which_theta&&(4*Pi/12)>=which_theta){
							Li_Num[3]=Li_Num[3]+1;
							Li[3]=Li[3]+g_Light_Idensity[which_x][which_y];}
						else if ((2*Pi/12)<=which_theta&&(3*Pi/12)>=which_theta){
							Li_Num[4]=Li_Num[4]+1;
							Li[4]=Li[4]+g_Light_Idensity[which_x][which_y];}
						else if ((1*Pi/12)<=which_theta&&(2*Pi/12)>=which_theta){
							Li_Num[5]=Li_Num[5]+1;
							Li[5]=Li[5]+g_Light_Idensity[which_x][which_y];}
						else if (0<=which_theta&&(1*Pi/12)>=which_theta){
							Li_Num[6]=Li_Num[6]+1;
							Li[6]=Li[6]+g_Light_Idensity[which_x][which_y];}
						else if ((-1*Pi/12)<=which_theta&&0>=which_theta){
							Li_Num[7]=Li_Num[7]+1;
							Li[7]=Li[7]+g_Light_Idensity[which_x][which_y];}
						else if ((-2*Pi/12)<=which_theta&&(-1*Pi/12)>=which_theta){
							Li_Num[8]=Li_Num[8]+1;
							Li[8]=Li[8]+g_Light_Idensity[which_x][which_y];}
						else if ((-3*Pi/12)<=which_theta&&(-2*Pi/12)>=which_theta){
							Li_Num[9]=Li_Num[9]+1;
							Li[9]=Li[9]+g_Light_Idensity[which_x][which_y];}
						else if ((-4*Pi/12)<=which_theta&&(-3*Pi/12)>=which_theta){
							Li_Num[10]=Li_Num[10]+1;
							Li[10]=Li[10]+g_Light_Idensity[which_x][which_y];}
						else if ((-5*Pi/12)<=which_theta&&(-4*Pi/12)>=which_theta){
							Li_Num[11]=Li_Num[11]+1;
							Li[11]=Li[11]+g_Light_Idensity[which_x][which_y];}
						else if ((-6*Pi/12)<=which_theta&&(-5*Pi/12)>=which_theta){
							Li_Num[12]=Li_Num[12]+1;
							Li[12]=Li[12]+g_Light_Idensity[which_x][which_y];}
					}
				}
			}
		}
	}

	for(i=1;i<13;i++){
		Li[i]=Li[i]/Search_Range_K;
	}
	
	
	/*Arrange the Light Idensity with decrease list*/
	for(i=1;i<13;i++){
		for(j=1;j<13-i;j++){
			if(Li[Li_Array[j]]<=Li[Li_Array[j+1]]){
				Temp_Li_Array=Li_Array[j];
				Li_Array[j]=Li_Array[j+1];
				Li_Array[j+1]=Temp_Li_Array;
			}
		}
	}

	/*Save the best Li and derection*/
	for(i=1;i<=BEST_LI_QUANTITY;i++){
		g_Bud_Light_Idensity_Vec_Row[Current_Bud_Num][i-1]=Li[Li_Array[i]];
		g_Bud_Light_Idensity_Vec_Theta[Current_Bud_Num][i-1]=(F32)(2*(7-Li_Array[i])-1)/24.0*Pi;
	}
	printf("\nBud:%d[X:%d][Y:%d] L_R:[%.3f];L_T[%.1fdeg]",Current_Bud_Num,Bud_Point_X,Bud_Point_Y,g_Bud_Light_Idensity_Vec_Row[Current_Bud_Num][0],(g_Bud_Light_Idensity_Vec_Theta[Current_Bud_Num][0]+Alpha)*180.0/Pi);
	/*Check the correctness*/


}

//-----------------------------------------------------------------------------
// Name: Reference_Trans_Descartes_To_Polar
// Desc: Transfer the Descartes coordination to Polar coordination
//-----------------------------------------------------------------------------
void Reference_Trans_Descartes_To_Polar(F32 D_X,F32 D_Y,UT016 O_X,UT016 O_Y,F32 Alpha,F32 * New_P_Row_Theta)
{
	F32		New_D_X=0;
	F32		New_D_Y=0;
	F32		Row_O=0.0;
	F32		Theta_O=0.0;
//	F32		New_P[2];
	
//	New_P[0]=New_P_Row_Theta;
	/*move to the new origin point*/
	New_D_X=D_X-O_X;
	New_D_Y=D_Y-O_Y;
	/*trans to polar reference system*/
	Row_O=sqrt(New_D_X*New_D_X+New_D_Y*New_D_Y);
	
	/*Avoid devide 0*/
	if(fabs((F32)(New_D_X))<SMALL_VALUE){
		if ((F32)(New_D_X)>0)
			New_D_X=SMALL_VALUE;
		else if((F32)(New_D_X)<0)
			New_D_X=-SMALL_VALUE;
	}

	if(New_D_X>0)
		Theta_O=atan((F32)(New_D_Y)/(F32)(New_D_X));
	else if(New_D_X<0)
		Theta_O=Pi+atan((F32)(New_D_Y)/(F32)(New_D_X));
	else if(New_D_Y>0)
		Theta_O=(F32)(Pi/2);
	else if(New_D_Y<0)
		Theta_O=(F32)(-Pi/2);
	else if(New_D_Y==0)
		Theta_O=0;
	/*Rotate the polar*/
	(*(New_P_Row_Theta++))=Row_O;
	(*(New_P_Row_Theta++))=Theta_O-Alpha;
	
}

//-----------------------------------------------------------------------------
// Name: InitPlantDataArray
// Desc: Initiate the plant data arraies
//-----------------------------------------------------------------------------
void InitPlantDataArray(void)
{
	UT016 i=0,j=0;
	g_Plant_Cell_Total_Num=0;
	g_Bud_Total_Num=0;
	g_Max_Cell_Age=0;

	for(i=0;i<MAX_PLANT_CELL_NUM;i++)
	{
		g_Parents_Array[i]=0;
		g_Location_X[i]=0;
		g_Location_Y[i]=0;
	}
	for(i=0;i<MAX_BUD_NUM;i++)
	{
		g_Bud_Alive[i]=BUD_IS_ALIVE;
		g_Bud_Array[i]=0;
		g_Bud_Light_Idensity_Vec_Row[i][0]=0.0;	
		g_Bud_Light_Idensity_Vec_Theta[i][0]=0.0;
		g_Bud_Alpha[i]=0.0;
		g_Bud_Li_Growing_Vec_Row[i]=0.0;
		g_Bud_Growing_Vec_Row[i]=0.0;
		g_Bud_Growing_Vec_Theta[i]=0.0;
		g_Bud_Auxin[i]=0.0;
		g_Bud_Cell_Age[i]=0;
		g_Bud_Branch_Age[i]=0;
	}
	
}

//-----------------------------------------------------------------------------
// Name: InitLightDataArray
// Desc: Initiate the Light data arraies
//-----------------------------------------------------------------------------
void InitLightDataArray(void)
{
	UT016 i=0,j=0;

	for( i=0;i<MAP_WIDTH;i++)
		{for( j=0;j<MAP_HEIGHT;j++)
			{
				g_Light_Idensity[i][j]=0;
			}
		}
}
//-----------------------------------------------------------------------------
// Name: LoadMapData
// Desc: Load any pre-existing map when launching the program.
//-----------------------------------------------------------------------------
void LoadMapData (void)
{
	UT016 x = 0;
	UT016 y = 0;
	ifstream filein;
	filein.open(g_Map_Name,ios::nocreate,0);
	if (filein)
	{
		for (x = 1; x < MAP_WIDTH; x++){
			for (y = 1; y <MAP_HEIGHT; y++){
				filein.read(&g_Map [x][y],sizeof(g_Map [x][y]));
				if (g_Map [x][y]==UT8(1)) 
					g_Map [x][y] = CELL_IS_OBSTACLE;
				cout<<g_Map [x][y];
			}
		}
		filein.close();	
	}
	else //initialize the map to completely walkable
	{
		;
	}
}
//-----------------------------------------------------------------------------
// Name: ShowMap
// Desc: show the map in graph
//-----------------------------------------------------------------------------
void ShowMap(void)
{	
	UT016 	x = 0;
	UT016 	y = 0;
	UT016 	time=0;

	UT8		enter=13;/*Values 8, 9, 10, and 13 convert to backspace, tab, linefeed, and carriage return characters, respectively*/
	UT8		Tab=9;
	UT8		Temp=0;		
//	time=timeGetTime();

	ofstream file;
	file.open("Map.dat");
	for (x = 1; x <MAP_WIDTH; x++){
		for (y = 1; y <MAP_HEIGHT; y++){
//			if(g_Map[x+1][y+1]==CELL_IS_TARGET){
//				printf("\n[%d][%d]is Target\n",x+1,y+1);
//			}
			file.write(&g_Map [x][y],sizeof(g_Map [x][y]));
			file.write(&Tab,1);
		}
		file.write(&enter,1);
	}
	file.close();
}
//-----------------------------------------------------------------------------
// Name: ShowMap
// Desc: show the map in graph
//-----------------------------------------------------------------------------
void SaveMap(CString FileName)
{	
	UT016 	x = 0;
	UT016 	y = 0;
	UT016 	time=0;

	ofstream file;
	file.open(FileName);
	for (x = 1; x <MAP_WIDTH; x++){
		for (y = 1; y <MAP_HEIGHT; y++){
			file.write(&g_Map [x][y],sizeof(g_Map [x][y]));
		}
	}
	file.close();
}

//-----------------------------------------------------------------------------
// Name: InitMapDataArray
// Desc: Initiate the map data arraies.
//-----------------------------------------------------------------------------
void InitMapDataArray(void)
{
	UT016 i=0, j=0;
		  
	for( i=0;i<MAP_WIDTH;i++)
		{for( j=0;j<MAP_HEIGHT;j++)
			{
				g_Map[i][j]=CELL_IS_BLANK;
			}
		}
	
}
//-----------------------------------------------------------------------------
// Name: InitPathDataArray
// Desc: Initiate the path data arraies.
//-----------------------------------------------------------------------------
void InitPathDataArray(void)
{

}
