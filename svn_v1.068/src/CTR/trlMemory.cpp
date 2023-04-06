/**
 * @file trlMemory_CTR.cpp
 * @author zhfang
 * @date 2009.11.16
 * @brief TRL Emulate For CTR - Memory Module
 */
#include <nn/os.h>
#include <nn/fnd.h>
#include "..\trlDebug.h"
#include "..\trlMemory.h"
using namespace nn::os;
using namespace nn::fnd;

/** @name Macro Define */
//@{
#define TRL_MEMORY_FCRAM_GX		0x400000
#define TRL_MATH_ROUNDUP(x, b)  ((x) + ((b)-1)) & ~((b)-1)
//@}

/** @name Global Variable */
//@{
static MemoryBlock	g_hTrlMemBlock;
static ExpHeap		g_hTrlMemHeap;
static ExpHeap		g_hTrlMemDeviceHeap;
static ExpHeap		g_hTrlMemFcramHeap;
static uptr			g_pTrlMemHeapForGx;
static uptr			g_pTrlMemCurAddrVramA;
static uptr			g_pTrlMemCurAddrVramB;
//@}

/** @brief init the trl system memory */
u32 trlMemInit(u32 nMaxSize )
{	
	g_hTrlMemBlock.Initialize(nMaxSize);
	g_hTrlMemHeap.Initialize(g_hTrlMemBlock.GetAddress(), g_hTrlMemBlock.GetSize());
	g_hTrlMemDeviceHeap.Initialize(nn::os::GetDeviceMemoryAddress(), nn::os::GetDeviceMemorySize(), nn::os::ALLOCATE_OPTION_LINEAR);
	g_pTrlMemHeapForGx = reinterpret_cast<uptr>(trlMemAllocDevice(TRL_MEMORY_FCRAM_GX, 128));
    g_hTrlMemFcramHeap.Initialize(g_pTrlMemHeapForGx, TRL_MEMORY_FCRAM_GX, nn::os::ALLOCATE_OPTION_LINEAR);
    g_pTrlMemCurAddrVramA = nn::gx::GetVramStartAddr(nn::gx::MEM_VRAMA);
    g_pTrlMemCurAddrVramB = nn::gx::GetVramStartAddr(nn::gx::MEM_VRAMB);
	return g_hTrlMemHeap.GetAllocatableSize();
}

/** @brief reset the trl system memory */ 
u32 trlMemReset()
{
	g_hTrlMemDeviceHeap.Finalize();
	g_hTrlMemHeap.Finalize();
	if(g_hTrlMemBlock.GetSize() != 0)
	{
		g_hTrlMemHeap.Initialize(g_hTrlMemBlock.GetAddress(), g_hTrlMemBlock.GetSize());
		g_hTrlMemDeviceHeap.Initialize(nn::os::GetDeviceMemoryAddress(), nn::os::GetDeviceMemorySize(), nn::os::ALLOCATE_OPTION_LINEAR);
		return g_hTrlMemHeap.GetAllocatableSize();
	}
	return 0;
}

/** @brief Alloc memory */
void* trlMemAlloc(size_t nSize, u8 nAlign)
{
#if !TRL_PRODUCTION
	if(nAlign != 1 && nAlign != 2 && nAlign !=4 && nAlign != 8 && nAlign != 16
		&& nAlign != 32 && nAlign != 64 && nAlign != 128)
	{		
		TRL_ERROR("trlMemAlloc unsupport align num");
		return NULL;
	}
#endif
	if(g_hTrlMemHeap.GetAllocatableSize(nAlign) >= nSize)
	{
		return g_hTrlMemHeap.Allocate(nSize, nAlign);
	}
	return NULL;
}

/** @brief Free Memory */
void trlMemFree(void* pBuf)
{
	if(pBuf != NULL)
		g_hTrlMemHeap.Free(pBuf);
}

/** @brief get total size of system memory */
u32 trlMemGetTotalSize()
{
	return g_hTrlMemBlock.GetSize();
}

