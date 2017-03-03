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

#include"Heatmap_performOverlay.h"

/*************************************************************************************
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
* @brief The mapOverlay function takes pointer to Y U and V
*        of Original and Reconstructed to compute psnr and do color overlay
*        based on psnr
*
* @param uc_pubReconstructedY : Pointer to Luma of Reconstructed
* @param uc_pubReconstructedU : Pointer to Chroma(cb) of Reconstructed
* @param uc_pubReconstructedV : Pointer to Chroma(cr) of Reconstructed
* @param uc_pubOriginalY      : Pointer to Luma of Orig
* @param uc_pubOriginalU      : Pointer to Chroma(cb) of Orig
* @param uc_pubOriginalV      : Pointer to Chroma(cr) of Orig
* @param i_ImgWidth           : Input image width
* @param i_ctuWidth           : width of block
* @param i_ctuHeight          : Height of block
*
* @return status
*
**************************************************************************************/
int mapOverlay(unsigned char *uc_pubReconstructedY,
               unsigned char *uc_pubReconstructedU,
               unsigned char *uc_pubReconstructedV,
               unsigned char *uc_pubOriginalY,
               unsigned char *uc_pubOriginalU,
               unsigned char *uc_pubOriginalV,
               int           i_ImgWidth,
               int           i_ctuWidth,
               int           i_ctuHeight
    )
{
  unsigned char *uc_pReconstructed, *uc_pOriginal;
    int i_row, i_col, i_ImgSize = 0;
    int i_ctu_width = i_ctuWidth;
    int i_ctu_height = i_ctuHeight;
    double d_sumOfDiff_Y = 0;
    double d_diffOfOriginalReconstructedPixel = 0;
    double d_i_psnr_Y = 0;
    int i_psnr = 0; /*To store int of d_i_psnr_Y*/
    i_ImgSize = i_ctu_width*i_ctu_height;
    unsigned char nOverlay_V[] = { 0x00, 0x09, 0x12, 0x1B, 0x24, 0x2D, 0x36, 0x3F, 0x48, 0x51, 0x5A, 0x63, 0x6C, 0x75, 0x7E, 0x87, 0x90, 0x99, 0xA2, 0xAB, 0xB4, 0xBD, 0xC6, 0xCF, 0xD8, 0xE1, 0xEA, 0xF3, 0xFC };
    unsigned char nOverlay_U = 0x00;
    
    /*Compute d_sumOfDiff_Y */
    for (i_row = 0; i_row < i_ctu_height; i_row++)
    {
      uc_pReconstructed = uc_pubReconstructedY + i_row*i_ImgWidth;
      uc_pOriginal = uc_pubOriginalY + i_row*i_ImgWidth;
        for (i_col = 0; i_col< (i_ctu_width); i_col++)
        {
          d_diffOfOriginalReconstructedPixel = abs(*uc_pReconstructed - *uc_pOriginal);
          d_sumOfDiff_Y += (d_diffOfOriginalReconstructedPixel * d_diffOfOriginalReconstructedPixel);
            uc_pReconstructed++;
            uc_pOriginal++;
        }
    }

    if (d_sumOfDiff_Y == 0)
    {
        d_sumOfDiff_Y = 0.1;
    }

    /*Compute psnr_Y*/
    d_i_psnr_Y = (double)(10 * log10((double)(255 * 255) / (double)(d_sumOfDiff_Y / (i_ImgSize))));
    i_psnr = (int)d_i_psnr_Y;

    /*Overlay cr*/
    for (i_row = 0; i_row < (i_ctu_height >> 1); i_row++)
    {
      uc_pOriginal = uc_pubOriginalV + i_row*(i_ImgWidth >> 1);
        for (i_col = 0; i_col< (i_ctu_width >> 1); i_col++)
        {
            if (i_psnr>52)
            {
              *uc_pOriginal = nOverlay_V[0];
              uc_pOriginal++;
            }
            else if (i_psnr < 24)
            {
              *uc_pOriginal = nOverlay_V[28];
              uc_pOriginal++;
            }
            else
            {
              *uc_pOriginal = nOverlay_V[abs(i_psnr - 52)];
              uc_pOriginal++;
            }
        }
    }

    /*Overlay cb */
    for (i_row = 0; i_row < (i_ctu_height >> 1); i_row++)
    {
      uc_pOriginal = uc_pubOriginalU + i_row*(i_ImgWidth >> 1);
        for (i_col = 0; i_col< (i_ctu_width >> 1); i_col++)
        {
          *uc_pOriginal = nOverlay_U;
          uc_pOriginal++;
        }
    }
    return 1;
}

