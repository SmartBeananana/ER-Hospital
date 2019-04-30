/**
 * @file patientAPI.h
 * @author Xiangyuan Lian
 * @date July 2018
 * @brief File containing function definitions of patient struct
 */
#ifndef _PATIENT_
#define _PATIENT_

#include <stdio.h>
#include <stdlib.h>

/**
 *Patient typedef for a patient
**/
typedef struct patientStruct{
    int priority;
    char *name;
    char *symptom;
    double arrivalTime;
    double waitingTime;
    int *counter;
}Patient;

/**
*Function allocate memory to the patient struct and point the struct the appropriate function.
*@return pointer the patient
**/
Patient *creatPatient();

/**
*Function to set the arrival time for patient
*@pre the patient must exist
*@para pointer to the patient
*@para variable to hold the arrival time
**/

void setArrivalTime(Patient *patient,double arrTime);

#endif
