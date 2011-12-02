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

		unsigned int GetNumDevices();
		bool GetPropertyValue(DWORD propIdent, unsigned int idx, DWORD & value);
		bool GetPropertyValue(DWORD propIdent, unsigned int idx, String ^ value);
		List<String ^> ^ DriverInfoLib::GetPropertyValue(DWORD propIdent, unsigned int idx);

	private:
		DriverInfo *driverInfo;
	};
}
