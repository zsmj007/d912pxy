/*
MIT License

Copyright(c) 2018-2019 megai2

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#pragma once
#include "stdafx.h"

class d912pxy_upload_pool;

class d912pxy_upload_item : public d912pxy_comhandler {
public:
	d912pxy_upload_item(d912pxy_device * dev, UINT8 icat);
	~d912pxy_upload_item();

	void UploadTargetWithOffset(d912pxy_resource* res, UINT64 sofs, UINT64 dofs, UINT64 sz, ID3D12GraphicsCommandList* cl);
	void UploadTarget(ID3D12Resource* res, UINT64 dofs, UINT64 sz, ID3D12GraphicsCommandList* cl);
	
	intptr_t DPtr();

	intptr_t DPtrOffset(UINT64 offset);

	void Reconstruct(void* mem, UINT64 rowPitch, UINT64 height, UINT64 size, const D3D12_RANGE* wofs);

	ID3D12Resource* GetResourcePtr() { return mRes; };

	UINT FinalReleaseCB();

	UINT32 PooledAction(UINT32 use);

private:	
	intptr_t mappedMemWofs;

	ID3D12Resource* mRes;

	UINT8 cat;
};

//start with 2^16 (64kB) end with 2^28(256mB)
//this will allow creating buffers with size up to 256mB
#define PXY_INNDER_UPLOAD_POOL_BITIGNORE 16
#define PXY_INNDER_UPLOAD_POOL_BITLIMIT 28
#define PXY_INNDER_UPLOAD_POOL_BITCNT PXY_INNDER_UPLOAD_POOL_BITLIMIT - PXY_INNDER_UPLOAD_POOL_BITIGNORE


class d912pxy_upload_pool : public d912pxy_pool_memcat<d912pxy_upload_item*, d912pxy_upload_pool*>
{
public:
	d912pxy_upload_pool(d912pxy_device* dev);
	~d912pxy_upload_pool();

	d912pxy_upload_item* GetUploadObject(UINT size);
	ID3D12Resource* MakeUploadBuffer(UINT maxSize);

	d912pxy_upload_item* AllocProc(UINT32 cat);	

	void EarlyInitProc();
private:		
	void CreateMemPool();

	d912pxy_thread_lock* ctorLock;

	ID3D12Heap* memPool;
	UINT64 memPoolOffset;
	UINT64 memPoolSize;
};

