/**
 * @file trlEmuMenuButtonSet.cpp
 * @author zhfang
 * @date 2010.03.26
 * @brief trlEmuMenu Button Set
 */
#include <nn/fs.h>
#include <nw/lyt.h>
#include <string.h>
#include "trlEmuMenuData.h"
#include "trlEmuMenuButtonSet.h"
#include "../../trlEmuShellStruct.h"
#include "../trlEmuShellDLP.h"

class CEmuMenuTagProc : public nw::font::TagProcessorBase<wchar_t>
{
public:
	virtual Operation Process(u16 code,nw::font::PrintContext< wchar_t > * pContext);
	virtual Operation CalcRect(nw::ut::Rect* pRect, u16 code, nw::font::PrintContext< wchar_t > * pContext);
};
extern trlSEmuShellResumeInfo	g_sEmuShellResumeInfo;
CEmuMenuTagProc g_emuMenuTagProcessor;

CEmuMenuTagProc::Operation CEmuMenuTagProc::CalcRect(nw::ut::Rect* pRect, u16 code, nw::font::PrintContext< wchar_t > * pContext)
{
	NN_POINTER_ASSERT(pRect);
    NN_ASSERT(code < ' ');
    NN_POINTER_ASSERT(pContext);

	switch(code)
	{
	case '\n':
	case '\t':
		return this->nw::font::TagProcessorBase<wchar_t>::CalcRect(pRect, code, pContext);
	case 0x1: //^dt
		{
			char temp[16];
			wchar_t *pstr = (wchar_t *)pContext->str;
			if(pstr[0] == 0x10)//year
			{
				sprintf(temp, "%04u", g_sEmuShellResumeInfo.nYear);
				pstr[1] = temp[0];
				pstr[2] = temp[1];
				pstr[3] = temp[2];
				pstr[4] = temp[3];
			}
			else if(pstr[0] == 0x11)//month
			{
				sprintf(temp, "%02u", g_sEmuShellResumeInfo.nMonth);
				pstr[1] = temp[0];
				pstr[2] = temp[1];
			}
			else if(pstr[0] == 0x12)//day
			{
				sprintf(temp, "%02u", g_sEmuShellResumeInfo.nDay);
				pstr[1] = temp[0];
				pstr[2] = temp[1];
			}
			else if(pstr[0] == 0x13)//time
			{
				sprintf(temp, "%02u:%02u", g_sEmuShellResumeInfo.nHour, g_sEmuShellResumeInfo.nMinute);
				pstr[1] = temp[0];
				pstr[2] = temp[1];
				pstr[3] = temp[2];
				pstr[4] = temp[3];
				pstr[5] = temp[4];
			}
			else if(pstr[0] == 0x14) //player_no
			{
				NN_LOG("g_vcm_specialplayer = %d\n", g_vcm_specialplayer);
				if(g_vcm_specialplayer >= 0)
					pstr[1] = ('1' + g_vcm_specialplayer);
				else
					pstr[1] = 'x';
			}
			return OPERATION_NO_CHAR_SPACE;
		}
	case 0x02: //^cl
		{
			return OPERATION_NO_CHAR_SPACE;
		}
	case 0x03:// ^^PLAYERNAME
		{			
			wchar_t *pName = NULL;
			wchar_t *pStr = (wchar_t *)pContext->str;
			{
				wchar_t *pTemp = pStr+1;
				for(int i=0;i<40;i++)
				{					
					*pTemp = 0x04;
					pTemp++;
				}
			}
			switch(pStr[0])
			{
			case 0x10://name1
				pName = trlEmuDLPGetSelfName();
				break;
			case 0x11://name2
				pName = trlEmuDLPGetChildName(0);
				break;
			case 0x12://name3
				pName = trlEmuDLPGetChildName(1);
				break;
			case 0x13://name4
				pName = trlEmuDLPGetChildName(2);
				break;
			}
			if(pName != NULL)
			{
				for(int i=0;;i++)
				{
					if(pName[i] == 0)
					{
						if(g_nTrlNetworkClintNum == 2 && pStr[0]  == 0x12)
							pStr[1+i] = 0;
						break;
					}
					pStr[1+i] = pName[i];
				}
			}
			return OPERATION_NO_CHAR_SPACE;
		}
	case 0x04:// ^^PLAYERNAME char...
		return OPERATION_NO_CHAR_SPACE;
	default:
		return OPERATION_NO_CHAR_SPACE;
	}
}
CEmuMenuTagProc::Operation CEmuMenuTagProc::Process(u16 code,nw::font::PrintContext< wchar_t > * pContext)
{
	NN_ASSERT(code < ' ');
    NN_POINTER_ASSERT(pContext);

    switch (code)
    {
    case '\n':
    case '\t':
		return this->nw::font::TagProcessorBase<wchar_t>::Process(code, pContext);
	case 0x1: //^dt
		{
			return OPERATION_NO_CHAR_SPACE;
		}
	case 0x02: //^cl
		{
			nw::font::TextWriterBase<wchar_t> *writer = pContext->writer;
			wchar_t *pstr = (wchar_t *)pContext->str;
			if(pstr[0] == 0x10)//clb
			{				
				writer->SetTextColor(nw::ut::Color8(0,0,0,255));
			}
			else if(pstr[0] == 0x11)//clr
			{				
				writer->SetTextColor(nw::ut::Color8(255,0,0,255));
			}
			return OPERATION_NO_CHAR_SPACE;
		}
	case 0x03:// ^^PLAYERNAME
		return OPERATION_NO_CHAR_SPACE;
	case 0x04:// ^^PLAYERNAME char
		return OPERATION_NO_CHAR_SPACE;
	default:
        return OPERATION_NO_CHAR_SPACE;
    }
}

