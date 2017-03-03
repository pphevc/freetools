/***************************************************************************
* Copyright (C) 2017 PathPartner Technology 
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
***************************************************************************/

#ifndef HEATMAP_STRUCTURES_H
#define HEATMAP_STRUCTURES_H
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX_FILE_NAME 256

/*****************************************************************************
*@struct InputParams
*
*@brief Structure with input parameters as member variable
*
******************************************************************************/
typedef struct
{
    /*Input stream name(Original)*/
  char c_InputOriginal[MAX_FILE_NAME];

    /*Input stream name(Reconstructed)*/
    char  c_InputRef[MAX_FILE_NAME];

    /*Width of input stream*/
    int i_ImgWidth;

    /*Height of input stream*/
    int i_ImgHeight;

    /*Number of frames to be processed*/
    int i_NoOfFrames;

    /*Number of pixel in x and y Direction */
    int i_BlkSize;
}InputParams;


/*****************************************************************************
*@struct BufferPointers
*
*@brief Structure with pointers to luma and chroma of Original and Reconstructed
*
******************************************************************************/
typedef struct
{
    /*Pointer to Luma of Reconstructed*/
  unsigned char *uc_Reconstructed_Y;

    /*Pointer to Chroma(cb) of Reconstructed*/
  unsigned char *uc_Reconstructed_U;

    /*Pointer to Chroma(cr) of Reconstructed*/
  unsigned char *uc_Reconstructed_V;

    /*Pointer to Luma of Original*/
  unsigned char *uc_Original_Y;

    /*Pointer to Chroma(cb) of Original*/
  unsigned char *uc_Original_U;

    /*Pointer to Chroma(cr) of Original*/
  unsigned char *uc_Original_V;
}BufferPointers;

#endif
