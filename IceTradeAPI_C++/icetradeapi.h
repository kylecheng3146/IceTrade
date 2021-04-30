#if !defined(AFX_ICETRADEAPI_H__BA24E59C_8AD4_405C_BD90_B9B0549729DA__INCLUDED_)
#define AFX_ICETRADEAPI_H__BA24E59C_8AD4_405C_BD90_B9B0549729DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CICETRADEAPI wrapper class

class CICETRADEAPI : public CWnd
{
protected:
	DECLARE_DYNCREATE(CICETRADEAPI)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xd7b3a04, 0xcacf, 0x44ab, { 0xab, 0xcd, 0x21, 0xe0, 0x79, 0x42, 0x8e, 0x79 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:
	CString GetOrdSubPrefix();
	void SetOrdSubPrefix(LPCTSTR);
	CString GetQueryServerAddr();
	void SetQueryServerAddr(LPCTSTR);
	CString GetQueryProxyAddr();
	void SetQueryProxyAddr(LPCTSTR);
	long GetQueryProxyPort();
	void SetQueryProxyPort(long);
	BOOL GetNeedCA();
	void SetNeedCA(BOOL);
	CString GetCAPath();
	void SetCAPath(LPCTSTR);
	CString GetCAPassword();
	void SetCAPassword(LPCTSTR);
	CString GetOBOrdSubPrefix();
	void SetOBOrdSubPrefix(LPCTSTR);
	long GetCAType();
	void SetCAType(long);

// Operations
public:
	long GetConnectStatus();
	long Login(long nLoginType, LPCTSTR strLoginURL, LPCTSTR strServerAddress, long nServerPort, LPCTSTR strProxyAddress, long nProxyPort, LPCTSTR strCompany, LPCTSTR strProduct, LPCTSTR strRocID, LPCTSTR strBranchID, LPCTSTR strCustID, 
		LPCTSTR strPassword, long nEncodeType);
	long Logout();
	long GetValueHigh(long nDataType, long nDataIndex, long nField);
	long GetValueLow(long nDataType, long nDataIndex, long nField);
	long GetDataCount(long nDataType);
	CString GetString(long nDataType, long nDataIndex, long nField);
	void SubscribeByAccount(long nAccountType, LPCTSTR branch, LPCTSTR account);
	CString GetReportString(long nDataType, long nDataIndex, long nField);
	long GetReportValue(long nDataType, long nDataIndex, long nField);
	long HttpQuery(LPCTSTR Type, LPCTSTR strXML);
	long PlaceFutOrder(VARIANT* pvData);
	long PlaceOptOrder(VARIANT* pvData);
	long PlaceOpt2Order(VARIANT* pvData);
	long PlaceStkOrder(VARIANT* pvData);
	long ReduceFutOrder(long nActType, VARIANT* pvData);
	long ReduceOptOrder(long nActType, VARIANT* pvData);
	long ReduceOpt2Order(long nActType, VARIANT* pvData);
	long ReduceStkOrder(long nActType, VARIANT* pvData);
	long PlaceOBFutOrder(VARIANT* pvData);
	long ReduceOBFutOrder(long nActType, VARIANT* pvData);
	CString GetOBReportString(long nDataType, long nDataIndex, long nField);
	double GetOBReportValue(long nDataType, long nDataIndex, long nField);
	long PlaceFutOrder2(const VARIANT& data);
	long PlaceOptOrder2(const VARIANT& data);
	long PlaceOpt2Order2(const VARIANT& data);
	long PlaceStkOrder2(const VARIANT& data);
	long PlaceOBFutOrder2(const VARIANT& data);
	long ReduceFutOrder2(long nActType, const VARIANT& data);
	long ReduceOptOrder2(long nActType, const VARIANT& data);
	long ReduceOpt2Order2(long nActType, const VARIANT& data);
	long ReduceStkOrder2(long nActType, const VARIANT& data);
	long ReduceOBFutOrder2(long nActType, const VARIANT& data);
	long PlaceFut2Order(VARIANT* pvData);
	long PlaceFut2Order2(const VARIANT& data);
	long ReduceFut2Order(long nActType, VARIANT* pvData);
	long ReduceFut2Order2(long nActType, const VARIANT& data);
	CString ReturnCAPath();
	CString ReturnCAPassword();
	void AboutBox();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICETRADEAPI_H__BA24E59C_8AD4_405C_BD90_B9B0549729DA__INCLUDED_)