CButtonSet2::CButtonSet2(void *arcbuff, const char *lyt_name, nw::lyt::DrawInfo *pDrawInfo,nw::lyt::Drawer* pDrawer)
{
	pResAccessor = new nw::lyt::ArcResourceAccessor;
	NW_NULL_ASSERT(pResAccessor);
    if (!pResAccessor->Attach(arcbuff, "."))
    {
        NW_FATAL_ERROR("can not attach layout archive.\n");
    }

	pLayout = new nw::lyt::Layout();
	NW_NULL_ASSERT(pLayout);

    {
        const void* lytRes = pResAccessor->GetResource(0, lyt_name);
        NW_NULL_ASSERT(lytRes);
        pLayout->Build(lytRes, pResAccessor);
    }
	pLayout->SetTagProcessor(&g_emuMenuTagProcessor);
	this->pDrawInfo = pDrawInfo;
	this->pDrawer = pDrawer;
	nAnimNum = 0;
	bUpdate = true;
	init();
}


CButtonSet2::CButtonSet2(void *arcbuff, const char *lyt_name, nw::lyt::DrawInfo *pDrawInfo, nw::lyt::Drawer *pDrawer, nw::font::ResFont *pFont)
{
	pResAccessor = new nw::lyt::ArcResourceAccessor;
	NW_NULL_ASSERT(pResAccessor);
    if (!pResAccessor->Attach(arcbuff, "."))
    {
        NW_FATAL_ERROR("can not attach layout archive.\n");
    }
	pResAccessor->RegistFont("cbf_std.bcfnt", pFont);
	pLayout = new nw::lyt::Layout();
	NW_NULL_ASSERT(pLayout);

    {
        const void* lytRes = pResAccessor->GetResource(0, lyt_name);
        NW_NULL_ASSERT(lytRes);
        pLayout->Build(lytRes, pResAccessor);
    }
	pLayout->SetTagProcessor(&g_emuMenuTagProcessor);
	this->pDrawInfo = pDrawInfo;
	this->pDrawer = pDrawer;
	nAnimNum = 0;
	bUpdate = true;
	init();
}

void CButtonSet2::Release()
{
	if(pLayout != NULL)
	{
		delete pLayout;
		pLayout = NULL;
	}
	if(pResAccessor != NULL)
	{
		delete pResAccessor;
		pResAccessor = NULL;
	}
}

void CButtonSet2::init()
{
	for(int i=0;i<ANIM_MAX;i++)
	{
		nAnimFrames[i] = 0;
		bAnimEnd[i] = 1;;
		bAnimLoop[i] = 0;
	}
	for(int i=0;i<PANE_NUM_MAX;i++)
		pSetStringPaneName[i][0] = 0;
}

