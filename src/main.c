/**
 * @file main.c
 * @author Xiangyuan Lian
 * @date July 2018
 * @brief File containing the implementation of a ER hospital
 */
#include "PQAPI.h"
#include "patientAPI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SPECIALIST "TR"
#define SYMPTOM_CODE  {"CV","HN","EV","GI","MH","NC","EC","RC","SK","SA","TR"}
#define SYMPTOM_COUNT 11

void destroyData(void *data);
void printNode(void *toBePrinted);
int compare(const void *first, const void *second);
double symptomTime(char *symptom);
void removeNewLine(char *input);
void setWaitingTime(PQueue *pqueue, double finish);
void setFinishingTime(Patient *patient, double *finish, int specialFlag);
void aging(PQueue *pqueue);

int main (int argc, char **argv)
{
    FILE *fpout, *fpin;
    PQueue *normalPq, *specialPq, *generalPq;
    char *token, str[30];
    Patient *newPatient, *gpPatient, *patient;
    int i, random, numGeneral, numSpecial, numNormal, length, counter=8, normalCounter=8, specialCounter=8;
    double finish = 0.0, totalWait = 0.0, processing = 0.0, normalFinish = 0;
    double specialFinish = 0, normalTotalWait = 0.0, specialTotalWait = 0.0, roundUp;

    if(argc != 2)
    {
        printf("----Invaild Input----\n");
    }
    else
    {
        fpout = fopen(argv[1],"r");
        if(fpout == NULL)
        {
            printf("Can not open the file \n");
            exit(1);
        }
        else
        {
            normalPq = creatPQueue(100,MIN_PQ,destroyData,printNode,compare);
            specialPq = creatPQueue(100,MIN_PQ,destroyData,printNode,compare);
            generalPq = creatPQueue(100,MIN_PQ,destroyData,printNode,compare);
            if(normalPq == NULL || specialPq == NULL)
            {
                printf("Priority queue is null\n");
                return 0;
            }
            while(fgets(str,50,fpout))
            {
                newPatient = creatPatient();
                gpPatient = creatPatient();

                token = strtok(str," ");
                length = strlen(token);
                newPatient->name = malloc(sizeof(char)*length+1);
                gpPatient->name = malloc(sizeof(char)*length+1);
                strcpy(newPatient->name,token);
                strcpy(gpPatient->name,token);
                removeNewLine(newPatient->name);
                removeNewLine(gpPatient->name);

                token = strtok(NULL," ");
                newPatient->priority = atoi(token);
                gpPatient->priority = atoi(token);

                token = strtok(NULL," ");
                length = strlen(token);
                newPatient->symptom = malloc(sizeof(char)*length+1);
                gpPatient->symptom = malloc(sizeof(char)*length+1);
                strcpy(newPatient->symptom,token);
                strcpy(gpPatient->symptom,token);
                removeNewLine(newPatient->symptom);
                removeNewLine(gpPatient->symptom);

                random = rand()%(20+1-8)+8;
                setArrivalTime(newPatient,random);
                setArrivalTime(gpPatient,random);

                gpPatient->counter = &counter;

                enQueue(generalPq,gpPatient);
                if(strcmp(SPECIALIST,newPatient->symptom) == 0)
                {
                    newPatient->counter = &specialCounter;
                    enQueue(specialPq,newPatient);
                }
                else
                {
                    newPatient->counter = &normalCounter;
                    enQueue(normalPq,newPatient);
                }
            }
        }
        fclose(fpout);
    }
    numGeneral = generalPq->heap->size;
    numNormal = normalPq->heap->size;
    numSpecial = specialPq->heap->size;

    fpin = fopen("report.txt","a+");
    if(fpin == NULL)
    {
        printf("Can not open the file \n");
        exit(1);
    }

    fprintf(fpin,"*****When only GP at hospital...*****\n\n");

    while(isEmpty(generalPq) == 0)
    {
        setWaitingTime(generalPq,finish);
        patient = peek(generalPq);

        if(patient->arrivalTime >= counter || counter<=finish)
        {
            processing = symptomTime(patient->symptom);
            setFinishingTime(patient,&finish,0);
            totalWait = totalWait + patient->waitingTime;
            deQueue(generalPq);
            for(i=0; i<processing; i++)
            {
                aging(generalPq);
                counter++;
            }
            fprintf(fpin,"name:%s priority:%d %s arrive:%g wait time:%g\n\n",
                    patient->name,patient->priority,patient->symptom,patient->arrivalTime,patient->waitingTime);
            destroyData(patient);
        }
        else
        {
            counter++;
        }
    }

    fprintf(fpin,"*****When a GP and a specialist are both at hospital...*****\n\n");
    while(isEmpty(specialPq)==0 || isEmpty(normalPq)==0)
    {
        if(isEmpty(normalPq)==0 && isEmpty(specialPq)==1)
        {
            setWaitingTime(normalPq,normalFinish);
            patient = peek(normalPq);

            if(patient->arrivalTime >= normalCounter || normalCounter<=normalFinish)
            {
                processing = symptomTime(patient->symptom);
                setFinishingTime(patient,&normalFinish,0);
                normalTotalWait = normalTotalWait + patient->waitingTime;
                deQueue(normalPq);
                for(i=0; i<processing; i++)
                {
                    aging(normalPq);
                    normalCounter++;
                }
                fprintf(fpin,"name:%s priority:%d %s arrive:%g wait time:%g\n\n",
                        patient->name,patient->priority,patient->symptom,patient->arrivalTime,patient->waitingTime);
                destroyData(patient);
            }
            else
            {
                normalCounter++;
            }
        }
        else if(isEmpty(normalPq)==1 && isEmpty(specialPq)==0)
        {
            setWaitingTime(specialPq,specialFinish);
            patient = peek(specialPq);

            if(patient->arrivalTime >= normalCounter || normalCounter <= specialFinish)
            {
                processing = symptomTime(patient->symptom);
                processing = ceil(processing);
                setFinishingTime(patient,&specialFinish,0);
                specialTotalWait = specialTotalWait + patient->waitingTime;
                deQueue(specialPq);
                for(i=0; i<processing; i++)
                {
                    aging(specialPq);
                    normalCounter++;
                }
                fprintf(fpin,"name:%s priority:%d %s arrive:%g wait time:%g\n\n",
                        patient->name,patient->priority,patient->symptom,patient->arrivalTime,patient->waitingTime);
                destroyData(patient);
            }
            else
            {
                normalCounter++;
            }

            if(peek(specialPq) != NULL)
            {
                setWaitingTime(specialPq,specialFinish);
                patient = peek(specialPq);

                if(patient->arrivalTime >= specialCounter || specialCounter <= specialFinish)
                {
                    processing = symptomTime(patient->symptom) * 1.1;
                    roundUp = ceil(processing);
                    setFinishingTime(patient,&specialFinish,1);
                    specialTotalWait = specialTotalWait + patient->waitingTime;
                    deQueue(specialPq);
                    for(i=0; i<roundUp; i++)
                    {
                        aging(specialPq);
                        specialCounter++;
                    }
                    fprintf(fpin,"name:%s priority:%d %s arrive:%g wait time:%g\n\n",
                            patient->name,patient->priority,patient->symptom,patient->arrivalTime,patient->waitingTime);
                    destroyData(patient);
                }
                else
                {
                    specialCounter++;
                }
            }

        }
        if(isEmpty(normalPq)==0 && isEmpty(specialPq)==0)
        {
            setWaitingTime(normalPq,normalFinish);
            patient = peek(normalPq);

            if(patient->arrivalTime >= normalCounter || normalCounter <= normalFinish)
            {
                processing = symptomTime(patient->symptom);
                setFinishingTime(patient,&normalFinish,0);
                normalTotalWait = normalTotalWait + patient->waitingTime;
                deQueue(normalPq);
                for(i=0; i<processing; i++)
                {
                    aging(normalPq);
                    normalCounter++;
                }
                fprintf(fpin,"name:%s priority:%d %s arrive:%g wait time:%g\n\n",
                        patient->name,patient->priority,patient->symptom,patient->arrivalTime,patient->waitingTime);
                destroyData(patient);
            }
            else
            {
                normalCounter++;
            }

            setWaitingTime(specialPq,specialFinish);
            patient = peek(specialPq);

            if(patient->arrivalTime >= specialCounter || specialCounter <= specialFinish)
            {
                processing = symptomTime(patient->symptom)*1.1;
                roundUp = ceil(processing);
                setFinishingTime(patient,&specialFinish,1);
                specialTotalWait = specialTotalWait + patient->waitingTime;
                deQueue(specialPq);
                for(i=0; i<roundUp; i++)
                {
                    aging(specialPq);
                    specialCounter++;
                }
                fprintf(fpin,"name:%s priority:%d %s arrive:%g wait time:%g\n\n",
                        patient->name,patient->priority,patient->symptom,patient->arrivalTime,patient->waitingTime);
                destroyData(patient);
            }
            else
            {
                specialCounter++;
            }
        }
    }

    fprintf(fpin,"------------Conclusion-----------\n");
    double aveGPOnlyWaiting = 0, aveTwoDocWaiting = 0;

    if(numGeneral != 0)
    {
        aveGPOnlyWaiting = totalWait / numGeneral;
    }

    if(numNormal != 0 || numSpecial != 0)
    {
        aveTwoDocWaiting = (specialTotalWait+normalTotalWait)/(numNormal+numSpecial);
    }

    fprintf(fpin,"\nThe average waiting time of GP only: %g\n",aveGPOnlyWaiting);
    fprintf(fpin,"\nThe average waiting time of GP and a specialist: %g\n",aveTwoDocWaiting);

    destroy(generalPq);
    destroy(normalPq);
    destroy(specialPq);
    fclose(fpin);

    return 0;
}

