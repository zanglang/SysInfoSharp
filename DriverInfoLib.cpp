#include "StdAfx.h"
#include <msclr\marshal_cppstd.h>
#include "DriverInfoLib.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace msclr::interop;

namespace SysInfoSharp
{

DriverInfoLib::DriverInfoLib(void)
	: driverInfo(NULL)
{
	driverInfo = new DriverInfo();
}

DriverInfoLib::DriverInfoLib(const GUID & classGuid)
	: driverInfo(NULL)
{
	driverInfo = new DriverInfo(classGuid);
}

unsigned int DriverInfoLib::GetNumDevices()
{
	return driverInfo->GetNumDevices();
}

bool DriverInfoLib::GetPropertyValue(DWORD propIdent, unsigned int idx, DWORD & value)
{
	return driverInfo->GetPropertyValue(propIdent, idx, value);
}

bool DriverInfoLib::GetPropertyValue(DWORD propIdent, unsigned int idx, String ^ value)
{
	return driverInfo->GetPropertyValue(propIdent, idx, marshal_as<std::wstring>(value));
}

List<String ^> ^ DriverInfoLib::GetPropertyValue(DWORD propIdent, unsigned int idx)
{
	auto list = gcnew List<String ^>();
	std::vector<std::wstring> vecValues;
	if (driverInfo->GetPropertyValue(propIdent, idx, vecValues))
	{
		for each (auto value in vecValues)
		{
			list->Add(marshal_as<String ^>(value));
		}
	}

	return list;
}

}
