// SysInfoSharp.h
#pragma once

#pragma unmanaged
#include <dxdiag.h>
#include "SysInfo/DxDiagInfo.h"

#pragma managed
using namespace System;
using namespace System::Collections::Generic;

namespace SysInfoSharp {

	public ref class DxDiagLib
	{
	public:
		DxDiagLib(void);

		// API
		int			GetContainerChildrenCount(String ^ container);
		String ^	GetInfoByContainer(String ^ container, int containerIdx, String ^ child);
		String ^	GetInfoByContainer(IDxDiagContainer* pContainer, String ^ child);
		List<String ^> ^ EnumProperties(String ^ container, int containerIdx);
		IDxDiagContainer * GetRootContainer();

	protected:
		DxDiagInfo *dxDiag;
	};
}
