#include "pch.h"
#include "CDataManger.h"
#include<climits>
CDataManger::CDataManger()
{

}
void CDataManger::Split(CString source, CStringArray& dest, CString division)
{
	dest.RemoveAll();
	int pos = 0;
	int pre_pos = 0;
	while (-1 != pos) {
		pre_pos = pos + 1;
		pos = source.Find(division, (pos + 1));
		if (pos != -1)
			dest.Add(source.Mid(pre_pos, (pos - pre_pos)));
	}
	//最后一个数据找不到分隔符,
	dest.Add(source.Mid(pre_pos));
	DataClean(dest);
}

void CDataManger::DataClean(CStringArray& sarr)
{
	m_sCode = sarr[0];
	if (m_sCode[m_sCode.GetLength() - 1] == '\"')
	{
		m_sCode.Delete(m_sCode.GetLength() - 1);
	}
	if (m_sCode[0] == '\"')
	{
		m_sCode.Delete(0);
	}
	m_arr.SetSize(sarr.GetSize() - 1);
	int len = sarr.GetSize();
	for (int i = 1; i < len; i++)
	{
		CString str = sarr[i];
		str.TrimLeft();
		str.TrimRight();
#if _DEBUG
		if (i == 1 || 7 == i)
		{
			int cnum = str[0];
			int test = 0;
			test++;
		}
#endif
		if (str[str.GetLength() - 1] == '\"')
		{
			str.Delete(str.GetLength() - 1);
		}
		if (str[0] == '\"')
		{
			str.Delete(0);
		}
		m_arr[i - 1] = str;
	}
	DataChange();
}
void CDataManger::Onnext()
{
	CString strline;//定义一个变量用于接收读取的一行内容
	CStdioFile file;//定义一个CStdioFile类的对象 file
	BOOL flag = file.Open("600321.txt", CFile::modeRead);//open函数需要传两个参数，前一个是文件路径，后一个是文件的打开模式
	//file.Seek(m_dwPos, CFile::begin);
	if (file.ReadString(strline) != FALSE)
	{
		m_str = strline;
		Split(m_str, m_dest, ",");
	}
	file.Close();
}

void CDataManger::DataChange()
{
	int len = m_arr.GetSize();
	for (int i = 1; i < len; i += 6)
	{
		vector<double>v;
		v.push_back(atoi(m_arr[i]));
		v.push_back(atoi(m_arr[i + 1]));
		v.push_back(atoi(m_arr[i+2]));
		v.push_back(atoi(m_arr[i+3]));
		v.push_back(atoi(m_arr[i+4]));
		m_VData.push_back(v);
	}
#if _DEBUG
	int a = 0;
	a++;
#endif
}

void CDataManger::SetRange(double& MinRange, double& MaxRange)
{
	MinRange = DBL_MAX;
	MaxRange = DBL_MIN;
	int len1 = m_VData.size();
	int len2 = m_VData[0].size();
	for (int i = 0; i < len1; i++)
	{
		for (int j = 0; j < len2; j++)
		{
			if (m_VData[i][j] < MinRange)
			{
				MinRange = static_cast<double>(m_VData[i][j]);
			}
			if (m_VData[i][j] > MaxRange)
			{
				MaxRange = static_cast<double>(m_VData[i][j]);
			}
		}
	}
}