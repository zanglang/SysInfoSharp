#include "StdAfx.h"
#include <msclr\marshal_cppstd.h>
#include "DxDiagLib.h"
using namespace std;
using namespace System;
using namespace System::Collections::Generic;
using namespace msclr::interop;

namespace SysInfoSharp {

DxDiagLib::DxDiagLib(void)
	: dxDiag(NULL)
{
	dxDiag = new DxDiagInfo();
}

IDxDiagContainer * DxDiagLib::GetRootContainer()
{
	return dxDiag->GetRootContainer();
}

int DxDiagLib::GetContainerChildrenCount(String ^ container)
{
	return dxDiag->GetContainerChildrenCount(marshal_as<std::wstring>(container));
}

String ^ DxDiagLib::GetInfoByContainer(String ^ container, int containerIdx, String ^ child)
{
	std::wstring szValue = L"";
	DWORD ret = dxDiag->GetInfoByContainer(marshal_as<std::wstring>(container),
		containerIdx, marshal_as<std::wstring>(child), szValue);
	if (ret != 0)
	{
		return marshal_as<String ^>(szValue);
	}
	else
		return nullptr;
}

String ^ DxDiagLib::GetInfoByContainer(IDxDiagContainer* pContainer, String ^ child)
{
	std::wstring szValue = L"";
	DWORD ret = dxDiag->GetInfoByContainer(pContainer,
		marshal_as<std::wstring>(child), szValue);
	if (ret != 0)
	{
		return marshal_as<String ^>(szValue);
	}
	else
		return nullptr;
}

List<String ^> ^ DxDiagLib::EnumProperties(String ^ container, int containerIdx)
{
	auto list = gcnew List<String ^>();
	std::vector<std::wstring> vecProps;
	if (dxDiag->EnumProperties(marshal_as<std::wstring>(container),
		containerIdx, vecProps) != 0)
	{
		for each (auto prop in vecProps)
		{
			list->Add(marshal_as<String ^>(prop));
		}
	}

	return list;
}

}
