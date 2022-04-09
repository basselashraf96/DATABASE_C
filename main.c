/*
 * main.c
 *
 *  Created on: Mar 27, 2022
 *      Author: Basel Ashraf
 */

#include "database.h"




void main(void)
{
	uint8 addEntryStatus = TRUE;
	uint8 options = 0;
	uint8 studentID = 0;
	uint8 studentYear = 0;
	uint8 studentSubjects[3] = {0};
	uint8 studentGrades[3] = {0};
	uint8 serial = 0;
	uint8 listofIDs[DATABASE_ENTRIES] = {0};
	uint8 readEntryStatus = TRUE;

	/* for scanf bug doesn't accept %d because the value is uint8*/
	uint8 scannedStudentID;
	uint8 scannedStudentYear;
	uint8 scannedstudentSubjects[3];
	uint8 scannedstudentGrades[3];
	while(1)
	{
		printf("\n-------->choose option<-----------\n");
		printf("*ADD new entry(press 1)\n*GET list of students IDs(press 2)\n*DELETE an entry(press 3)\n*READ entry(press 4)\n");
		scanf("%d" , &options);

		switch(options)
		{
		case 1:
			if(addEntryStatus == FALSE)
			{
				printf("*****************************\n");
				printf("**failed** Database is full\n");
				printf("*****************************\n");
			}
			else{
				printf("enter student id\n");
				scanf("%d" ,&studentID);
				scannedStudentID = studentID;
				printf("enter student year\n");
				scanf("%d" , &studentYear);
				scannedStudentYear = studentYear;

				for(uint8 i = 0; i<3 ; i++)
				{
					printf("enter subject id[%d]\n",i+1);
					scanf("%d" , &studentSubjects[i]);
					scannedstudentSubjects[i] = studentSubjects[i];
					printf("enter grade of id[%d]\n",i+1);
					do{
					scanf("%d" , &studentGrades[i]);
					scannedstudentGrades[i] = studentGrades[i];
					}
					while(scannedstudentGrades[i] > 100);
				}

				addEntryStatus = SDB_AddEntry(scannedStudentID , scannedStudentYear , scannedstudentSubjects , scannedstudentGrades);
			}

			break;

		case 2:
			SDB_GetIdList(&serial , listofIDs);
			printf("**************************\n");
			printf("number of entries---->%d\n" , serial);

			if(serial == 0)
			{
				printf("no list to show\n\n");
				printf("**************************\n");
			}
			else
			{
				for(uint8 i = 0; i<serial ; i++)
				{
					printf("serial[%d]---->student ID is %d\n",i+1,listofIDs[i]);

				}
				printf("**************************\n");
			}
			break;

		case 3:
			printf("enter student id to delete\n");
			scanf("%d" ,&studentID);
			scannedStudentID = studentID;
			if(SDB_IsIdExist(scannedStudentID) == 1)
			{
				addEntryStatus = TRUE;
				SDB_DeleteEntry(scannedStudentID);
			}
			else
			{
				printf("*********************\n");
				printf("ID doesn't exist\n");
				printf("*********************\n");
			}
			break;

		case 4:
			printf("enter student id to search for it\n");
			scanf("%d" ,&studentID);
			scannedStudentID = studentID;
			readEntryStatus = SDB_ReadEntry(scannedStudentID , &studentYear , studentSubjects , studentGrades);
			if(readEntryStatus == FALSE)
			{
				printf("*************************************************\n");
				printf("No data to read please enter a valid student id\n");

			}
			else
			{
				printf("student year is 20%d\n" , studentYear);
				for(uint8 i = 0 ; i < 3 ; i++)
				{
					printf("subject[%d] with grade[%d]\n" ,studentSubjects[i],studentGrades[i]);
				}
				printf("*************************************************\n");
			}

			break;


		default:
			break;

		}

	}
}
