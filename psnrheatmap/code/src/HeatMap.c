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

#include"Heatmap_bufferManager.h"
#include"Heatmap_ArgParser.h"
#include"Heatmap_performOverlay.h"


/*****************************************************************************
* @fn main(int argc, char *argv[])
*
* @brief Main function calling function to do color overlay
*
* @param argc : Argument count
*
* @param argv : Argument vector
*
* @return None
*****************************************************************************/
int main(int argc, char *argv[])
{
    /*check if no argument is given*/
    if (argc == 1)
    {
      printf("\nSample Use: HeatMap.exe -r Reconstructed_file.yuv -o Original_file.yuv -w inputWidth -h inputHeight -f noOfFrames -b blockSize\n");
      return 1;
    }
    char  c_Output[MAX_FILE_NAME] = { '\0' };
    InputParams st_InputParams;
    BufferPointers st_BuffPtrs;
    int i_ImgSize;

    /*Parse command line argument*/
    if (ParseCommandArgs(argc, argv, &st_InputParams) == 1)
    {
        return 1;
    }

    /*Open Input refrence stream*/
    FILE *fp_InputReconstructed = fopen(st_InputParams.c_InputRef, "rb");
    if (!fp_InputReconstructed)
    {
        printf("Unable to open Reconstructed stream\n");
        return 1;
    }

    /*Open Input Original stream*/
    FILE *fp_InputOriginal = fopen(st_InputParams.c_InputOriginal, "rb");
    if (!fp_InputOriginal)
    {
        printf("Unable to open Original stream\n");
        return 1;
    }


    /*Open Output stream(add OVERLAY to Reconstructed stream to show output stream)*/
    strncpy(c_Output, st_InputParams.c_InputRef, strlen(st_InputParams.c_InputRef) - 4);
    strcat(c_Output, "_OVERLAY.yuv"); /*output file name*/
    FILE *fp_Output = fopen(c_Output, "wb");
    if (!fp_Output)
    {
        printf("Unable to open Out File\n");
        return 1;
    }
    i_ImgSize = st_InputParams.i_ImgHeight*st_InputParams.i_ImgWidth;

    /*Memory allocation*/
    if (BUFFMGR_AllocBuffer(&st_InputParams, &st_BuffPtrs) == 1)
    {
        printf("Unable to allocate memory\n");
        return 1;
    }

    /*Call function to overlay for each frame*/
    for (int frame = 0; frame < st_InputParams.i_NoOfFrames; frame++)
    {
        /*Read Rcon stream*/
      fread(st_BuffPtrs.uc_Reconstructed_Y, 1 , i_ImgSize* sizeof(unsigned char), fp_InputReconstructed);
      fread(st_BuffPtrs.uc_Reconstructed_U, 1 , (i_ImgSize >> 2)* sizeof(unsigned char), fp_InputReconstructed);
      fread(st_BuffPtrs.uc_Reconstructed_V, 1 , (i_ImgSize >> 2)* sizeof(unsigned char), fp_InputReconstructed);

        /*Read Original stream*/
      fread(st_BuffPtrs.uc_Original_Y, 1 , i_ImgSize* sizeof(unsigned char), fp_InputOriginal);
      fread(st_BuffPtrs.uc_Original_U, 1 , (i_ImgSize >> 2)* sizeof(unsigned char), fp_InputOriginal);
      fread(st_BuffPtrs.uc_Original_V, 1 , (i_ImgSize >> 2)* sizeof(unsigned char), fp_InputOriginal);

        /*Calling function to do color overlay*/
        ComputeHeatMap(&st_InputParams, &st_BuffPtrs);

        /*Write Overlayed stream to file*/
        fwrite(st_BuffPtrs.uc_Original_Y, 1 , i_ImgSize* sizeof(unsigned char), fp_Output);
        fwrite(st_BuffPtrs.uc_Original_U, 1 , (i_ImgSize >> 2)* sizeof(unsigned char), fp_Output);
        fwrite(st_BuffPtrs.uc_Original_V, 1 , (i_ImgSize >> 2)* sizeof(unsigned char), fp_Output);
        printf("  Frame %3d\n", frame + 1);
    }

    /*Memory Deallocation*/
    if (BUFFMGR_ReleaseBuffer(&st_BuffPtrs) == 0)
    {
        printf("Error in memory Deallocation\n");
        return 0;
    }


    /*Close File*/
    if (fp_InputReconstructed)
    {
      fclose(fp_InputReconstructed);
    }
    if (fp_InputOriginal)
    {
      fclose(fp_InputOriginal);
    }
    if (fp_Output)
    {
        fclose(fp_Output);
    }
    return 1;
}