void destroyData(void *toBeDeleted)
{
    free(((Patient *)toBeDeleted)->name);
    free(((Patient *)toBeDeleted)->symptom);
    free(toBeDeleted);
}

int compare(const void *first,const void *second)
{
    Patient *p1, *p2;
    int firstPriority, secondPriority;

    p1 = ((Patient*)first);
    p2 = ((Patient*)second);

    firstPriority = p1->priority;
    secondPriority = p2->priority;

    if(firstPriority == secondPriority)
    {
        firstPriority = (int)(p1->arrivalTime * 10.0);
        secondPriority = (int)(p2->arrivalTime *10.0);
    }

    return firstPriority - secondPriority;
}

void printNode(void *toBePrinted)
{
    printf("%s %d %s\n", ((Patient*)toBePrinted)->name,
                       ((Patient*)toBePrinted)->priority,
                       ((Patient*)toBePrinted)->symptom);
}

double symptomTime(char *symptom)
{
    int i, length;
    char *array[] = SYMPTOM_CODE;

    for (i=0; i<SYMPTOM_COUNT; i++)
    {
        if(strcmp(array[i],symptom) == 0)
        {
            length = i*3+6;
        }
    }
    return length;
}

void removeNewLine(char *input)
{
    int length;

    length = strlen(input);

    if(input[length-1] == '\n')
    {
        input[length-1] = '\0';
    }
}

