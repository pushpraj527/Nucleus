  
/*
 * Copyright 2019-present Infosys Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
/**************************************
 * detachWfDelSessionResp.cpp
 * This is an auto generated file.
 * Please do not edit this file.
 * All edits to be made through template source file
 * <TOP-DIR/scripts/SMCodeGen/templates/stateMachineTmpls/state.cpp.tt>
 **************************************/

#include "mmeSmDefs.h"
#include "actionTable.h"
#include "actionHandlers/actionHandlers.h"

#include "mmeStates/detachWfDelSessionResp.h"

using namespace mme;
using namespace SM;

/******************************************************************************
* Constructor
******************************************************************************/
DetachWfDelSessionResp::DetachWfDelSessionResp():State(detach_wf_del_session_resp)
{
}

/******************************************************************************
* Destructor
******************************************************************************/
DetachWfDelSessionResp::~DetachWfDelSessionResp()
{
}

/******************************************************************************
* creates and returns static instance
******************************************************************************/
DetachWfDelSessionResp* DetachWfDelSessionResp::Instance()
{
        static DetachWfDelSessionResp state;
        return &state;
}

/******************************************************************************
* initializes eventToActionsMap
******************************************************************************/
void DetachWfDelSessionResp::initialize()
{
        {
                ActionTable actionTable;
                actionTable.addAction(&ActionHandlers::process_del_session_resp);
                actionTable.addAction(&ActionHandlers::detach_accept_to_ue);
                eventToActionsMap.insert(pair<uint16_t, ActionTable>(DEL_SESSION_RESP_FROM_SGW, actionTable));
        }
}
