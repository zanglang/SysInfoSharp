// SysInfoSharp.h
#pragma once

#pragma unmanaged
#include "SysInfo/SysInfo.h"

#pragma managed
#include "DxDiagLib.h"
#include "DriverInfoLib.h"
using namespace System;
using namespace System::Collections::Generic;

namespace SysInfoSharp {

	public ref class SysInfoLib
	{
	public:
		SysInfoLib(void);

		// wrapped SysInfo functions
		void		Init(void);
		void		Refresh(void);

		// categories
		int			GetNumCategories(void);
		String ^	GetCategoryName(int index);
		List<String^> ^	GetCategories();
		int			GetNumCategoryContents(String ^categoryName);

		// values
		String ^	GetValue(String ^category, String ^valueName);
		String ^	GetValueName(String ^category, int valueIndex);

		// comparison
		bool		ValueCheck(String ^name, String ^testValue, ComparisonMethods dwMode);
		static bool	Compare(String ^actualValue, String ^testValue, ComparisonMethods dwMode);
		static bool	CompareStr(String ^reference, String ^value, ComparisonMethods method);
		static bool	CompareVersionString(String ^reference, String ^value, ComparisonMethods method);

		// maps
		void	Merge(String ^categoryName, Dictionary<String^, String^> ^map);
		Dictionary<String^, Dictionary<String^, String^> ^> ^ GetMap();

		property Dictionary<String^, String^> ^ default[String ^]
		{
			Dictionary<String^, String^> ^ get(String ^);
			void set(String ^, Dictionary<String^, String^> ^);
		}

	protected:
		SysInfo *sysInfo;
	};
}
