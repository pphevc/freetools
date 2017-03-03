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

#include"Heatmap_structures.h"


/*****************************************************************************
* @fn mapOverlay(unsigned char *uc_pubReconstructedY,
*               unsigned char *uc_pubReconstructedU,
*               unsigned char *uc_pubReconstructedV,
*               unsigned char *uc_pubOriginalY,
*               unsigned char *uc_pubOriginalU,
*               unsigned char *uc_pubOriginalV,
*               int           i_ImgWidth,
*               int           i_ctuWidth,
*               int           i_ctuHeight
*               )
*
*        The mapOverlay function takes pointer to Y U and V
*        of Original and Reconstructed to compute i_psnr and do i_color overlay
*
*******************************************************************************/
int mapOverlay(unsigned char *uc_pubReconstructedY,
               unsigned char *uc_pubReconstructedU,
               unsigned char *uc_pubReconstructedV,
               unsigned char *uc_pubOriginalY,
               unsigned char *uc_pubOriginalU,
               unsigned char *uc_pubOriginalV,
               int           i_ImgWidth,
               int           i_ctuWidth,
               int           i_ctuHeight
    );


/*******************************************************************************
* @fn ComputeHeatMap(InputParams   *st_InputParams,
*                   BufferPointers *st_BuffPtrs
*                   )
*
*        The ComputeHeatMap function takes structure of pointers
*        and Input parameters and call mapOverlay()
*        function with block size provided
*
*******************************************************************************/
void  ComputeHeatMap(InputParams *st_InputParams,
    BufferPointers *st_BuffPtrs
    );