void CButtonSet2::InitGX()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
#ifdef NW_PLATFORM_CTR
    glDisable(GL_EARLY_DEPTH_TEST_DMP);
#endif
    NW_GL_ASSERT();
}

void CButtonSet2::SetupCamera()
{
    nw::ut::Rect layoutRect = pLayout->GetLayoutRect();
    f32 znear = 0.f;
    f32 zfar = 500.f;

    nw::math::MTX44 projMtx;
    nw::math::MTX44OrthoPivot(
        &projMtx,
        layoutRect.left,   // left
        layoutRect.right,  // right
        layoutRect.bottom, // bottom
        layoutRect.top,    // top
        znear,
        zfar,
        nw::math::PIVOT_UPSIDE_TO_TOP);
    pDrawInfo->SetProjectionMtx(projMtx);

    nw::math::VEC3 pos(0, 0, 1);
    nw::math::VEC3 up(0, 1, 0);
    nw::math::VEC3 target(0, 0, 0);

    nw::math::MTX34 viewMtx;
    nw::math::MTX34LookAt(&viewMtx, &pos, &up, &target);
    pDrawInfo->SetViewMtx(viewMtx);
}

void CButtonSet2::draw()
{
	//InitGX();
	//SetupCamera();
	//glGetError();
	pDrawer->Draw(pLayout, *pDrawInfo);
	//nw::lyt::GraphicsResource* graphicsResource = pDrawInfo->GetGraphicsResource();
	//graphicsResource->ResetGlState();
	//graphicsResource->ResetGlProgramState();

    //graphicsResource->SetProjectionMtx(pDrawInfo->GetProjectionMtx());
	//pDrawInfo->SetLayout(pLayout);
	//pLayout->Draw(*pDrawInfo);
}

void CButtonSet2::update()
{
	for(int i=0;i<nAnimNum;i++)
	{

		if(nAnimFrames[i] >= pAnimTrans[i]->GetFrameSize())
		{
			if(bAnimLoop[i] == 0)
			{
				/*if(pAnimTrans[i]->IsLoopData())
				{
					nAnimFrames[i] = 0;
					pAnimTrans[i]->SetFrame(nAnimFrames[i]);
				}
				else*/
				{	unbindanim(i);
					bAnimEnd[i] = 1;
					pAnimTrans[i]->SetFrame(pAnimTrans[i]->GetFrameSize()-1);
				}
			}
			else
			{
				nAnimFrames[i] = 0;
				pAnimTrans[i]->SetFrame(nAnimFrames[i]);
			}
		}
		else
		{
			//if(bAnimEnd[i] == 0)
			//	NN_LOG("%d anim %f\n", i, nAnimFrames[i]);
			pAnimTrans[i]->SetFrame(nAnimFrames[i]);
			nAnimFrames[i]+=1.0f;
		}
	}
	pLayout->Animate();
    pLayout->CalculateMtx(*pDrawInfo);

}

bool CButtonSet2::animisend(u32 index)
{

	if(bAnimEnd[index] == 1)
		return true;
	return false;
}


s32 CButtonSet2::addanim(const char *anim_name)
{
	if(nAnimNum < this->ANIM_MAX)
	{
		void* lpaRes = pResAccessor->GetResource(0, anim_name);
		NW_NULL_ASSERT(lpaRes);
        pAnimTrans[nAnimNum] = pLayout->CreateAnimTransform(lpaRes, pResAccessor);
		bAnimEnd[nAnimNum] = 0;
		nAnimNum++;
		return nAnimNum-1;
	}
	return -1;
}

//this is only for menu touch open test
//at this point , the layout isn't run, so the GetGlobalMtx return zero
s32 CButtonSet2::inPaneAreaSpecial(const char *button_name, s16 x, s16 y)
{
	nw::lyt::Pane *pPane = search(button_name);
	//NN_LOG("inPaneAreaSpecial  %d %d\n", x, y);
	if(pPane != NULL)
	{
		//nw::math::MTX34 mtx = pPane->GetGlobalMtx();
		nw::math::VEC3 vec3 = pPane->GetTranslate();
		nw::ut::Rect rect = pPane->GetPaneRect();

		//NN_LOG("--inPaneAreaSpecial x:%f,%f y:%f,%f\n", (rect.left +vec3.x), (rect.right +vec3.x), (rect.bottom +vec3.y), (rect.top +vec3.y));

		if( x<(rect.left +vec3.x) || x> (rect.right + vec3.x))
			return 0;
		if( y<(rect.bottom + vec3.y) || y > (rect.top + vec3.y))
			return 0;
		return 1;
	}
	return 0;
}

