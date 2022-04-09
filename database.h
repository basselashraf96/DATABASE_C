/*
 * database.h
 *
 *  Created on: Mar 27, 2022
 *      Author: Basel Ashraf
 */

#ifndef DATABASE_H_
#define DATABASE_H_

/***************************************************** Includes *********************************************************/
#include <stdio.h>
#include "std_types.h"

/*************************************************************************************************************************************/



/***************************************************** preprocessors *********************************************************/

#define DATABASE_ENTRIES 10

/*************************************************************************************************************************************/


/***************************************************** Function Decelerations *********************************************************/
bool SDB_isFull(void);
uint8 SDB_GetUsedSize(void);
bool SDB_AddEntry(uint8 id, uint8 year, uint8* subjects, uint8* grades);
void SDB_DeleteEntry(uint8 id);
bool SDB_ReadEntry(uint8 id, uint8* year, uint8* subjects, uint8* grades);
void SDB_GetIdList(uint8* count, uint8* list);
bool SDB_IsIdExist(uint8 ID);
/*************************************************************************************************************************************/

/******************************************************* Data Structure **************************************************************/
typedef struct SimpleDB
{
	uint8 serialId;

	uint8 Student_ID;
	uint8 Student_Year;

	uint8 Course_ID[3];
	uint8 Course_Grade[3];

}SimpleDB_t;

SimpleDB_t DB[DATABASE_ENTRIES];

/*************************************************************************************************************************************/

#endif /* DATABASE_H_ */
