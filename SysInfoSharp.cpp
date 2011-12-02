// This is the main DLL file.

#include "stdafx.h"
#include <msclr\marshal_cppstd.h>
#include "SysInfoSharp.h"
#include "DxDiagLib.h"
using namespace std;
using namespace System;
using namespace System::Collections::Generic;
using namespace msclr::interop;

namespace SysInfoSharp {

SysInfoLib::SysInfoLib(void)
	: sysInfo(NULL)
{
	sysInfo = new ::SysInfo();
}

void SysInfoLib::Init(void)
{
	sysInfo->Init();
}

void SysInfoLib::Refresh(void)
{
	sysInfo->Refresh();
}

int SysInfoLib::GetNumCategories(void)
{
	return sysInfo->GetNumCategories();
}

String^	SysInfoLib::GetCategoryName(int index)
{
	return marshal_as<String^>(sysInfo->GetCategoryName(index));
}

List<String^> ^	SysInfoLib::GetCategories()
{
	auto categories = gcnew List<String ^>();
	for each (auto p in sysInfo->m_mapInfo)
	{
		categories->Add(marshal_as<String ^>(p.first));
	}

	return categories;
}

int SysInfoLib::GetNumCategoryContents(String ^categoryName)
{
	std::wstring szCat = marshal_as<std::wstring>(categoryName);
	return sysInfo->GetNumCategoryContents(szCat);
}

String^	SysInfoLib::GetValue(String ^ category, String ^ valueName)
{
	std::wstring szCat = marshal_as<std::wstring>(category),
			szName = marshal_as<std::wstring>(valueName);

	return marshal_as<String^>(sysInfo->GetValue(szCat, szName));
}

String^	SysInfoLib::GetValueName(String ^category, int valueIndex)
{
	std::wstring szCat = marshal_as<std::wstring>(category);
	return marshal_as<String^>(sysInfo->GetValueName(szCat, valueIndex));
}

bool SysInfoLib::ValueCheck(String ^name, String ^testValue, ComparisonMethods dwMode)
{
	int ret = sysInfo->ValueCheck(
				marshal_as<std::wstring>(name),
				marshal_as<std::wstring>(testValue),
				static_cast<DWORD>(dwMode));
	return ret != 0;
}

bool SysInfoLib::Compare(String ^actualValue, String ^testValue, ComparisonMethods dwMode)
{
	int ret = SysInfo::Compare(
				marshal_as<std::wstring>(actualValue),
				marshal_as<std::wstring>(testValue),
				static_cast<DWORD>(dwMode));
	return ret != 0;
}

bool SysInfoLib::CompareStr(String ^reference, String ^value, ComparisonMethods method)
{
	int ret = SysInfo::CompareStr(
				marshal_as<std::wstring>(reference),
				marshal_as<std::wstring>(value),
				static_cast<DWORD>(method));
	return ret != 0;
}

bool SysInfoLib::CompareVersionString(String ^reference, String ^value, ComparisonMethods method)
{
	int ret = SysInfo::CompareVersionString(
				marshal_as<std::wstring>(reference),
				marshal_as<std::wstring>(value),
				static_cast<DWORD>(method));
	return ret != 0;
}

void SysInfoLib::Merge(String ^categoryName, Dictionary<String^, String^> ^map)
{
	std::wstring szCat = marshal_as<std::wstring>(categoryName);
	if (sysInfo->m_mapInfo.find(szCat) != sysInfo->m_mapInfo.end())
	{
		for each (KeyValuePair<String ^, String ^> p in map)
		{
			std::wstring k = marshal_as<std::wstring>(p.Key);
			if (sysInfo->m_mapInfo[szCat].find(k) == sysInfo->m_mapInfo[szCat].end())
			{
				sysInfo->m_mapInfo[szCat][k] = marshal_as<std::wstring>(p.Value);
			}
		}
	}
	else
	{
		std::map<std::wstring, std::wstring> dict;
		for each (KeyValuePair<String ^, String ^> p in map)
		{
			dict[marshal_as<std::wstring>(p.Key)] = marshal_as<std::wstring>(p.Value);
		}

		sysInfo->m_mapInfo[szCat] = dict;
	}
}

Dictionary<String^, Dictionary<String^, String^> ^> ^ SysInfoLib::GetMap()
{
	auto dict = gcnew Dictionary<String^, Dictionary<String^, String^> ^>();
	for each (auto p in sysInfo->m_mapInfo)
	{
		auto values = gcnew Dictionary<String^, String^>();
		for each (auto k in p.second)
		{
			values->Add(marshal_as<String ^>(k.first), marshal_as<String ^>(k.second));
		}

		dict->Add(marshal_as<String ^>(p.first), values);
	}

	return dict;
}

Dictionary<String^, String^> ^ SysInfoLib::default::get(String ^categoryName)
{
	std::wstring szCat = marshal_as<std::wstring>(categoryName);
	if (sysInfo->m_mapInfo.find(szCat) != sysInfo->m_mapInfo.end())
	{
		auto dict = gcnew Dictionary<String^, String^>();
		for each (auto p in sysInfo->m_mapInfo[szCat])
		{
			dict->Add(marshal_as<String ^>(p.first), marshal_as<String ^>(p.second));
		}

		return dict;
	}

	return nullptr;
}

void SysInfoLib::default::set(String ^categoryName, Dictionary<String^, String^> ^map)
{
	Merge(categoryName, map);
}

}