s32 CButtonSet2::inPaneArea(const char *button_name, s16 x, s16 y)
{
	nw::lyt::Pane *pPane = search(button_name);
	if(pPane != NULL)
	{
		nw::math::MTX34 mtx = pPane->GetGlobalMtx();


		//nw::math::VEC3 vec3 = pPane->GetTranslate();
		nw::ut::Rect rect = pPane->GetPaneRect();

		if( x<(rect.left + mtx.m[0][3]) || x> (rect.right + mtx.m[0][3]))
			return 0;
		if( y<(rect.bottom + mtx.m[1][3]) || y > (rect.top + mtx.m[1][3]))
			return 0;
		return 1;
	}
	return 0;
}

void CButtonSet2::bindanim(const char *button_name, u32 anim_index, u32 bLoop, u32 bRecursive)
{
	if(anim_index < this->nAnimNum)
	{
		nw::lyt::Pane *pPane = search(button_name);
		if(pPane != NULL)
		{
			pPane->BindAnimation(pAnimTrans[anim_index], bRecursive);
			nAnimFrames[anim_index] = 0;
			bAnimEnd[anim_index] = 0;
			bAnimLoop[anim_index] = bLoop;
			pAnimTrans[anim_index]->SetFrame(nAnimFrames[anim_index]);
		}
		else
		{
			NN_LOG("can't find the Button %s\n", button_name);
		}
	}
	else
	{
		NN_LOG("can't find anim %d for %s\n", anim_index, button_name);
	}
}



void CButtonSet2::bindanimall(u32 anim_index, u32 bLoop)
{
	if(anim_index < this->nAnimNum)
	{
		pLayout->BindAnimation(pAnimTrans[anim_index]);
		nAnimFrames[anim_index] = 0;
		pAnimTrans[anim_index]->SetFrame(nAnimFrames[anim_index]);
		bAnimEnd[anim_index] = 0;
		bAnimLoop[anim_index] = bLoop;
	}
}

void CButtonSet2::unbindanim(const char *button_name, u32 anim_index)
{
	if(anim_index < this->nAnimNum)
	{
		nw::lyt::Pane *pPane = search(button_name);
		if(pPane != NULL)
		{
			pPane->UnbindAnimation(pAnimTrans[anim_index]);
			nAnimFrames[anim_index] = 0;
			bAnimEnd[anim_index] = 1;
			bAnimLoop[anim_index] = 0;
		}
	}
}

void CButtonSet2::unbindanim(u32 anim_index)
{
	if(anim_index < this->nAnimNum)
	{
		pLayout->UnbindAnimation(pAnimTrans[anim_index]);
		nAnimFrames[anim_index] = 0;
		bAnimEnd[anim_index] = 1;
		bAnimLoop[anim_index] = 0;
	}
}

void CButtonSet2::unbindallanim(const char *button_name)
{
	nw::lyt::Pane *pPane = search(button_name);
	if(pPane != NULL)
		pPane->UnbindAllAnimation();
}

void CButtonSet2::unbindallanim()
{
	pLayout->UnbindAllAnimation();
}


nw::lyt::Pane* CButtonSet2::searchchild(nw::lyt::Pane *pParent, const char *name)
{
	nw::lyt::PaneList &list = pParent->GetChildList();
	for(nw::lyt::PaneList::Iterator it = list.GetBeginIter(); it != list.GetEndIter(); ++ it)
	{
		if(strcmp((char*)name, it->GetName()) == 0)
			return (&*it);
	}

	nw::lyt::Pane *pPane;
	for(nw::lyt::PaneList::Iterator it = list.GetBeginIter(); it != list.GetEndIter(); ++ it)
	{
		pPane = searchchild(&*it, name);
		if(pPane != NULL)
			return pPane;
	}
	return NULL;
}

