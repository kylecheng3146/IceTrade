// IceTradeAPISampleDlg.h : header file
//

#if !defined(AFX_ICETRADEAPISAMPLEDLG_H__3AEB47F4_3E54_4597_BEBA_AE13EAB8F80C__INCLUDED_)
#define AFX_ICETRADEAPISAMPLEDLG_H__3AEB47F4_3E54_4597_BEBA_AE13EAB8F80C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CIceTradeAPISampleDlg dialog
class CICETRADEAPI;
class CIceTradeAPISampleDlg : public CDialog
{
// Construction
public:
	CIceTradeAPISampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIceTradeAPISampleDlg)
	enum { IDD = IDD_ICETRADEAPISAMPLE_DIALOG };
	CButton	m_ckReloadFlag;
	CButton	m_ckNeedCA;
	CListBox	m_listbox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIceTradeAPISampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strAgentID;
	CString m_strAccount;
	CString m_strBranch;
	HICON m_hIcon;
	CICETRADEAPI* m_pAPI;

	CListCtrl m_listOrderReport;
	CListCtrl m_listDealReport;
	CListCtrl m_listObOrderReport;
	CListCtrl m_listObDealReport;

	CTabCtrl m_tab;
	// Generated message map functions
	//{{AFX_MSG(CIceTradeAPISampleDlg)
	afx_msg void OnConnectStatusChanged(long nStatus);
	afx_msg void OnError(long nErrorType, LPCTSTR ErrCode, LPCTSTR ErrMsg);
	afx_msg void OnOrdRestoreComplete();
	afx_msg void OnNewOrderReport(long nDataType, long nDataIndex);
	afx_msg void OnChgOrderReport(long nDataType, long nDataIndex);
	afx_msg void OnNewDealReport(long nDataType, long nDataIndex);
	afx_msg void OnChgDealReport(long nDataType, long nDataIndex);
	afx_msg void OnOBOrdRestoreComplete();
	afx_msg void OnOBNewOrderReport(long nDataType, long nDataIndex);
	afx_msg void OnOBChgOrderReport(long nDataType, long nDataIndex);
	afx_msg void OnOBNewDealReport(long nDataType, long nDataIndex);
	afx_msg void OnOBChgDealReport(long nDataType, long nDataIndex);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonConnnect();
	afx_msg void OnDestroy();
	afx_msg void OnButtonDisconnect();
	afx_msg void OnButtonStkOrder();
	afx_msg void OnButtonOptOrder();
	afx_msg void OnButtonFutOrder();
	afx_msg void OnButtonOBFutOrder();
	afx_msg void OnButtonReduceOrder();
	afx_msg void OnTabSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditCAPath();
	afx_msg void OnChangeEditCAPwd();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICETRADEAPISAMPLEDLG_H__3AEB47F4_3E54_4597_BEBA_AE13EAB8F80C__INCLUDED_)
