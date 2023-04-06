/*---------------------------------------------------------------------------*
  Project:  Pia
  File:     main.cpp

  Copyright (C)2011-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.
 *---------------------------------------------------------------------------*/


#include "ErrorHandling.h"

#include <nn/Result.h>

#include <pia/common/common_ErrorHandler.h>
#include <pia/common/common_Log.h>

#include <cstdlib>

namespace
{
const char* STRING_PIA_MODULE_TYPE[] =
{
    "Reserved",
	"PiaCommon",
	"PiaLocal",
	"PiaTransport",
	"PiaSync",
	"NotDefined"
};

const char* STRING_PIA_ERROR_SEVERITY[] =
{
    "NO_PROBLEM",
	"PROGRAMMING_ERROR",
	"IGNORABLE",
	"SHOULD_BE_HANDLED",
	"MUST_BE_REINITIALIZED",
	"UNKNOWN"
};

const char* STRING_PIA_COMMON_ERROR[] =
{
    "NotInitialized",
    "MemoryLeak",
    "InvalidArgument",
    "AlreadyInitialized",
    "OutOfResource",
    "InternalError",
    "InvalidState"
};

const char* STRING_PIA_LOCAL_ERROR[] =
{
    "NotInitialized",
    "InvalidArgument",
    "AlreadyInitialized",
    "InvalidState",
    "NotFoundNetwork",
    "InvalidNode",
    "NothingPacket",
    "NegligibleFault",
    "InvalidConnection",
    "HostMigrationFailure"
};

const char* STRING_PIA_TRANSPORT_ERROR[] =
{
    "DESCRIPTION_SUCCESS",
    "DESCRIPTION_FAIL"
};

const char* STRING_PIA_SYNC_ERROR[] =
{
    "Base",
    "NotInitialized",
    "InvalidState",
    "InvalidArgument",
    "DataIsNotArrivedYet",
    "OutOfResource",
    "SynchronizationIsLost",
    "FailedToSynchronize",
    "InvalidDevice",
    "ToBeImplemented"
};

#if 0
    inline void CopyString(char8 *szDestination, const char16 *szSource)
    {
        const s32 iLength=std::wcslen(szSource)+1;
        std::wcstombs(szDestination, szSource, iLength);
    }

    inline void CopyString(char16 *szDestination, const char8 *szSource)
    {
        const s32 iLength = std::strlen(szSource)+1;
        std::mbstowcs(szDestination, szSource, iLength);
    }
#else
    inline void CopyString(char8 *szDestination, const char8 *szSource)
    {
        std::strcpy(szDestination, szSource);
    }
#endif

}  // end of anonymous namespace


nn::Result ErrorHandling::s_result                     = nn::ResultSuccess();
char8      ErrorHandling::s_filename[FILENAME_MAX_LEN] = {};
u32        ErrorHandling::s_lineNo                     = 0;

bool ErrorHandling::s_bInitialized = false;


void ErrorHandling::Initialize(void)
{
    if(!s_bInitialized)
    {
        s_bInitialized = true;
    }
}

void ErrorHandling::Finalize(void)
{
    if(s_bInitialized)
    {
        s_bInitialized = false;
    }
}

bool ErrorHandling::IsErrorDetected(void)
{
    NN_ASSERT(s_bInitialized);

    return s_result.IsFailure();
}


nn::Result ErrorHandling::GetResultCode(void)
{
    return s_result;
}


const char* ErrorHandling::GetFilename(void)
{
    return s_filename;
}


u32 ErrorHandling::GetLineNo(void)
{
    return s_lineNo;
}