nw::lyt::Pane* CButtonSet2::search(const char *name)
{
	return searchchild(pLayout->GetRootPane(), name);
	/*nw::lyt::PaneList &list = pLayout->GetRootPane()->GetChildList();
	for(nw::lyt::PaneList::Iterator it = list.GetBeginIter(); it != list.GetEndIter(); ++ it)
	{
		if(strcmp((char*)name, it->GetName()) == 0)
			return (&*it);
	}
	return NULL;*/
}

void CButtonSet2::SetStringByName(const char *name, const wchar_t *str)
{
	nw::lyt::TextBox *pTextBox =  (nw::lyt::TextBox*)search(name);
	if(pTextBox != NULL)
	{
		u32 strlen = 0;
		while(str[strlen]!=0)
			strlen++;
		if(strlen > pTextBox->GetStringBufferLength())
		{
			pTextBox->FreeStringBuffer();
			pTextBox->AllocStringBuffer(strlen);
		}
		pTextBox->SetString(str);
	}
}

void CButtonSet2::SetStringByUserStr(const char *userstr, const wchar_t *str, const int strlen, const float scale)
{	
	SetStringChildByUserStr(pLayout->GetRootPane(), userstr, str, strlen, scale);
}

void CButtonSet2::SetStringChildByUserStr(nw::lyt::Pane *pParent, const char *userstr, const wchar_t *str, const int strlen, const float scale)
{
	nw::lyt::PaneList &list = pParent->GetChildList();
	for(nw::lyt::PaneList::Iterator it = list.GetBeginIter(); it != list.GetEndIter(); ++ it)
	{
		if(strcmp((char*)userstr, it->GetUserData()) == 0)
		{
			if(strlen > ((nw::lyt::TextBox*)(&*it))->GetStringBufferLength())
			{
				((nw::lyt::TextBox*)(&*it))->FreeStringBuffer();
				((nw::lyt::TextBox*)(&*it))->AllocStringBuffer(strlen);
			}
			((nw::lyt::TextBox*)(&*it))->SetString(str);
			//it->SetScale(nw::math::VEC2(scale, scale));
			//if( scale > 1.00001f || scale < 0.9999f)
			{
				int index = -1;
				nw::lyt::Size size;
				//change font size
				for(int i=0;i<PANE_NUM_MAX;i++)
				{
					if(pSetStringPaneName[i][0] == 0)
					{
						memset(pSetStringPaneName[i], 0, PANE_NAME_LENGTH_MAX);
						strcpy(pSetStringPaneName[i], it->GetName());
						size = ((nw::lyt::TextBox*)(&*it))->GetFontSize();
						pSetStringPaneFontSizeX[i] = size.width;
						pSetStringPaneFontSizeY[i] = size.height;
						index = i;
						break;
					}
					else if(strcmp(pSetStringPaneName[i], it->GetName()) == 0)
					{
						index = i;
						break;
					}
				}
				size.width = pSetStringPaneFontSizeX[index]*scale;
				size.height = pSetStringPaneFontSizeY[index]*scale;
				((nw::lyt::TextBox*)(&*it))->SetFontSize(size);
				//NN_LOG("SetStringChildByUserStr  done\n");
			}
		}
	}

	nw::lyt::Pane *pPane;
	for(nw::lyt::PaneList::Iterator it = list.GetBeginIter(); it != list.GetEndIter(); ++ it)
	{
		SetStringChildByUserStr(&*it, userstr, str, strlen, scale);
	}
	return;
}

void CButtonSet2::SetFont(nw::font::ResFont *pFont)
{
	SetFont(pLayout->GetRootPane(), pFont);
}

void CButtonSet2::SetFont(nw::lyt::Pane *pParent, nw::font::ResFont *pFont)
{
	nw::lyt::PaneList &list = pParent->GetChildList();
	for(nw::lyt::PaneList::Iterator it = list.GetBeginIter(); it != list.GetEndIter(); ++ it)
	{
		const char *temp = it->GetUserData();
		if(temp != NULL && strcmp("", temp) != 0)
		{
			((nw::lyt::TextBox*)(&*it))->SetFont(pFont);
		}
	}

	nw::lyt::Pane *pPane;
	for(nw::lyt::PaneList::Iterator it = list.GetBeginIter(); it != list.GetEndIter(); ++ it)
	{
		SetFont(&*it, pFont);
	}
	return;
}

