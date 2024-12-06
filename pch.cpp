// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。
CString SetUnit(double Price)
{
	CString str;
	if (abs(Price) >= 1.e8)
	{
		Price /= 1.e8;
		str.Format("%.1f亿", Price);
	}
	else if (abs(Price) >= 1.e4)
	{
		Price /= 1.e4;
		str.Format("%d万", static_cast<int>(Price));
	}
	else
	{
		str.Format("%d", static_cast<int>(Price));
	}
	return str;
}

CString SetUnit4(double Price)
{
	CString str;
	if (abs(Price) >= 1.e8)
	{
		Price /= 1.e8;
		str.Format("%.4f亿", Price);
	}
	else if (abs(Price) >= 1.e4)
	{
		Price /= 1.e4;
		str.Format("%.4f万", Price);
	}
	else
	{
		str.Format("%d", static_cast<int>(Price));
	}
	return str;
}