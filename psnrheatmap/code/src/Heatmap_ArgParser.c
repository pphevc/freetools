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

#include"Heatmap_ArgParser.h"



/*****************************************************************************
* @fn ParseCommandArgs(int         argc,
*                      char        *argv[],
*                      InputParams *st_InputParams)
*
* @brief The ParseCommandArgs function takes number of argument to
*        be read, Argumentlist and input params where arguments will be stored
*
* @param argc           : Number of argument
* @param argv           : Array containg arguments
* @param st_InputParams : structure where arguments will be stored
*
* @return status
*
******************************************************************************/
int ParseCommandArgs(int argc, char *argv[], InputParams *st_InputParams)
{
    if (argc<13)
    {
        printf("Insufficient argument provided\n");
        return 1;
    }
    int i_cmdIterator;
    for (i_cmdIterator = 1; i_cmdIterator<argc; i_cmdIterator++)
    {
        if (*argv[i_cmdIterator] == '-')
        {
            switch (*(++argv[i_cmdIterator]))
            {
            case 'r':
            case 'R':
                strcpy(st_InputParams->c_InputRef, (argv[++i_cmdIterator]));
                break;

            case 'o':
            case 'O':
              strcpy(st_InputParams->c_InputOriginal, (argv[++i_cmdIterator]));
                break;

            case 'w':
            case 'W':
                st_InputParams->i_ImgWidth = atoi(argv[++i_cmdIterator]);
                break;

            case 'h':
            case 'H':
                st_InputParams->i_ImgHeight = atoi(argv[++i_cmdIterator]);
                break;

            case 'f':
            case 'F':
                st_InputParams->i_NoOfFrames = atoi(argv[++i_cmdIterator]);
                if (st_InputParams->i_NoOfFrames<1)
                {
                    printf("Number of frames must be greater than 1\n");
                    return 1;
                }
                break;

            case 'b':
            case 'B':
                st_InputParams->i_BlkSize = atoi(argv[++i_cmdIterator]);
                if (st_InputParams->i_BlkSize < 2 || (st_InputParams->i_BlkSize % 2) != 0)
                {
                    printf("Block size sholud be 2xN ( NOTE : N!=0 )\n");
                    return 1;
                }
                break;

            default:
            {
                printf("-r Reconstructed file path\n");
                printf("-o Original file path\n");
                printf("-w Width of file\n");
                printf("-h Height of file\n");
                printf("-f Number of frames\n");
                printf("-b block size(Even number)\n");
                printf("Example HeatMap.exe -r Reconstructed_file.yuv -o Original_file.yuv -w 1920 -h 1080 -f 99 -b 16\n");
                return 1;
            }
            }
        }
    }
    return 0;
}