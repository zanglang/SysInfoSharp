// SysInfoSharp.h
#pragma once

#pragma unmanaged
#include "SysInfo/DriverInfo.h"

#pragma managed
#include "DxDiagLib.h"
using namespace System;
using namespace System::Collections::Generic;

namespace SysInfoSharp {

	public ref class DriverInfoLib
	{
	public:
		DriverInfoLib(void);
		DriverInfoLib(const GUID & classGuid);
		DriverInfoLib(String ^classGuid);

		int GetNumDevices();
		DWORD GetPropertyValue(DWORD propIdent, int idx);
		String ^ GetPropertyString(DWORD propIdent, int idx);
		List<String ^> ^ GetPropertyList(DWORD propIdent, int idx);
		bool GetPropertyValueEx(DWORD propIdent, int idx, DWORD* dwType, BYTE** buffer);

	private:
		DriverInfo *driverInfo;
	};
}
