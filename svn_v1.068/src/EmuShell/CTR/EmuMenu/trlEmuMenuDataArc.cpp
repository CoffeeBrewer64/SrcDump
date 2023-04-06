/**
* @file trlEmuMenuDataArc.cpp
* @author zhfang
* @date 2011.06.30
* @brief trlEmuMenu
*/
#include "trlEmuMenuDataLayout.h"
#include "trlEmuMenuDataArc.h"


//////////////////////////
////arc 
//////////////////////////
enum EVCMArc
{
	eVCMArc_CGB,
	eVCMArc_ERR,	
	eVCMArc_HVC_CtrlChange,
	eVCMArc_HomeNix,
	eVCMArc_CommonWnd,
	eVCMArcNum
};

trlEmuMenuArc cgbvcm_arc =	{	L"rom:/VCM/CGBVCM/layout.arc",	eCGBVCMLayoutNum, cgbvcm_layout	};
trlEmuMenuArc errvcm_arc =	{	L"rom:/VCM/ERRVCM/layout.arc",	eERRVCMLayoutNum, errvcm_layout	};
trlEmuMenuArc hvcvcm_arc =	{	L"rom:/VCM/HVCVCM/ctrl_change/layout.arc",	eHVCVCMCTRLLyoutNum, hvcvcm_layout	};
trlEmuMenuArc homenixvcm_arc = { L"rom:/VCM/HomeNixSign/layout/layout_out/layout.arc", eHOMENIXCTRLLayoutNum, homenix_layout };
trlEmuMenuArc common_wnd_arc = {	L"rom:/VCM/HVCVCM/COMMON_WND/layout.arc",	eCOMMONWINDOWLayoutNum, commonewindow_layout	};

trlEmuMenuArc* vcmarc[] =
{
	&cgbvcm_arc,
	&errvcm_arc,
	&hvcvcm_arc,
	&homenixvcm_arc,
	&common_wnd_arc
};

trlEmuMenuRes g_vcmres = 
{
	eVCMArcNum, 
	vcmarc
};
