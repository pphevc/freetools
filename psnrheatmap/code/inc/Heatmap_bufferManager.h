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

/**********************************************************************************
* @fn BUFFMGR_AllocBuffer(InputParams *st_InputParams, BufferPointers *st_BuffPtrs)
*        The BUFFMGR_AllocBuffer function takes st_InputParams which holds size
*        of memory required and allocate memory to st_BuffPtrs, if allocated
*        returns success
***********************************************************************************/
int BUFFMGR_AllocBuffer(InputParams *st_InputParams, BufferPointers *st_BuffPtrs);



/***********************************************************************************
* @fn BUFFMGR_ReleaseBuffer(BufferPointers *st_BuffPtrs)
*        The BUFFMGR_ReleaseBuffer function takes structure of pointers
*        and free them all if they are valid
************************************************************************************/
int BUFFMGR_ReleaseBuffer(BufferPointers *st_BuffPtrs);
