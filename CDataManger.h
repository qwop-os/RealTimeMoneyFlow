#pragma once
#include <vector>
using std::vector;
class CDataManger
{
public:
	CDataManger();
	void Onnext();
	void Split(CString source, CStringArray& dest, CString division);
	void DataClean(CStringArray& sarr);
	void DataChange();
	void SetRange(double& MinRange, double& MaxRange);
	vector<vector<double>>& GetVData() { return m_VData; }
private:
	CString m_sCode;
	CArray<CString, CString>m_arr;
	CStringArray m_dest;
	CString m_str;
	vector<vector<double>>m_VData;
};

