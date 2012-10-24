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

DriverInfoLib::DriverInfoLib(String ^classGuid)
	: driverInfo(NULL)
{
	GUID guid;
	std::wstring guidStr = marshal_as<std::wstring>(classGuid);
	CLSIDFromString(guidStr.c_str(), (LPCLSID)&guid);
	driverInfo = new DriverInfo(guid);
}

int DriverInfoLib::GetNumDevices()
{
	return driverInfo->GetNumDevices();
}

DWORD DriverInfoLib::GetPropertyValue(DWORD propIdent, int idx)
{
	DWORD value(0);
	if (!driverInfo->GetPropertyValue(propIdent, (UINT)idx, value))
	{
		throw gcnew Exception(gcnew String(
			"Error getting property value with error code " + driverInfo->m_error));
	}

	return value;
}

String ^ DriverInfoLib::GetPropertyString(DWORD propIdent, int idx)
{
	std::wstring ws;
	if (!driverInfo->GetPropertyValue(propIdent, (UINT)idx, ws))
	{
		throw gcnew Exception(gcnew String(
			"Error getting property value with error code " + driverInfo->m_error));
	}

	return marshal_as<String ^>(ws);
}

List<String ^> ^ DriverInfoLib::GetPropertyList(DWORD propIdent, int idx)
{
	auto list = gcnew List<String ^>();
	std::vector<std::wstring> vecValues;
	if (driverInfo->GetPropertyValue(propIdent, (UINT)idx, vecValues))
	{
		for each (auto value in vecValues)
		{
			list->Add(marshal_as<String ^>(value));
		}
	}

	return list;
}

bool DriverInfoLib::GetPropertyValueEx(DWORD propIdent, int idx, DWORD* dwType, BYTE** buffer)
{
	return driverInfo->GetPropertyValueEx(propIdent, (UINT)idx, dwType, buffer);
}

}
