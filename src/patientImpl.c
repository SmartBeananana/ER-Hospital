/**
 * @file patientImpl.c
 * @author Xiangyuan Lian
 * @date July 2018
 * @brief File containing the implementation of a patient struct
 */#include "patientAPI.h"

Patient *creatPatient()
{
    Patient *newPatient;

    newPatient = malloc(sizeof(Patient));

    newPatient->priority = -1;
    newPatient->name = NULL;
    newPatient->symptom = NULL;
    newPatient->waitingTime = -1;
    newPatient->counter = NULL;

    return newPatient;
}

void setArrivalTime(Patient *patient,double arrTime)
{
    patient->arrivalTime = arrTime;
}
