#ifndef CREATESHAPE1_H
#define CREATESHAPE1_H

#include "MACROS.h"
#include "Globals.h"

#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;


char* CreateBigSphere(const int volWidth,
                   const int volHeight,
                   const int volDepth);

char* CreateBigSphere(const int volWidth,
                   const int volHeight,
                   const int volDepth)
{
    // 3D spatial array
    char*** pData_3D;
    pData_3D = (char***) malloc(sizeof(char**) * volWidth);
    for (int i = 0; i < volWidth; i++)
    {
        pData_3D[i] = (char**) malloc(sizeof(char*) * volHeight);

        for(int j = 0; j < volHeight; j++)
            pData_3D[i][j] = (char*) malloc(sizeof(char) * volDepth);
    }

    const int volumeSize = volWidth * volHeight * volDepth;
    char* pData_1D = (char*) malloc (sizeof(char) * volumeSize);

    for (int i = -volWidth/2; i < volWidth/2; i++)
        for (int j = -volHeight/2; j < volHeight/2; j++)
            for (int k = -volDepth/2; k < volDepth/2; k++)
            {
                // Vector XYZ length
                float pVector = sqrt((i * i) + (j * j) + (k * k));

                // Sphere radius
                float sRadius = volWidth / 2;

                if (pVector < sRadius)
                    pData_3D[i + volWidth / 2]
                            [j + volHeight / 2]
                            [k + volDepth / 2] = 150;
                else
                    pData_3D[i + volWidth / 2]
                            [j + volHeight / 2]
                            [k + volDepth / 2] = 0;
            }
    int index = 0 ;
    for (int i = 0; i < volWidth; i++)
        for (int j = 0; j < volHeight; j++)
            for (int k = 0; k < volDepth; k++)
            {
                pData_1D[index] = pData_3D[i][j][k];
                index++;
            }

    // Free the 3D array
    for (int i = 0; i < volWidth; i++)
    {
        for (int j = 0; j < volHeight; j++)
        {
            free(pData_3D[i][j]);
        }
        free(pData_3D[i]);
    }
    free(pData_3D);

    return pData_1D;
}

#endif // CREATESHAPE1_H