void setWaitingTime(PQueue *pqueue,double finish)
{
    if(pqueue== NULL)
    {
        return;
    }
    int i, temp;

    temp = pqueue->heap->size;
    for(i=0; i<temp; i++)
    {
        ((Patient *)(pqueue->heap->array[i]->data))->waitingTime = finish -((Patient *) (pqueue->heap->array[i]->data))->arrivalTime;

        if(((Patient *)(pqueue->heap->array[i]->data))->waitingTime<0)
        {
            ((Patient *)(pqueue->heap->array[i]->data))->waitingTime = 0;
        }
    }
}

void setFinishingTime(Patient *patient, double *finish, int specialFlag)
{
    if(patient == NULL)
    {
        return;
    }

    double processing;

    if(specialFlag == 1)
    {
        processing = symptomTime(patient->symptom) * 1.1;
    }
    else
    {
        processing = symptomTime(patient->symptom);
    }

    if(patient->arrivalTime < *finish)
    {
        *finish = *finish + processing;
    }
    else
    {
        *finish = patient->arrivalTime + processing;
    }
}

void aging(PQueue *pqueue)
{
    if(pqueue== NULL)
    {
        return;
    }
    int i, temp, upgrade;
    Patient *patient;

    temp = pqueue->heap->size;
    for(i=0; i<temp; i++)
    {
        patient = pqueue->heap->array[i]->data;

        if(*(patient->counter)>((int)(patient->arrivalTime)))
        {
            upgrade = (*(patient->counter) -((int)(patient->arrivalTime))) % 60;
            if (upgrade == 0)
            {
                if(((Patient *)(pqueue->heap->array[i]->data))->priority > 1 )
                {
                    ((Patient *)(pqueue->heap->array[i]->data))->priority--;
                    heapifyup(pqueue->heap,i);
                }
            }
        }
    }
}