/** @brief get current free system memory */
u32 trlMemGetFree()
{
	return g_hTrlMemHeap.GetAllocatableSize();
}

/** @brief output the state of system memory usage */
void trlMemPrint()
{
	NN_LOG("g_hTrlMemHeap  0x%x  0x%x\n", g_hTrlMemHeap.GetStartAddress(), trlMemGetFree());	
}

/** @brief Alloc Device Memory */
void* trlMemAllocDevice(size_t nSize, u8 nAlign)
{
	return g_hTrlMemDeviceHeap.Allocate(nSize, nAlign);
}

/** @brief Free Device Memory */
void trlMemFreeDevice(void* pBuf)
{
	if(pBuf != NULL)
	{
		g_hTrlMemDeviceHeap.Free(pBuf);
		pBuf = NULL;
	}

}

/** @brief Alloc Vram Memory */
void* trlMemAllocVram(GLenum area, GLenum aim, GLuint id, GLsizei size)
{
	(void)id;
	if (size == 0)
		return 0;

	int addrAlign = 8;
    void* resultAddr = NULL;
    switch (aim)
    {
        case NN_GX_MEM_SYSTEM:
            addrAlign = 4;
            break;
        case NN_GX_MEM_TEXTURE:
            addrAlign = 128;
            break;
        case NN_GX_MEM_VERTEXBUFFER:
            addrAlign = 8;
            break;
        case NN_GX_MEM_RENDERBUFFER:
            addrAlign = 64;
            break;
        case NN_GX_MEM_DISPLAYBUFFER:
            addrAlign = 16;
            break;
        case NN_GX_MEM_COMMANDBUFFER:
            addrAlign = 16;
            break;
    }
    
    switch (area)
    {
    case NN_GX_MEM_FCRAM:
        if ( (resultAddr = g_hTrlMemFcramHeap.Allocate(size, addrAlign)) == NULL)
            NN_TPANIC_("[MemoryManager] lack of resource on Main Memory (FCRAM).\n");
        break;
    case NN_GX_MEM_VRAMA:
        if (TRL_MATH_ROUNDUP(g_pTrlMemCurAddrVramA, addrAlign) + size > nn::gx::GetVramEndAddr(nn::gx::MEM_VRAMA))
            NN_TPANIC_("[MemoryManager] lack of resource on VRAM-A.\n");
        g_pTrlMemCurAddrVramA = TRL_MATH_ROUNDUP(g_pTrlMemCurAddrVramA, addrAlign);
        resultAddr = reinterpret_cast<void*>(g_pTrlMemCurAddrVramA);
        g_pTrlMemCurAddrVramA += size;
        break;
    case NN_GX_MEM_VRAMB:
        if (TRL_MATH_ROUNDUP(g_pTrlMemCurAddrVramB, addrAlign) + size > nn::gx::GetVramEndAddr(nn::gx::MEM_VRAMB))
            NN_TPANIC_("[MemoryManager] lack of resource on VRAM-B.\n");
        g_pTrlMemCurAddrVramB = TRL_MATH_ROUNDUP(g_pTrlMemCurAddrVramB, addrAlign);
        resultAddr = reinterpret_cast<void*>(g_pTrlMemCurAddrVramB);
        g_pTrlMemCurAddrVramB += size;
        break;
    }
    return resultAddr;
}

/** @brief Free Vram Memory */
void trlMemFreeVram(GLenum area, GLenum aim, GLuint id, void* addr)
{
    (void)aim;
    (void)id;
	if(area == NN_GX_MEM_FCRAM)
        g_hTrlMemFcramHeap.Free(addr);
}

/** @brief Delete Memory */
void trlMemExit()
{
    g_hTrlMemFcramHeap.Invalidate();
	g_hTrlMemDeviceHeap.Invalidate();
	g_hTrlMemHeap.Invalidate();
	g_hTrlMemHeap.Finalize();
	g_hTrlMemBlock.Finalize();
}
