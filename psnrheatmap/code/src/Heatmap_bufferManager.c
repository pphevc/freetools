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



/*****************************************************************************
* @fn BUFFMGR_AllocBuffer(InputParams    *st_InputParams,
*                         BufferPointers *st_BuffPtrs)
*
* @brief Implementation of buffer manager that allocates memory
*        The BUFFMGR_AllocBuffer function takes st_InputParams which
*        holds size of memory required and allocate memory to st_BuffPtrs
*
* @param st_InputParams : Input parameters
* @param st_BuffPtrs    : Buffer pointer
*
* @return status
*
******************************************************************************/
int BUFFMGR_AllocBuffer(InputParams *st_InputParams, BufferPointers *st_BuffPtrs)
{
    int i_ImgSize = st_InputParams->i_ImgHeight*st_InputParams->i_ImgWidth;

    st_BuffPtrs->uc_Reconstructed_Y = (unsigned char *)malloc(i_ImgSize*sizeof(unsigned char));

    st_BuffPtrs->uc_Reconstructed_U = (unsigned char *)malloc((i_ImgSize >>2)*sizeof(unsigned char));

    st_BuffPtrs->uc_Reconstructed_V = (unsigned char *)malloc((i_ImgSize >>2)*sizeof(unsigned char));

    st_BuffPtrs->uc_Original_Y = (unsigned char *)malloc(i_ImgSize*sizeof(unsigned char));

    st_BuffPtrs->uc_Original_U = (unsigned char *)malloc((i_ImgSize >>2)*sizeof(unsigned char));

    st_BuffPtrs->uc_Original_V = (unsigned char *)malloc((i_ImgSize >>2)*sizeof(unsigned char));

    if (st_BuffPtrs->uc_Reconstructed_Y && st_BuffPtrs->uc_Reconstructed_U &&
        st_BuffPtrs->uc_Reconstructed_V && st_BuffPtrs->uc_Original_Y &&
        st_BuffPtrs->uc_Original_U && st_BuffPtrs->uc_Original_V)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


/*****************************************************************************
* @fn BUFFMGR_ReleaseBuffer(BufferPointers *st_BuffPtrs)
*
* @brief Implementation of buffer manager that releases allocated memory
*
*        The BUFFMGR_ReleaseBuffer function takes structure of pointers
*        and free them all if they are valid
*
* @param st_BuffPtrs   : Pointer to structure having all buffer pointer
*
* @return status
*
******************************************************************************/
int BUFFMGR_ReleaseBuffer(BufferPointers *st_BuffPtrs)
{
  if (st_BuffPtrs->uc_Reconstructed_Y && st_BuffPtrs->uc_Reconstructed_U &&
      st_BuffPtrs->uc_Reconstructed_V && st_BuffPtrs->uc_Original_Y &&
      st_BuffPtrs->uc_Original_U && st_BuffPtrs->uc_Original_V)
    {
      free(st_BuffPtrs->uc_Reconstructed_Y);

      free(st_BuffPtrs->uc_Reconstructed_U);

      free(st_BuffPtrs->uc_Reconstructed_V);

      free(st_BuffPtrs->uc_Original_Y);

      free(st_BuffPtrs->uc_Original_U);

      free(st_BuffPtrs->uc_Original_V);
        return 1;
    }
    else
    {
        return 0;
    }
}