void ErrorHandling::PrintResult(nn::Result result)
{
    if( nn::pia::common::ErrorHandler::IsPiaError(result) )
    {
        NN_PIA_DUMMY_PARAM(STRING_PIA_MODULE_TYPE);
        NN_PIA_DUMMY_PARAM(STRING_PIA_ERROR_SEVERITY);
        NN_PIA_DUMMY_PARAM(STRING_PIA_COMMON_ERROR);
        NN_PIA_DUMMY_PARAM(STRING_PIA_LOCAL_ERROR);
        NN_PIA_DUMMY_PARAM(STRING_PIA_TRANSPORT_ERROR);
        NN_PIA_DUMMY_PARAM(STRING_PIA_SYNC_ERROR);
    #ifndef NN_BUILD_VERBOSE
        //_PLOG(nn::pia::common::Log::LEVEL_ERROR, " Value:   0x%08x(Pia)",  result.GetValue());
        //_PLOG(nn::pia::common::Log::LEVEL_ERROR, " Module:  %02d", nn::pia::common::ErrorHandler::GetModuleTypeFromResult(result));
        //_PLOG(nn::pia::common::Log::LEVEL_ERROR, " Severity:%02d", nn::pia::common::ErrorHandler::GetSeverity(result));
        //_PLOG(nn::pia::common::Log::LEVEL_ERROR, " Desc: %04d", result.GetDescription() & 0x001F );
    #else
        /*_PLOG(nn::pia::common::Log::LEVEL_ERROR, " Value:   0x%08x(Pia)",  result.GetValue());
        _PLOG(nn::pia::common::Log::LEVEL_ERROR, " Module:  %s", STRING_PIA_MODULE_TYPE[nn::pia::common::ErrorHandler::GetModuleTypeFromResult(result)]);
        _PLOG(nn::pia::common::Log::LEVEL_ERROR, " Severity:%s", STRING_PIA_ERROR_SEVERITY[nn::pia::common::ErrorHandler::GetSeverity(result)]);
        switch( nn::pia::common::ErrorHandler::GetModuleTypeFromResult(result) )
        {
        case nn::pia::MODULE_TYPE_COMMON:
            {
                _PLOG(nn::pia::common::Log::LEVEL_ERROR, " Desc: %s", STRING_PIA_COMMON_ERROR[(result.GetDescription() & 0x001F)]);
            }break;
        case nn::pia::MODULE_TYPE_LOCAL:
            {
                _PLOG(nn::pia::common::Log::LEVEL_ERROR, " Desc: %s", STRING_PIA_LOCAL_ERROR[(result.GetDescription() & 0x001F)]);
            }break;
        case nn::pia::MODULE_TYPE_TRANSPORT:
            {
                _PLOG(nn::pia::common::Log::LEVEL_ERROR, " Desc: %s", STRING_PIA_TRANSPORT_ERROR[(result.GetDescription() & 0x001F)]);
            }break;
        case nn::pia::MODULE_TYPE_SYNC:
            {
                _PLOG(nn::pia::common::Log::LEVEL_ERROR, " Desc: %s", STRING_PIA_SYNC_ERROR[(result.GetDescription() & 0x001F)]);
            }break;
        default:
            {
                _PLOG(nn::pia::common::Log::LEVEL_ERROR, " Unknown Error");
            }break;
        }*/
    #endif
    }
    else
    {
        NN_LOG(" Value:   0x%08x(Not Pia)",  result.GetValue());
        NN_LOG(" Level:       %4d", result.GetLevel());
        NN_LOG(" Module:      %4d", result.GetModule());
        NN_LOG(" Summary:     %4d", result.GetSummary());
        NN_LOG(" Description: %4d", result.GetDescription());
    }
}

void ErrorHandling::Print(void)
{
    char8 buf[FILENAME_MAX_LEN];
    CopyString(buf, GetFilename());
    //_PLOG(nn::pia::common::Log::LEVEL_ERROR, "\n----- ErrorHandling Start -----");
    //_PLOG(nn::pia::common::Log::LEVEL_ERROR, " Filename:    %s", buf);
    //_PLOG(nn::pia::common::Log::LEVEL_ERROR, " Line:        %d", GetLineNo());

    PrintResult(GetResultCode());
    //_PLOG(nn::pia::common::Log::LEVEL_ERROR, "----- ErrorHandling End -----\n");
}



void ErrorHandling::Clear(void)
{
    s_result       = nn::ResultSuccess();
    s_filename[0]  = '\0';
    s_lineNo       = 0;
}


void ErrorHandling::SetResultCode(nn::Result result)
{
    s_result = result;
}
