/*
 * database.c
 *
 *  Created on: Mar 27, 2022
 *      Author: Basel Ashraf
 */
#include "database.h"

bool SDB_isFull(void)
{
	/* 1- Check if the database is full
	 * 2- return 1 if the database is full, otherwise 0
	 */

	if(DB[DATABASE_ENTRIES-1].serialId  == DATABASE_ENTRIES) //gets the last serial id if it equals the database limit then the database is full because serial id increments every data entry
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

uint8 SDB_GetUsedSize(void)
{
	/* 1- get the number of the entries in the database
	 * 2- return the number of entries
	 */

	uint8 max=0;

	for(uint8 i = 0; i<DATABASE_ENTRIES ; i++) //gets the last serial id added because it equals to the used size
	{
		if(DB[i].serialId >= max)
		{
			max = DB[i].serialId;

		}

	}
	if(max == 0)
	{
		return 0;
	}
	else
	{
		return max;
	}
}
bool SDB_AddEntry(uint8 id, uint8 year, uint8* subjects, uint8* grades)
{

	/* 1- add new entry to the database
	 * 2- return 1 if the new entry is successfully added; otherwise 0
	 * 3- input parameters [student id, student year, pointer to 3 subject IDs,
	 * -  pointer to 3 grades]
	 * 4- the allowed range of the grade is only from 0 to 100
	 * 5- assume that the caller will always provide the 3 subjects with their grades
	 */
	if(SDB_IsIdExist(id))
	{
		printf("ID already exist");
		return 0 ;
	}
	uint8 usedSize = SDB_GetUsedSize();


	if(SDB_isFull() == 1) //if database is full
	{
		return 0;

	}

	else if(usedSize == 0) //first entry
	{
		DB[0].serialId=1;

		DB[0].Student_ID = id;
		DB[0].Student_Year = year;
		for(uint8 i = 0; i<3 ; i++)
		{
			DB[0].Course_ID[i] = subjects[i];
			DB[0].Course_Grade[i]= grades[i];
		}

	}
	else
	{

		DB[usedSize].serialId = DB[usedSize-1].serialId +1; //increment serial by 1 from its previous value ex: 1--->2--->3
		//prev->next
		DB[usedSize].Student_ID = id;																		//		prev->next
		DB[usedSize].Student_Year = year;
		for(uint8 i = 0; i<3 ; i++)
		{
			DB[usedSize].Course_ID[i] = subjects[i];
			DB[usedSize].Course_Grade[i]= grades[i];
		}
	}
	return 1;

}
void SDB_DeleteEntry(uint8 id)
{
	/* 1- delete the entry with the given ID
	 * 2- ID of the entry to be deleted
	 */
	uint8 i = 0;
	uint8 j = 0;
	uint8 k = 0;

	while(DB[i].serialId != 0)
	{
		if(DB[i].Student_ID == id)
		{
			j=i;

			while(j<DATABASE_ENTRIES)
			{
				k=0;

				if(DB[j+1].serialId == 0)
				{
					DB[j].serialId = DB[j+1].serialId; //only overwrite last serial with 0
				}
				else
				{

				}

				/*shift current value with the next one */
				DB[j].Student_ID = DB[j+1].Student_ID;
				DB[j].Student_Year = DB[j+1].Student_Year;

				while(k<3){
					DB[j].Course_ID[k] = DB[j+1].Course_ID[k]; //copy arrays
					DB[j].Course_Grade[k] = DB[j+1].Course_Grade[k];
					k++;
				}
				j++;
			}

		}
		i++;
	}



}
bool SDB_ReadEntry(uint8 id, uint8* year, uint8* subjects, uint8* grades)
{
	/* 1- read an entry matching the provided ID
	 * 2- return 1 if the entry exist, otherwise 0
	 * 3- input parameters[student ID, pointer to the student year, pointer to subjects, pointer to the grades]
	 */
	uint8 i = 0;
	uint8 k = 0;
	uint8 usedSize = SDB_GetUsedSize();
	if(usedSize == 0 ) //if no data entry exit with 0 value
	{
		return 0;
	}
	else if (SDB_IsIdExist(id) == 1)
	{
		while(DB[i].serialId != 0) //loop with database serial id
		{
			if(DB[i].Student_ID == id)//search with student id
			{
				*year = DB[i].Student_Year;
				while(k<3)
				{
					subjects[k] = DB[i].Course_ID[k];
					grades[k] = DB[i].Course_Grade[k];
					k++;
				}
				return 1;
			}
			i++;
		}
	}
	else
	{
		return 0; // if non existing id exit with 0 value.
	}
}
void SDB_GetIdList(uint8* count, uint8* list)
{
	/* 1- get the list of the IDs of the students
	 * output parameters [pointer to the number of entries currently exists in the database, pointers to the list IDs
	 */
	uint8 i =0;
	if(DB[0].serialId == 0)
	{
		*count = 0;
	}
	else
	{
		while(DB[i].serialId != 0)
		{
			*count = DB[i].serialId;
			list[i] = DB[i].Student_ID;
			i++;
		}
	}

}
bool SDB_IsIdExist(uint8 ID)
{
	/* 1- checks if the provided students ID exists
	 * 2- returns 1 if ID exists in the database, otherwise 0
	 */
	uint8 i =0;
	while(DB[i].serialId != 0)
	{
		if(ID == DB[i].Student_ID)
		{
			return 1;
		}
		i++;
	}
	return 0;

}