/************************************************************************************
* @fn ComputeHeatMap(InputParams    *st_InputParams,
*                    BufferPointers *st_BuffPtrs
*                   )
*
*
* @brief The ComputeHeatMap function takes structure of pointers
*        and Input parameters and call mapOverlay()
*        function with block size provided
*
* @param st_InputParams : Input parameters
* @param st_BuffPtrs    : Pointer to structure having all buffer pointer
*
* @return status
*
*************************************************************************************/
void  ComputeHeatMap(InputParams *st_InputParams,
    BufferPointers *st_BuffPtrs
    )
{
    int i_imgPos_X;
    int i_imgPos_Y;
    int i_ImgWidth = st_InputParams->i_ImgWidth;
    int i_ImgHeight = st_InputParams->i_ImgHeight;
    unsigned char  *uc_pubReconstructedY = st_BuffPtrs->uc_Reconstructed_Y;
    unsigned char  *uc_pubReconstructedU = st_BuffPtrs->uc_Reconstructed_U;
    unsigned char  *uc_pubReconstructedV = st_BuffPtrs->uc_Reconstructed_V;
    unsigned char  *uc_pubOriginalY = st_BuffPtrs->uc_Original_Y;
    unsigned char  *uc_pubOriginalU = st_BuffPtrs->uc_Original_U;
    unsigned char  *uc_pubOriginalV = st_BuffPtrs->uc_Original_V;

    int i_ctuHgt = st_InputParams->i_BlkSize;
    int i_ctuWdth = st_InputParams->i_BlkSize;

    for (i_imgPos_Y = 0; i_imgPos_Y < i_ImgHeight; i_imgPos_Y += st_InputParams->i_BlkSize)
    {
        if ((i_ImgHeight - i_imgPos_Y) < i_ctuHgt)
        {
            /*if frames is not in blksize*blksize we need to calculate height of last row*/
            i_ctuHgt = (i_ImgHeight - i_imgPos_Y);
        }
        uc_pubReconstructedY = st_BuffPtrs->uc_Reconstructed_Y + (i_imgPos_Y * i_ImgWidth);
        uc_pubReconstructedU = st_BuffPtrs->uc_Reconstructed_U + ((i_imgPos_Y >> 1)*(i_ImgWidth >> 1));
        uc_pubReconstructedV = st_BuffPtrs->uc_Reconstructed_V + ((i_imgPos_Y >> 1)*(i_ImgWidth >> 1));
        uc_pubOriginalY = st_BuffPtrs->uc_Original_Y + (i_imgPos_Y* i_ImgWidth);
        uc_pubOriginalU = st_BuffPtrs->uc_Original_U + ((i_imgPos_Y >> 1)*(i_ImgWidth >> 1));
        uc_pubOriginalV = st_BuffPtrs->uc_Original_V + ((i_imgPos_Y >> 1)*(i_ImgWidth >> 1));

        for (i_imgPos_X = 0; i_imgPos_X < i_ImgWidth; i_imgPos_X += st_InputParams->i_BlkSize)
        {
            if ((i_ImgWidth - i_imgPos_X) < i_ctuWdth)
            {
                /*if frames is not in blksize*blksize we need to calculate width of last col*/
                i_ctuWdth = (i_ImgWidth - i_imgPos_X);
            }
            mapOverlay(uc_pubReconstructedY, uc_pubReconstructedU, uc_pubReconstructedV, uc_pubOriginalY, uc_pubOriginalU, uc_pubOriginalV, i_ImgWidth, i_ctuWdth, i_ctuHgt);
            uc_pubReconstructedY = uc_pubReconstructedY + (i_ctuWdth);
            uc_pubReconstructedU = uc_pubReconstructedU + (i_ctuWdth >> 1);
            uc_pubReconstructedV = uc_pubReconstructedV + (i_ctuWdth >> 1);
            uc_pubOriginalY = uc_pubOriginalY + (i_ctuWdth);
            uc_pubOriginalU = uc_pubOriginalU + (i_ctuWdth >> 1);
            uc_pubOriginalV = uc_pubOriginalV + (i_ctuWdth >> 1);

        }
        i_ctuHgt = st_InputParams->i_BlkSize;
        i_ctuWdth = st_InputParams->i_BlkSize;
    }
}
