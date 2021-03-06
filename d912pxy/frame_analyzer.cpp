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
#include "stdafx.h"

d912pxy_device* d912translator;

IDirect3DDevice9* app_cb_D3D9Dev_create(IDirect3DDevice9Proxy* dev, IDirect3D9* obj)
{
	
#ifndef PERFORMANCE_GRAPH_WRITE_DX9
	if (dev->GetOrigD3D9Call()->DeviceType != D3DDEVTYPE_HAL)
		return dev;
#else 
	if (dev->GetOrigD3D9Call()->DeviceType != D3DDEVTYPE_HAL)
		return dev;
	else {
		if (!d912pxy_helper::IsFileExist("performance_graph_dx9.png"))
		{
			dev->InitPerfGraph();
			return dev;
		}
	}
#endif
	
		
	d912translator = new d912pxy_device(dev, obj);
	return (IDirect3DDevice9*)d912translator;
}

void app_cb_D3D9Dev_destroy(IDirect3DDevice9 * dev)
{

}