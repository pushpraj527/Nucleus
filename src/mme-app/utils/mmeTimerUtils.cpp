/*
 * Copyright 2020-present Infosys Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <utils/mmeTimerUtils.h>
#include <controlBlock.h>
#include <contextManager/subsDataGroupManager.h>
#include <eventMessage.h>
#include "mme_app.h"
#include <mmeSmDefs.h>
#include <timeoutManager.h>
#include <timerQueue.h>
#include <utils/mmeTimerTypes.h>

using namespace mme;
using namespace cmn;

TimerContext* MmeTimerUtils::startTimer( uint32_t durationMs,
        uint32_t ueIdx,
        uint16_t timerType,
        uint16_t timerId)
{
    MmeUeTimerContext* timerCtxt = NULL;
    
    TimeoutManager &timeoutMgr =
    		static_cast<TimeoutManager&>(
    	    			compDb.getComponent(TimeoutManagerCompId));

    CTime duration(durationMs);
    CTime expiryTime;
    expiryTime = expiryTime + duration;
    
    timerCtxt = new MmeUeTimerContext(
                ueIdx, timerType, timerId, expiryTime);
    
    timeoutMgr.startTimer(timerCtxt);
    
    log_msg(LOG_DEBUG,
                "Timer started. duration %d", durationMs);
    return timerCtxt;
}

uint32_t MmeTimerUtils::stopTimer(TimerContext* timerCtxt)
{
    uint32_t rc = 0;

    TimeoutManager &timeoutMgr =
    		static_cast<TimeoutManager&>(
    				compDb.getComponent(TimeoutManagerCompId));

    if (timerCtxt != NULL)
    {
        rc = timeoutMgr.cancelTimer(timerCtxt);
        if (rc > 0)
        {
            log_msg(LOG_DEBUG, "Timer deleted\n");
            delete timerCtxt;
        }
    }
    return rc;
}

void MmeTimerUtils::onTimeout(TimerContext* timerCtxt)
{
    MmeUeTimerContext* mmeTimerCtxt = static_cast<MmeUeTimerContext *>(timerCtxt);
    if (mmeTimerCtxt == NULL)
    {
        return;
    }

    ControlBlock* controlBlk_p =
            SubsDataGroupManager::Instance()->findControlBlock(mmeTimerCtxt->getUeIndex());
    if(controlBlk_p == NULL)
    {
        log_msg(LOG_INFO, "Failed to find UE context using idx %d\n",
                mmeTimerCtxt->getUeIndex());

        return;
    }

    log_msg(LOG_DEBUG, "State Guard Timeout fired. "
                      "Timer Type %d. Current Time %d\n",
                       mmeTimerCtxt->getTimerId(), time(NULL));

    TimeoutMessage *eMsg = new TimeoutMessage(timerCtxt);

    SM::Event evt(STATE_GUARD_TIMEOUT, eMsg);
    controlBlk_p->addEventToProcQ(evt);
}
