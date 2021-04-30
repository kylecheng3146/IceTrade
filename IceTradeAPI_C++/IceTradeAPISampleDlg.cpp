// IceTradeAPISampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IceTradeAPISample.h"
#include "IceTradeAPISampleDlg.h"
#include "icetradeapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIceTradeAPISampleDlg dialog

CIceTradeAPISampleDlg::CIceTradeAPISampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIceTradeAPISampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIceTradeAPISampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	AfxEnableControlContainer( );
	m_pAPI=NULL;

}

void CIceTradeAPISampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIceTradeAPISampleDlg)
	DDX_Control(pDX, IDC_CHECK_RELOADFLAG, m_ckReloadFlag);
	DDX_Control(pDX, IDC_CHECK_NEEDCA, m_ckNeedCA);
	DDX_Control(pDX, IDC_LIST, m_listbox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIceTradeAPISampleDlg, CDialog)
	//{{AFX_MSG_MAP(CIceTradeAPISampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNNECT, OnButtonConnnect)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, OnButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_STKORDER, OnButtonStkOrder)
	ON_BN_CLICKED(IDC_BUTTON_OPTORDER, OnButtonOptOrder)
	ON_BN_CLICKED(IDC_BUTTON_FUTORDER, OnButtonFutOrder)
	ON_BN_CLICKED(IDC_BUTTON_OBFUTORDER, OnButtonOBFutOrder)
	ON_BN_CLICKED(IDC_BUTTON_REDUCEORDER, OnButtonReduceOrder)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnTabSelchange)
	ON_EN_CHANGE(IDC_EDIT_CAPATH, OnChangeEditCAPath)
	ON_EN_CHANGE(IDC_EDIT_CAPWD, OnChangeEditCAPwd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIceTradeAPISampleDlg message handlers

BOOL CIceTradeAPISampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here	
	GetDlgItem(IDC_EDIT_ENCODE_TYPE)->SetWindowText("1");
	GetDlgItem(IDC_EDIT_SERVER_PORT)->SetWindowText("443");
	GetDlgItem(IDC_EDIT_ORDER_CATYPE)->SetWindowText("1");
	GetDlgItem(IDC_EDIT_ORDER_DAYTRADE)->SetWindowText("N");
	GetDlgItem(IDC_EDIT_ORDER_STOPPRICE)->SetWindowText("0");
	GetDlgItem(IDC_EDIT_ODQTY)->SetWindowText("1");
	GetDlgItem(IDC_EDIT_ORDER_STRIKE)->SetWindowText("0");
	GetDlgItem(IDC_EDIT_ORDER_ODPRICE)->SetWindowText("1");


	m_tab.Create(WS_CHILD|WS_VISIBLE|TCS_TABS|TCS_SINGLELINE|TCS_RAGGEDRIGHT, CRect(14, 470, 655, 495), this, IDC_TAB);
	m_tab.InsertItem(0, "委託回報");
	m_tab.InsertItem(1, "成交回報");
	m_tab.InsertItem(2, "國外委託回報");
	m_tab.InsertItem(3, "國外成交回報");

	m_listOrderReport.Create(WS_BORDER|WS_VISIBLE|WS_CHILD|LVS_REPORT,   CRect(14,495,655,700),this,IDC_LIST);
	m_listOrderReport.InsertColumn( 0 , _T("商品代號"),LVCFMT_LEFT,80);
	m_listOrderReport.InsertColumn( 1 , _T("商品月份"),LVCFMT_LEFT,60);
	m_listOrderReport.InsertColumn( 2 , _T("CALL/PUT"),LVCFMT_LEFT,80);
	m_listOrderReport.InsertColumn( 3 , _T("履約價"),LVCFMT_LEFT,80);
	m_listOrderReport.InsertColumn( 4 , _T("委託書號"),LVCFMT_LEFT,80);
	m_listOrderReport.InsertColumn( 5 , _T("買賣別"),LVCFMT_LEFT,80);
	m_listOrderReport.InsertColumn( 6 , _T("委託價格"),LVCFMT_LEFT,80);
	m_listOrderReport.InsertColumn( 7 , _T("委託數量"),LVCFMT_LEFT,80);
	m_listOrderReport.InsertColumn( 8 , _T("ODKEY"),LVCFMT_LEFT,80);
	m_listOrderReport.InsertColumn( 9 , _T("錯誤代碼"),LVCFMT_LEFT,80);
	m_listOrderReport.InsertColumn( 10 , _T("錯誤訊息"),LVCFMT_LEFT,80);
	m_listOrderReport.InsertColumn( 11 , _T("DataType"),LVCFMT_LEFT,80);
	m_listOrderReport.InsertColumn( 12 , _T("DataIndex"),LVCFMT_LEFT,80);

	m_listDealReport.Create(WS_BORDER|WS_VISIBLE|WS_CHILD|LVS_REPORT,   CRect(14,495,655,700),this,IDC_LIST);
	m_listDealReport.InsertColumn( 0 , _T("商品代碼"),LVCFMT_LEFT,80);
	m_listDealReport.InsertColumn( 1 , _T("商品月份"),LVCFMT_LEFT,60);
	m_listDealReport.InsertColumn( 2 , _T("CALL/PUT"),LVCFMT_LEFT,80);
	m_listDealReport.InsertColumn( 3 , _T("履約價"),LVCFMT_LEFT,80);
	m_listDealReport.InsertColumn( 4 , _T("委託書號"),LVCFMT_LEFT,80);
	m_listDealReport.InsertColumn( 5 , _T("買賣別"),LVCFMT_LEFT,80);
	m_listDealReport.InsertColumn( 6 , _T("成交價格"),LVCFMT_LEFT,80);
	m_listDealReport.InsertColumn( 7 , _T("成交數量"),LVCFMT_LEFT,80);

	m_listObOrderReport.Create(WS_BORDER|WS_VISIBLE|WS_CHILD|LVS_REPORT,   CRect(14,495,655,700),this,IDC_LIST);
	m_listObOrderReport.InsertColumn( 0 , _T("商品代號"),LVCFMT_LEFT,80);
	m_listObOrderReport.InsertColumn( 1 , _T("商品月份"),LVCFMT_LEFT,60);
	m_listObOrderReport.InsertColumn( 2 , _T("CALL/PUT"),LVCFMT_LEFT,80);
	m_listObOrderReport.InsertColumn( 3 , _T("履約價"),LVCFMT_LEFT,80);
	m_listObOrderReport.InsertColumn( 4 , _T("委託書號"),LVCFMT_LEFT,80);
	m_listObOrderReport.InsertColumn( 5 , _T("買賣別"),LVCFMT_LEFT,80);
	m_listObOrderReport.InsertColumn( 6 , _T("委託價格"),LVCFMT_LEFT,80);
	m_listObOrderReport.InsertColumn( 7 , _T("委託數量"),LVCFMT_LEFT,80);
	m_listObOrderReport.InsertColumn( 8 , _T("ODKEY"),LVCFMT_LEFT,80);
	m_listObOrderReport.InsertColumn( 9 , _T("錯誤代碼"),LVCFMT_LEFT,80);
	m_listObOrderReport.InsertColumn( 10 , _T("錯誤訊息"),LVCFMT_LEFT,80);
	m_listObOrderReport.InsertColumn( 11 , _T("FormType"),LVCFMT_LEFT,80);

	m_listObDealReport.Create(WS_BORDER|WS_VISIBLE|WS_CHILD|LVS_REPORT,   CRect(14,495,655,700),this,IDC_LIST);
	m_listObDealReport.InsertColumn( 0 , _T("商品代碼"),LVCFMT_LEFT,80);
	m_listObDealReport.InsertColumn( 1 , _T("商品月份"),LVCFMT_LEFT,60);
	m_listObDealReport.InsertColumn( 2 , _T("CALL/PUT"),LVCFMT_LEFT,80);
	m_listObDealReport.InsertColumn( 3 , _T("履約價"),LVCFMT_LEFT,80);
	m_listObDealReport.InsertColumn( 4 , _T("委託書號"),LVCFMT_LEFT,80);
	m_listObDealReport.InsertColumn( 5 , _T("買賣別"),LVCFMT_LEFT,80);
	m_listObDealReport.InsertColumn( 6 , _T("成交價格"),LVCFMT_LEFT,80);
	m_listObDealReport.InsertColumn( 7 , _T("成交數量"),LVCFMT_LEFT,80);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIceTradeAPISampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIceTradeAPISampleDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIceTradeAPISampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CIceTradeAPISampleDlg::OnButtonConnnect() 
{
	if(m_listOrderReport.GetItemCount()>0)
		m_listOrderReport.DeleteAllItems();
	if(m_listDealReport.GetItemCount()>0)
		m_listDealReport.DeleteAllItems();
	if(m_listObOrderReport.GetItemCount()>0)
		m_listObOrderReport.DeleteAllItems();
	if(m_listObDealReport.GetItemCount()>0)
		m_listObDealReport.DeleteAllItems();
	// TODO: Add your control notification handler code here
	if(m_pAPI)
	{
		delete m_pAPI;
		m_pAPI=NULL;
	}
	m_pAPI=new CICETRADEAPI;
	if(m_pAPI)
	{
		if(!m_pAPI->Create("", WS_CHILD, CRect(0,0,0,0), this, IDC_ICETRADEAPICTRL))
		{
			delete m_pAPI;
			m_pAPI=NULL;
		}
		CString strUrl,strServerAddr,strServerPort,strRocID,strLoginPwd,strEncodeType,strCAPath,strCAPwd;
		GetDlgItem(IDC_EDIT_LOGIN_URL)->GetWindowText(strUrl);
		GetDlgItem(IDC_EDIT_SERVER_ADDR)->GetWindowText(strServerAddr);
		GetDlgItem(IDC_EDIT_SERVER_PORT)->GetWindowText(strServerPort);
		int nServerPort	= _ttoi(strServerPort);
		GetDlgItem(IDC_EDIT_LOGIN_ID)->GetWindowText(strRocID);
		GetDlgItem(IDC_EDIT_LONG_PWD)->GetWindowText(strLoginPwd);
		GetDlgItem(IDC_EDIT_ENCODE_TYPE)->GetWindowText(strEncodeType);
		int nEncodeType = _ttoi(strEncodeType);

		GetDlgItem(IDC_EDIT_CAPATH)->GetWindowText(strCAPath);
		m_pAPI->SetCAPath(strCAPath);
		GetDlgItem(IDC_EDIT_CAPWD)->GetWindowText(strCAPwd);
		m_pAPI->SetCAPassword(strCAPwd);

		int rtn = m_pAPI->Login(1, strUrl, strServerAddr, nServerPort, "", 0, "ICE", "iRealII", strRocID, "", "", strLoginPwd, nEncodeType);
	}
}

void CIceTradeAPISampleDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_pAPI)
	{
		delete m_pAPI;
		m_pAPI=NULL;
	}	
}

void CIceTradeAPISampleDlg::OnButtonDisconnect() 
{
	// TODO: Add your control notification handler code here
	m_pAPI->Logout();
	if(m_listOrderReport.GetItemCount()>0)
		m_listOrderReport.DeleteAllItems();
	if(m_listDealReport.GetItemCount()>0)
		m_listDealReport.DeleteAllItems();
	if(m_listObOrderReport.GetItemCount()>0)
		m_listObOrderReport.DeleteAllItems();
	if(m_listObDealReport.GetItemCount()>0)
		m_listObDealReport.DeleteAllItems();
}

void CIceTradeAPISampleDlg::OnButtonStkOrder() 
{
	// TODO: Add your control notification handler code here
	//證券下單
	VARIANT var;
	VariantInit(&var);
	var.vt = VT_ARRAY | VT_VARIANT;
	SAFEARRAYBOUND bound;
	bound.cElements = 38;
	bound.lLbound = 0;
	var.parray = SafeArrayCreate(VT_VARIANT, 1, &bound);
	VARIANT* args;
	HRESULT hr=SafeArrayAccessData(var.parray, (void**)&args);
	if(FAILED(hr))
	{
		VariantClear(&var);  
		return ;
	}
	for(int i = 0; i < (int)bound.cElements; i ++)
		VariantInit(args + i);

	CString strData;
	//身份證字號
	GetDlgItem(IDC_EDIT_LOGIN_ID)->GetWindowText(strData); 
	args[0].vt = VT_BSTR;
	args[0].bstrVal = strData.AllocSysString();
	//登入密碼
	GetDlgItem(IDC_EDIT_LONG_PWD)->GetWindowText(strData); 
	args[1].vt = VT_BSTR;
	args[1].bstrVal = strData.AllocSysString();
	//分公司代號
	args[2].vt = VT_BSTR;
	args[2].bstrVal = m_strBranch.AllocSysString();
	//帳號
	args[3].vt = VT_BSTR;
	args[3].bstrVal = m_strAccount.AllocSysString();
	//營業員代碼
	args[4].vt = VT_BSTR;
	args[4].bstrVal = m_strAgentID.AllocSysString();
	//來源別
	args[5].vt = VT_BSTR;
	args[5].bstrVal = CString("IC").AllocSysString();
	//商品代碼
	GetDlgItem(IDC_EDIT_SYMBOL_ID)->GetWindowText(strData); 
	args[6].vt = VT_BSTR;
	args[6].bstrVal = strData.AllocSysString();
	//買賣別
	GetDlgItem(IDC_EDIT_ORDER_BS)->GetWindowText(strData); 
	args[7].vt = VT_BSTR;
	args[7].bstrVal = strData.AllocSysString();
	//OrderType  現股=0 融資=1 融券=2
	GetDlgItem(IDC_EDIT_ORDER_ODTYPE)->GetWindowText(strData); 
	args[8].vt = VT_BSTR;
	args[8].bstrVal = strData.AllocSysString();
	//TradeType  N/O/F
	CString strTradeType;
	GetDlgItem(IDC_EDIT_ORDER_TRADETYPE)->GetWindowText(strTradeType); 
	args[9].vt = VT_BSTR;
	args[9].bstrVal = strTradeType.AllocSysString();
	//PriceFlag 限市價 限價=0 市價=1
	GetDlgItem(IDC_EDIT_ORDER_PRICEFLAG)->GetWindowText(strData); 
	args[10].vt = VT_BSTR;
	args[10].bstrVal = strData.AllocSysString();
	//價格 需乘上1000,後三位是小數位數
	GetDlgItem(IDC_EDIT_ORDER_ODPRICE)->GetWindowText(strData);
	long nData = (long)((atof(strData))*1000);
	args[11].vt = VT_I4;
	args[11].lVal = nData;
	//數量
	GetDlgItem(IDC_EDIT_ODQTY)->GetWindowText(strData);
	nData = _ttol(strData);
	args[12].vt = VT_I4;
	args[12].lVal = (strTradeType=="O")?nData:(nData*1000);//非零股則以張為單位，需乘1000。
	//Order Key(User Key)   此筆下單的key,每次下單必須有一個unique的key
	GetDlgItem(IDC_EDIT_ORDER_KEY)->GetWindowText(strData);
	args[13].vt = VT_BSTR;
	args[13].bstrVal = strData.AllocSysString();
	//Market Type   T/O
	GetDlgItem(IDC_EDIT_MARKET_TYPE)->GetWindowText(strData);
	args[23].vt = VT_BSTR;
	args[23].bstrVal = strData.AllocSysString();
	//Day Trade
	GetDlgItem(IDC_EDIT_ORDER_DAYTRADE)->GetWindowText(strData);
	args[26].vt = VT_BSTR;
	args[26].bstrVal = strData.AllocSysString();
	
	SafeArrayUnaccessData(var.parray);

	m_pAPI->SetNeedCA((m_ckNeedCA.GetCheck())?TRUE:FALSE);
	GetDlgItem(IDC_EDIT_ORDER_CATYPE)->GetWindowText(strData);
	nData = _ttol(strData);
	m_pAPI->SetCAType(nData);

	long nResult=m_pAPI->PlaceStkOrder2(var);
	strData.Format(_T("%d"),nResult);
	MessageBox(strData, "", MB_OK|MB_TOPMOST);
	VariantClear(&var);
}

void CIceTradeAPISampleDlg::OnButtonOptOrder() 
{
	// TODO: Add your control notification handler code here
	//選擇權下單
	VARIANT var;
	VariantInit(&var);
	var.vt = VT_ARRAY | VT_VARIANT;
	SAFEARRAYBOUND bound;
	bound.cElements = 38;
	bound.lLbound = 0;
	var.parray = SafeArrayCreate(VT_VARIANT, 1, &bound);
	VARIANT* args;
	HRESULT hr=SafeArrayAccessData(var.parray, (void**)&args);
	if(FAILED(hr))
	{
		VariantClear(&var);
		return;
	}
	for(int i = 0; i < (int)bound.cElements; i ++)
		VariantInit(args + i);

	CString strData;
	//身份證字號
	GetDlgItem(IDC_EDIT_LOGIN_ID)->GetWindowText(strData); 
	args[0].vt = VT_BSTR;
	args[0].bstrVal = strData.AllocSysString();
	//登入密碼
	GetDlgItem(IDC_EDIT_LONG_PWD)->GetWindowText(strData); 
	args[1].vt = VT_BSTR;
	args[1].bstrVal = strData.AllocSysString();
	//分公司代號
	args[2].vt = VT_BSTR;
	args[2].bstrVal = m_strBranch.AllocSysString();
	//帳號
	args[3].vt = VT_BSTR;
	args[3].bstrVal = m_strAccount.AllocSysString();
	//營業員代碼
	args[4].vt = VT_BSTR;
	args[4].bstrVal = m_strAgentID.AllocSysString();
	//來源別
	args[5].vt = VT_BSTR;
	args[5].bstrVal = CString("IC").AllocSysString();
	//商品代碼
	GetDlgItem(IDC_EDIT_SYMBOL_ID)->GetWindowText(strData); 
	args[6].vt = VT_BSTR;
	args[6].bstrVal = strData.AllocSysString();
	//買賣別
	GetDlgItem(IDC_EDIT_ORDER_BS)->GetWindowText(strData); 
	args[7].vt = VT_BSTR;
	args[7].bstrVal = strData.AllocSysString();	
	//OrderType  ROD/IOC/FOK
	GetDlgItem(IDC_EDIT_ORDER_ODTYPE)->GetWindowText(strData); 
	args[8].vt = VT_BSTR;
	args[8].bstrVal = strData.AllocSysString();
	//PriceFlag 限市價 限價=0 市價=1
	GetDlgItem(IDC_EDIT_ORDER_PRICEFLAG)->GetWindowText(strData); 
	args[10].vt = VT_BSTR;
	args[10].bstrVal = strData.AllocSysString();
	//價格 需乘上1000,後三位是小數位數
	GetDlgItem(IDC_EDIT_ORDER_ODPRICE)->GetWindowText(strData);
	long nData = (long)((atof(strData))*1000);
	args[11].vt = VT_I4;
	args[11].lVal = nData;
	//數量
	GetDlgItem(IDC_EDIT_ODQTY)->GetWindowText(strData);
	nData = _ttol(strData);
	args[12].vt = VT_I4;
	args[12].lVal = nData;
	//Order Key(User Key)  此筆下單的key,每次下單必須有一個unique的key
	GetDlgItem(IDC_EDIT_ORDER_KEY)->GetWindowText(strData);
	args[13].vt = VT_BSTR;
	args[13].bstrVal = strData.AllocSysString();
	//倉別
	GetDlgItem(IDC_EDIT_ORDER_OPENCLOSE)->GetWindowText(strData);
	args[14].vt = VT_BSTR;
	args[14].bstrVal = strData.AllocSysString();
	//履約月份
	GetDlgItem(IDC_EDIT_ORDER_MTH)->GetWindowText(strData);
	args[15].vt = VT_BSTR;
	args[15].bstrVal = strData.AllocSysString();
	//Call Put
	GetDlgItem(IDC_EDIT_ORDER_CP)->GetWindowText(strData);
	args[16].vt = VT_BSTR;
	args[16].bstrVal = strData.AllocSysString();
	//Strike Price
	GetDlgItem(IDC_EDIT_ORDER_STRIKE)->GetWindowText(strData);
	nData = (long)((atof(strData))*1000);
	args[17].vt = VT_I4;
	args[17].lVal = nData;
	//Day Trade
	GetDlgItem(IDC_EDIT_ORDER_DAYTRADE)->GetWindowText(strData);
	args[26].vt = VT_BSTR;
	args[26].bstrVal = strData.AllocSysString();

	SafeArrayUnaccessData(var.parray);

	m_pAPI->SetNeedCA((m_ckNeedCA.GetCheck())?TRUE:FALSE);
	GetDlgItem(IDC_EDIT_ORDER_CATYPE)->GetWindowText(strData);
	nData = _ttol(strData);
	m_pAPI->SetCAType(nData);

	int nResult=m_pAPI->PlaceOptOrder2(var);
	strData.Format(_T("%d"),nResult);
	MessageBox(strData, "", MB_OK|MB_TOPMOST);
	VariantClear(&var);
}

void CIceTradeAPISampleDlg::OnButtonFutOrder() 
{
	// TODO: Add your control notification handler code here
	//期貨下單
	VARIANT var;
	VariantInit(&var);
	var.vt = VT_ARRAY | VT_VARIANT;
	SAFEARRAYBOUND bound;
	bound.cElements = 38;
	bound.lLbound = 0;
	var.parray = SafeArrayCreate(VT_VARIANT, 1, &bound);
	VARIANT* args;
	HRESULT hr=SafeArrayAccessData(var.parray, (void**)&args);
	if(FAILED(hr))
	{
		VariantClear(&var);
		return;
	}
	for(int i = 0; i < (int)bound.cElements; i ++)
		VariantInit(args + i);

	CString strData;
	//身份證字號
	GetDlgItem(IDC_EDIT_LOGIN_ID)->GetWindowText(strData); 
	args[0].vt = VT_BSTR;
	args[0].bstrVal = strData.AllocSysString();
	//登入密碼
	GetDlgItem(IDC_EDIT_LONG_PWD)->GetWindowText(strData); 
	args[1].vt = VT_BSTR;
	args[1].bstrVal = strData.AllocSysString();
	//分公司代號
	args[2].vt = VT_BSTR;
	args[2].bstrVal = m_strBranch.AllocSysString();
	//帳號
	args[3].vt = VT_BSTR;
	args[3].bstrVal = m_strAccount.AllocSysString();
	//營業員代碼
	args[4].vt = VT_BSTR;
	args[4].bstrVal = m_strAgentID.AllocSysString();
	//來源別
	args[5].vt = VT_BSTR;
	args[5].bstrVal = CString("IC").AllocSysString();
	//商品代碼
	GetDlgItem(IDC_EDIT_SYMBOL_ID)->GetWindowText(strData); 
	args[6].vt = VT_BSTR;
	args[6].bstrVal = strData.AllocSysString();
	//買賣別
	GetDlgItem(IDC_EDIT_ORDER_BS)->GetWindowText(strData); 
	args[7].vt = VT_BSTR;
	args[7].bstrVal = strData.AllocSysString();		
	//OrderType  ROD/IOC/FOK
	GetDlgItem(IDC_EDIT_ORDER_ODTYPE)->GetWindowText(strData); 
	args[8].vt = VT_BSTR;
	args[8].bstrVal = strData.AllocSysString();
	//PriceFlag 限市價 限價=0 市價=1
	GetDlgItem(IDC_EDIT_ORDER_PRICEFLAG)->GetWindowText(strData); 
	args[10].vt = VT_BSTR;
	args[10].bstrVal = strData.AllocSysString();
	//價格 需乘上1000,後三位是小數位數
	GetDlgItem(IDC_EDIT_ORDER_ODPRICE)->GetWindowText(strData);
	long nData = (long)((atof(strData))*1000);
	args[11].vt = VT_I4;
	args[11].lVal = nData;
	//數量
	GetDlgItem(IDC_EDIT_ODQTY)->GetWindowText(strData);
	nData = _ttol(strData);
	args[12].vt = VT_I4;
	args[12].lVal = nData;
	//Order Key(User Key)  此筆下單的key,每次下單必須有一個unique的key
	GetDlgItem(IDC_EDIT_ORDER_KEY)->GetWindowText(strData);
	args[13].vt = VT_BSTR;
	args[13].bstrVal = strData.AllocSysString();
	//倉別
	GetDlgItem(IDC_EDIT_ORDER_OPENCLOSE)->GetWindowText(strData);
	args[14].vt = VT_BSTR;
	args[14].bstrVal = strData.AllocSysString();
	//商品月份
	GetDlgItem(IDC_EDIT_ORDER_MTH)->GetWindowText(strData);
	args[15].vt = VT_BSTR;
	args[15].bstrVal = strData.AllocSysString();
	//Day Trade
	GetDlgItem(IDC_EDIT_ORDER_DAYTRADE)->GetWindowText(strData);
	args[26].vt = VT_BSTR;
	args[26].bstrVal = strData.AllocSysString();

	SafeArrayUnaccessData(var.parray);

	m_pAPI->SetNeedCA((m_ckNeedCA.GetCheck())?TRUE:FALSE);
	int a = m_ckReloadFlag.GetCheck();
	GetDlgItem(IDC_EDIT_ORDER_CATYPE)->GetWindowText(strData);
	nData = _ttol(strData);
	m_pAPI->SetCAType(nData);

	int nResult=m_pAPI->PlaceFutOrder2(var);
	strData.Format(_T("%d"),nResult);
	MessageBox(strData, "", MB_OK|MB_TOPMOST);
	VariantClear(&var);
}

void CIceTradeAPISampleDlg::OnButtonOBFutOrder() 
{
	// TODO: Add your control notification handler code here
	//國外期貨下單
	VARIANT var;
	VariantInit(&var);
	var.vt = VT_ARRAY | VT_VARIANT;
	SAFEARRAYBOUND bound;
	bound.cElements = 38;
	bound.lLbound = 0;
	var.parray = SafeArrayCreate(VT_VARIANT, 1, &bound);
	VARIANT* args;
	HRESULT hr=SafeArrayAccessData(var.parray, (void**)&args);
	if(FAILED(hr))
	{
		VariantClear(&var);
		return;
	}
	for(int i = 0; i < (int)bound.cElements; i ++)
		VariantInit(args + i);

	CString strData;
	//身份證字號
	GetDlgItem(IDC_EDIT_LOGIN_ID)->GetWindowText(strData); 
	args[0].vt = VT_BSTR;
	args[0].bstrVal = strData.AllocSysString();
	//登入密碼
	GetDlgItem(IDC_EDIT_LONG_PWD)->GetWindowText(strData); 
	args[1].vt = VT_BSTR;
	args[1].bstrVal = strData.AllocSysString();
	//分公司代號
	args[2].vt = VT_BSTR;
	args[2].bstrVal = m_strBranch.AllocSysString();
	//帳號
	args[3].vt = VT_BSTR;
	args[3].bstrVal = m_strAccount.AllocSysString();
	//營業員代碼
	args[4].vt = VT_BSTR;
	args[4].bstrVal = m_strAgentID.AllocSysString();
	//來源別
	args[5].vt = VT_BSTR;
	args[5].bstrVal = CString("IC").AllocSysString();
	//商品代碼
	GetDlgItem(IDC_EDIT_SYMBOL_ID)->GetWindowText(strData); 
	args[6].vt = VT_BSTR;
	args[6].bstrVal = strData.AllocSysString();
	//買賣別
	GetDlgItem(IDC_EDIT_ORDER_BS)->GetWindowText(strData); 
	args[7].vt = VT_BSTR;
	args[7].bstrVal = strData.AllocSysString();
	//OrderType  ROD/IOC/FOK
	GetDlgItem(IDC_EDIT_ORDER_ODTYPE)->GetWindowText(strData); 
	args[8].vt = VT_BSTR;
	args[8].bstrVal = strData.AllocSysString();
	//PriceFlag 限市價 限價=0 市價=1
	GetDlgItem(IDC_EDIT_ORDER_PRICEFLAG)->GetWindowText(strData); 
	args[10].vt = VT_BSTR;
	args[10].bstrVal = strData.AllocSysString();
	//價格 
	GetDlgItem(IDC_EDIT_ORDER_ODPRICE)->GetWindowText(strData);
	LONGLONG llData = (LONGLONG)((atof(strData))*1000000);
	strData.Format(_T("%I64d"),llData);
	args[11].vt = VT_BSTR;
	args[11].bstrVal = strData.AllocSysString();
	//數量
	GetDlgItem(IDC_EDIT_ODQTY)->GetWindowText(strData);
	long nData = _ttol(strData);
	args[12].vt = VT_I4;
	args[12].lVal = nData;
	//Order Key(User Key)  此筆下單的key,每次下單必須有一個unique的key
	GetDlgItem(IDC_EDIT_ORDER_KEY)->GetWindowText(strData);
	args[13].vt = VT_BSTR;
	args[13].bstrVal = strData.AllocSysString();
	//倉別
	GetDlgItem(IDC_EDIT_ORDER_OPENCLOSE)->GetWindowText(strData);
	args[14].vt = VT_BSTR;
	args[14].bstrVal = strData.AllocSysString();
	//商品月份
	GetDlgItem(IDC_EDIT_ORDER_MTH)->GetWindowText(strData);
	args[15].vt = VT_BSTR;
	args[15].bstrVal = strData.AllocSysString();
	//國外交易所
	GetDlgItem(IDC_EDIT_EXCHANGE)->GetWindowText(strData);
	args[24].vt = VT_BSTR;
	args[24].bstrVal = strData.AllocSysString();
	//停損價
	GetDlgItem(IDC_EDIT_ORDER_STOPPRICE)->GetWindowText(strData);
	llData = (LONGLONG)((atof(strData))*1000000);
	strData.Format(_T("%I64d"),llData);
	args[25].vt = VT_BSTR;
	args[25].bstrVal = strData.AllocSysString();
	//Day Trade
	GetDlgItem(IDC_EDIT_ORDER_DAYTRADE)->GetWindowText(strData);
	args[26].vt = VT_BSTR;
	args[26].bstrVal = strData.AllocSysString();
	
	SafeArrayUnaccessData(var.parray);

	m_pAPI->SetNeedCA((m_ckNeedCA.GetCheck())?TRUE:FALSE);
	GetDlgItem(IDC_EDIT_ORDER_CATYPE)->GetWindowText(strData);
	nData = _ttol(strData);
	m_pAPI->SetCAType(nData);

	int nResult=m_pAPI->PlaceOBFutOrder2(var);
	strData.Format(_T("%d"),nResult);
	MessageBox(strData, "", MB_OK|MB_TOPMOST);
	VariantClear(&var);
}

void CIceTradeAPISampleDlg::OnButtonReduceOrder() 
{
	// TODO: Add your control notification handler code here
	//刪單
	CString strData = _T("");
	GetDlgItem(IDC_EDIT_ORDER_ORDNO)->GetWindowText(strData);
	int nType = -1;
	int nIndex = -1;
	if(!strData.IsEmpty())
	{
		for(int i = 0 ; i<m_listOrderReport.GetItemCount(); i++)
		{
			if(m_listOrderReport.GetItemText(i,4) == strData)
			{
				nType = _ttoi(m_listOrderReport.GetItemText(i,11));
				nIndex = _ttoi(m_listOrderReport.GetItemText(i,12));
				break;
			}
		}
		if( nType >= 0 && nIndex >= 0 )
		{
			VARIANT var;
			VariantInit(&var);
			var.vt = VT_ARRAY | VT_VARIANT;
			SAFEARRAYBOUND bound;
			bound.cElements = 38;
			bound.lLbound = 0;
			var.parray = SafeArrayCreate(VT_VARIANT, 1, &bound);
			VARIANT* args;
			HRESULT hr=SafeArrayAccessData(var.parray, (void**)&args);
			if(FAILED(hr))
			{
				VariantClear(&var);
				return;
			}
			for(int i = 0; i < (int)bound.cElements; i ++)
				VariantInit(args + i);

			//身份證字號
			GetDlgItem(IDC_EDIT_LOGIN_ID)->GetWindowText(strData); 
			args[0].vt = VT_BSTR;
			args[0].bstrVal = strData.AllocSysString();
			//登入密碼
			GetDlgItem(IDC_EDIT_LONG_PWD)->GetWindowText(strData); 
			args[1].vt = VT_BSTR;
			args[1].bstrVal = strData.AllocSysString();
			//分公司代號
			strData = m_pAPI->GetReportString(nType, nIndex, 1/*BRANCH_ID*/);
			args[2].vt = VT_BSTR;
			args[2].bstrVal = strData.AllocSysString();
			//帳號
			strData = m_pAPI->GetReportString(nType, nIndex, 39/*CUST_ID*/);
			args[3].vt = VT_BSTR;
			args[3].bstrVal = strData.AllocSysString();
			//營業員代碼
			args[4].vt = VT_BSTR;
			args[4].bstrVal = m_strAgentID.AllocSysString();
			//來源別
			args[5].vt = VT_BSTR;
			args[5].bstrVal = CString("IC").AllocSysString();
			//商品代碼
			strData = m_pAPI->GetReportString(nType, nIndex, 114/*FTR_ID*/);
			args[6].vt = VT_BSTR;
			args[6].bstrVal = strData.AllocSysString();
			//買賣別
			strData = m_pAPI->GetReportString(nType, nIndex, 148/*BUYSELL*/);
			args[7].vt = VT_BSTR;
			args[7].bstrVal = strData.AllocSysString();
			//OrderType  ROD/IOC/FO
			strData = m_pAPI->GetReportString(nType, nIndex, 149/*OD_TYPE*/);
			args[8].vt = VT_BSTR;
			args[8].bstrVal = strData.AllocSysString();
			//PriceFlag 限市價 限價=0 市價=1
			strData = m_pAPI->GetReportString(nType, nIndex, 150/*PRICE_FLAG*/);
			args[10].vt = VT_BSTR;
			args[10].bstrVal = strData.AllocSysString();
			//價格 
			long nData = m_pAPI->GetReportValue(nType, nIndex, 151/*OD_PRICE*/);
			args[11].vt = VT_I4;
			args[11].lVal = nData;
			//數量
			nData = m_pAPI->GetReportValue(nType, nIndex, 156/*OD_QTY*/);
			args[12].vt = VT_I4;
			args[12].lVal = nData;
			//Order Key(User Key)  此筆下單的key,每次下單必須有一個unique的key
			GetDlgItem(IDC_EDIT_ORDER_KEY)->GetWindowText(strData);
			args[13].vt = VT_BSTR;
			args[13].bstrVal = strData.AllocSysString();
			//倉別
			strData = m_pAPI->GetReportString(nType, nIndex, 163/*OD_TYPE*/);
			args[14].vt = VT_BSTR;
			args[14].bstrVal = strData.AllocSysString();
			//商品月份
			strData = m_pAPI->GetReportString(nType, nIndex, 115/*FTR_MTH*/);
			args[15].vt = VT_BSTR;
			args[15].bstrVal = strData.AllocSysString();
			//Call Put
			strData = m_pAPI->GetReportString(nType, nIndex, 116/*CALLPUT*/);
			args[16].vt = VT_BSTR;
			args[16].bstrVal = strData.AllocSysString();
			//Strike Price
			nData = m_pAPI->GetReportValue(nType, nIndex, 117/*STRIKE_PRICE*/);
			args[17].vt = VT_I4;
			args[17].lVal = nData;
			//OrgSeq原始網路單號
			CString strHeader = m_pAPI->GetReportString(nType, nIndex, 208/*F_OD_SEQ*/);
			args[27].vt = VT_BSTR;
			args[27].bstrVal = strHeader.AllocSysString();
			//OrgSource
			strData=m_pAPI->GetReportString(nType, nIndex, 362/*SRC_CODE*/);
			args[28].vt = VT_BSTR;
			args[28].bstrVal = strData.AllocSysString();
			//OrdNo
			strData = m_pAPI->GetReportString(nType, nIndex, 147/*ORDNO*/);
			args[29].vt = VT_BSTR;
			args[29].bstrVal = strData.AllocSysString();
			//Trans Date
			strData=m_pAPI->GetReportString(nType, nIndex, 159/*TRANS_DATE*/);
			args[32].vt = VT_BSTR;
			args[32].bstrVal = strData.AllocSysString();

			SafeArrayUnaccessData(var.parray);
			int nResult;
			if(strHeader == _T("05"))
				nResult=m_pAPI->ReduceFutOrder2(0, var);
			else
				nResult=m_pAPI->ReduceOptOrder2(0, var);
			strData.Format(_T("%d"),nResult);
			MessageBox(strData, "", MB_OK|MB_TOPMOST);
			VariantClear(&var);
		}
	}
}

void CIceTradeAPISampleDlg::OnTabSelchange(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (IsWindow(m_listOrderReport.m_hWnd))
	{
		m_listOrderReport.ShowWindow(SW_HIDE);
		m_listDealReport.ShowWindow(SW_HIDE);
		m_listObOrderReport.ShowWindow(SW_HIDE);
		m_listObDealReport.ShowWindow(SW_HIDE);
		int nSel = m_tab.GetCurSel();
		switch (nSel)
		{
		case 0:
			m_listOrderReport.ShowWindow(SW_SHOW);
			break;
		case 1:
			m_listDealReport.ShowWindow(SW_SHOW);
			break;
		case 2:
			m_listObOrderReport.ShowWindow(SW_SHOW);
			break;
		case 3:
			m_listObDealReport.ShowWindow(SW_SHOW);
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////// ICE Trade API Events
///////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_EVENTSINK_MAP(CIceTradeAPISampleDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CIceTradeAPISampleDlg)
	ON_EVENT(CIceTradeAPISampleDlg, IDC_ICETRADEAPICTRL, 1 /* ConnectStatusChanged */, OnConnectStatusChanged, VTS_I4)
	ON_EVENT(CIceTradeAPISampleDlg, IDC_ICETRADEAPICTRL, 2 /* OnError */, OnError, VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CIceTradeAPISampleDlg, IDC_ICETRADEAPICTRL, 3 /* OrdRestoreComplete */, OnOrdRestoreComplete, VTS_NONE)
	ON_EVENT(CIceTradeAPISampleDlg, IDC_ICETRADEAPICTRL, 4 /* NewOrderReport */, OnNewOrderReport, VTS_I4 VTS_I4)
	ON_EVENT(CIceTradeAPISampleDlg, IDC_ICETRADEAPICTRL, 5 /* ChgOrderReport */, OnChgOrderReport, VTS_I4 VTS_I4)
	ON_EVENT(CIceTradeAPISampleDlg, IDC_ICETRADEAPICTRL, 6 /* NewDealReport */, OnNewDealReport, VTS_I4 VTS_I4)
	ON_EVENT(CIceTradeAPISampleDlg, IDC_ICETRADEAPICTRL, 7 /* ChgDealReport */, OnChgDealReport, VTS_I4 VTS_I4)
	ON_EVENT(CIceTradeAPISampleDlg, IDC_ICETRADEAPICTRL, 13 /* OBOrdRestoreComplete */, OnOBOrdRestoreComplete, VTS_NONE)
	ON_EVENT(CIceTradeAPISampleDlg, IDC_ICETRADEAPICTRL, 14 /* OBNewOrderReport */, OnOBNewOrderReport, VTS_I4 VTS_I4)
	ON_EVENT(CIceTradeAPISampleDlg, IDC_ICETRADEAPICTRL, 15 /* OBChgOrderReport */, OnOBChgOrderReport, VTS_I4 VTS_I4)
	ON_EVENT(CIceTradeAPISampleDlg, IDC_ICETRADEAPICTRL, 16 /* OBNewDealReport */, OnOBNewDealReport, VTS_I4 VTS_I4)
	ON_EVENT(CIceTradeAPISampleDlg, IDC_ICETRADEAPICTRL, 17 /* OBChgDealReport */, OnOBChgDealReport, VTS_I4 VTS_I4)

	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CIceTradeAPISampleDlg::OnConnectStatusChanged(long nStatus) 
{
	TRACE("OnConnectStatusChanged %d\r\n", nStatus);
	if(nStatus==0)
	{
		m_listbox.AddString("離線");
	}
	else if(nStatus==1)
	{
		m_listbox.AddString("連線中");
	}
	if(nStatus==2/*CONNECT_STATUS_CONNECTED*/)
	{
		m_listbox.AddString("連線成功");

		m_pAPI->SetOrdSubPrefix("OrdTW");
		m_pAPI->SetOBOrdSubPrefix("OrdOB");

		int nAccountCount=m_pAPI->GetDataCount(1/*ITS_REPORT_LOGIN_OK*/);
		for(int i=0; i<nAccountCount; i++)
		{
			CString strType=m_pAPI->GetString(1, i, 59/*ACCOUNT_TYPE*/);
            if (strType == "S")
            {
				CString strBranchID=m_pAPI->GetString(1, i, 1/*BRANCH_ID*/);
				CString strCustID=m_pAPI->GetString(1, i, 39/*CUST_ID*/);
                CString strStkName = m_pAPI->GetString(1, i, 40/*CUST_NAME*/);
                CString strStkAgentId = m_pAPI->GetString(1, i, 5/*AGENT_ID*/);
				m_listbox.AddString("分公司代號=" + strBranchID); 
				m_listbox.AddString("股票帳號=" + strCustID);
				m_listbox.AddString("帳號名稱=" + strStkName);
				m_listbox.AddString("營業員=" + strStkAgentId);
				if(!m_ckReloadFlag.GetCheck())
					m_pAPI->SubscribeByAccount(12, strBranchID, strCustID);
                m_pAPI->SubscribeByAccount(0, strBranchID, strCustID);
			}
			else
			{
				m_strBranch=m_pAPI->GetString(1, i, 1/*BRANCH_ID*/);
				m_strAccount=m_pAPI->GetString(1, i, 39/*CUST_ID*/);
                CString strName = m_pAPI->GetString(1, i, 40/*CUST_NAME*/);
                m_strAgentID = m_pAPI->GetString(1, i, 5/*AGENT_ID*/);
				m_listbox.AddString("分公司代號=" + m_strBranch); 
				m_listbox.AddString("期貨帳號=" + m_strAccount);
				m_listbox.AddString("帳號名稱=" + strName);
				m_listbox.AddString("營業員=" + m_strAgentID);				
				if(!m_ckReloadFlag.GetCheck())
					m_pAPI->SubscribeByAccount(12, m_strBranch, m_strAccount);
                m_pAPI->SubscribeByAccount(0, m_strBranch, m_strAccount);
                m_pAPI->SubscribeByAccount(1, m_strBranch, m_strAccount);
			}
		}
	}
}

void CIceTradeAPISampleDlg::OnError(long nErrorType, LPCTSTR ErrCode, LPCTSTR ErrMsg) 
{
	m_listbox.AddString(CString(ErrCode) + _T(":") + CString(ErrMsg));
}

void CIceTradeAPISampleDlg::OnOrdRestoreComplete() 
{
	m_listbox.AddString(_T("RestoreComplete Trigger"));
}

void CIceTradeAPISampleDlg::OnNewOrderReport(long nDataType, long nDataIndex) 
{
	m_listbox.AddString("new order");
	CString strData = m_pAPI->GetReportString(nDataType, nDataIndex, 114/*FTR_ID*/); 
	m_listOrderReport.InsertItem(0, strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 115/*FTR_MTH*/); 
	m_listOrderReport.SetItemText(0, 1 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 116/*CALLPUT*/);
	m_listOrderReport.SetItemText(0, 2 , strData);
	double dData = m_pAPI->GetReportValue(nDataType, nDataIndex, 117/*STRIKE_PRICE*/);
	strData.Format(_T("%.2f"), dData/1000 );
	strData.TrimRight(_T("0"));
	strData.TrimRight(_T("."));
	m_listOrderReport.SetItemText(0, 3 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 147/*ORDNO*/);
	m_listOrderReport.SetItemText(0, 4 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 148/*BUYSELL*/);
	m_listOrderReport.SetItemText(0, 5 , strData);
	dData = m_pAPI->GetReportValue(nDataType, nDataIndex, 151/*OD_PRICE*/);
	strData.Format(_T("%.3f"), dData/1000 );
	strData.TrimRight(_T("0"));
	strData.TrimRight(_T("."));
	m_listOrderReport.SetItemText(0, 6 , strData);
	dData = m_pAPI->GetReportValue(nDataType, nDataIndex, 156/*OD_QTY*/);
	strData.Format(_T("%.f"), dData );
	m_listOrderReport.SetItemText(0, 7 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 201/*OD_KEY*/);
	m_listOrderReport.SetItemText(0, 8 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 68/*ERR_CODE*/);
	m_listOrderReport.SetItemText(0, 9 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 69/*ERR_MSG*/);
	m_listOrderReport.SetItemText(0, 10 , strData);
	strData.Format(_T("%ld"),nDataType);
	m_listOrderReport.SetItemText(0, 11 , strData);
	strData.Format(_T("%ld"),nDataIndex);
	m_listOrderReport.SetItemText(0, 12 , strData);
}

void CIceTradeAPISampleDlg::OnChgOrderReport(long nDataType, long nDataIndex) 
{
	m_listbox.AddString("chg order");
	int nItemCount = m_listOrderReport.GetItemCount();
	int nItemIndex = nItemCount - nDataIndex - 1 ;

	CString strData = m_pAPI->GetReportString(nDataType, nDataIndex, 114/*FTR_ID*/); 
	m_listOrderReport.SetItemText(nItemIndex , 0 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 115/*FTR_MTH*/); 
	m_listOrderReport.SetItemText(nItemIndex , 1 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 116/*CALLPUT*/);
	m_listOrderReport.SetItemText(nItemIndex, 2 , strData);
	double dData = m_pAPI->GetReportValue(nDataType, nDataIndex, 117/*STRIKE_PRICE*/);
	strData.Format(_T("%.2f"), dData/1000 );
	strData.TrimRight(_T("0"));
	strData.TrimRight(_T("."));
	m_listOrderReport.SetItemText(nItemIndex , 3 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 147/*ORDNO*/);
	m_listOrderReport.SetItemText(nItemIndex , 4 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 148/*BUYSELL*/);
	m_listOrderReport.SetItemText(nItemIndex, 5 , strData);
	dData = m_pAPI->GetReportValue(nDataType, nDataIndex, 151/*OD_PRICE*/);
	strData.Format(_T("%.3f"), dData/1000 );
	strData.TrimRight(_T("0"));
	strData.TrimRight(_T("."));
	m_listOrderReport.SetItemText(nItemIndex, 6 , strData);
	dData = m_pAPI->GetReportValue(nDataType, nDataIndex, 156/*OD_QTY*/);
	strData.Format(_T("%.f"), dData );
	m_listOrderReport.SetItemText(nItemIndex, 7 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 201/*OD_KEY*/);
	m_listOrderReport.SetItemText(nItemIndex, 8 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 68/*ERR_CODE*/);
	m_listOrderReport.SetItemText(nItemIndex, 9 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 69/*ERR_MSG*/);
	m_listOrderReport.SetItemText(nItemIndex, 10 , strData);
}

void CIceTradeAPISampleDlg::OnNewDealReport(long nDataType, long nDataIndex) 
{
	m_listbox.AddString("New Deal");
	CString strData = m_pAPI->GetReportString(nDataType, nDataIndex, 114/*FTR_ID*/); 
	m_listDealReport.InsertItem(0, strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 115/*FTR_MTH*/); 
	m_listDealReport.SetItemText(0, 1 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 116/*CALLPUT*/);
	m_listDealReport.SetItemText(0, 2 , strData);
	double dData = m_pAPI->GetReportValue(nDataType, nDataIndex, 117/*STRIKE_PRICE*/);
	strData.Format(_T("%.3f"), dData/1000 );
	strData.TrimRight(_T("0"));
	strData.TrimRight(_T("."));
	m_listDealReport.SetItemText(0, 3 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 147/*ORDNO*/);
	m_listDealReport.SetItemText(0, 4 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 148/*BUYSELL*/);
	m_listDealReport.SetItemText(0, 5 , strData);
	dData = m_pAPI->GetReportValue(nDataType, nDataIndex, 151/*OD_PRICE*/);
	strData.Format(_T("%.2f"), dData/1000 );
	strData.TrimRight(_T("0"));
	strData.TrimRight(_T("."));
	m_listDealReport.SetItemText(0, 6 , strData);
	dData = m_pAPI->GetReportValue(nDataType, nDataIndex, 364/*DEAL_QTY*/);
	strData.Format(_T("%.f"), dData );
	m_listDealReport.SetItemText(0, 7 , strData);
}

void CIceTradeAPISampleDlg::OnChgDealReport(long nDataType, long nDataIndex) 
{
	m_listbox.AddString("chg Deal");
	int nItemCount = m_listDealReport.GetItemCount();
	int nItemIndex = nItemCount - nDataIndex -1;

	CString strData = m_pAPI->GetReportString(nDataType, nDataIndex, 114/*FTR_ID*/); 
	m_listDealReport.SetItemText(nItemIndex , 0 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 115/*FTR_MTH*/); 
	m_listDealReport.SetItemText(nItemIndex, 1 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 116/*CALLPUT*/);
	m_listDealReport.SetItemText(nItemIndex, 2 , strData);
	double dData = m_pAPI->GetReportValue(nDataType, nDataIndex, 117/*STRIKE_PRICE*/);
	strData.Format(_T("%.3f"), dData/1000 );
	strData.TrimRight(_T("0"));
	strData.TrimRight(_T("."));
	m_listDealReport.SetItemText(nItemIndex, 3 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 147/*ORDNO*/);
	m_listDealReport.SetItemText(nItemIndex, 4 , strData);
	strData = m_pAPI->GetReportString(nDataType, nDataIndex, 148/*BUYSELL*/);
	m_listDealReport.SetItemText(nItemIndex, 5 , strData);
	dData = m_pAPI->GetReportValue(nDataType, nDataIndex, 151/*OD_PRICE*/);
	strData.Format(_T("%.2f"), dData/1000 );
	strData.TrimRight(_T("0"));
	strData.TrimRight(_T("."));
	m_listDealReport.SetItemText(nItemIndex, 6 , strData);
	dData = m_pAPI->GetReportValue(nDataType, nDataIndex, 364/*DEAL_QTY*/);
	strData.Format(_T("%.f"), dData );
	m_listDealReport.SetItemText(nItemIndex, 7 , strData);
}

void CIceTradeAPISampleDlg::OnOBOrdRestoreComplete() 
{
	m_listbox.AddString(_T("OB RestoreComplete Trigger"));
}

void CIceTradeAPISampleDlg::OnOBNewOrderReport(long nDataType, long nDataIndex) 
{
	m_listbox.AddString("new Oborder");
	CString strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 114/*FTR_ID*/); 
	m_listObOrderReport.InsertItem(0, strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 115/*FTR_MTH*/); 
	m_listObOrderReport.SetItemText(0, 1 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 116/*CALLPUT*/);
	m_listObOrderReport.SetItemText(0, 2 , strData);
	double dData = m_pAPI->GetOBReportValue(nDataType, nDataIndex, 117/*STRIKE_PRICE*/);
	strData.Format(_T("%.2f"), dData/1000 );
	strData.TrimRight(_T("0"));
	strData.TrimRight(_T("."));
	m_listObOrderReport.SetItemText(0, 3 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 147/*ORDNO*/);
	m_listObOrderReport.SetItemText(0, 4 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 148/*BUYSELL*/);
	m_listObOrderReport.SetItemText(0, 5 , strData);
	dData = m_pAPI->GetOBReportValue(nDataType, nDataIndex, 151/*OD_PRICE*/);
	strData.Format(_T("%.6f"), dData/1000000 );
	strData.TrimRight(_T("0"));
	strData.TrimRight(_T("."));
	m_listObOrderReport.SetItemText(0, 6 , strData);
	dData = m_pAPI->GetOBReportValue(nDataType, nDataIndex, 156/*OD_QTY*/);
	strData.Format(_T("%.f"), dData );
	m_listObOrderReport.SetItemText(0, 7 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 201/*OD_KEY*/);
	m_listObOrderReport.SetItemText(0, 8 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 68/*ERR_CODE*/);
	m_listObOrderReport.SetItemText(0, 9 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 69/*ERR_MSG*/);
	m_listObOrderReport.SetItemText(0, 10 , strData);
	dData = m_pAPI->GetOBReportValue(nDataType, nDataIndex, 352/*FORM_TYPE*/);
	strData.Format(_T("%.f"), dData );
	m_listObOrderReport.SetItemText(0, 11 , strData);
}

void CIceTradeAPISampleDlg::OnOBChgOrderReport(long nDataType, long nDataIndex) 
{
	m_listbox.AddString("chg Oborder");
	int nItemCount = m_listObOrderReport.GetItemCount();
	int nItemIndex = nItemCount - nDataIndex -1;

	CString strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 114/*FTR_ID*/); 
	m_listObOrderReport.SetItemText(nItemIndex , 0 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 115/*FTR_MTH*/); 
	m_listObOrderReport.SetItemText(nItemIndex , 1 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 116/*CALLPUT*/);
	m_listObOrderReport.SetItemText(nItemIndex, 2 , strData);
	double dData = m_pAPI->GetOBReportValue(nDataType, nDataIndex, 117/*STRIKE_PRICE*/);
	strData.Format(_T("%.2f"), dData/1000 );
	strData.TrimRight(_T("0"));
	strData.TrimRight(_T("."));
	m_listObOrderReport.SetItemText(nItemIndex , 3 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 147/*ORDNO*/);
	m_listObOrderReport.SetItemText(nItemIndex , 4 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 148/*BUYSELL*/);
	m_listObOrderReport.SetItemText(nItemIndex, 5 , strData);
	dData = m_pAPI->GetOBReportValue(nDataType, nDataIndex, 151/*OD_PRICE*/);
	strData.Format(_T("%.6f"), dData/1000000 );
	strData.TrimRight(_T("0"));
	strData.TrimRight(_T("."));
	m_listObOrderReport.SetItemText(nItemIndex, 6 , strData);
	dData = m_pAPI->GetOBReportValue(nDataType, nDataIndex, 156/*OD_QTY*/);
	strData.Format(_T("%.f"), dData );
	m_listOrderReport.SetItemText(nItemIndex, 7 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 201/*OD_KEY*/);
	m_listObOrderReport.SetItemText(nItemIndex, 8 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 68/*ERR_CODE*/);
	m_listObOrderReport.SetItemText(nItemIndex, 9 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 69/*ERR_MSG*/);
	m_listObOrderReport.SetItemText(nItemIndex, 10 , strData);
	dData = m_pAPI->GetOBReportValue(nDataType, nDataIndex, 352/*FORM_TYPE*/);
	strData.Format(_T("%.f"), dData );
	m_listObOrderReport.SetItemText(0, 11 , strData);
}

void CIceTradeAPISampleDlg::OnOBNewDealReport(long nDataType, long nDataIndex) 
{
	m_listbox.AddString("new Obdeal");
	CString strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 114/*FTR_ID*/); 
	m_listObDealReport.InsertItem(0, strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 115/*FTR_MTH*/); 
	m_listObDealReport.SetItemText(0, 1 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 116/*CALLPUT*/);
	m_listObDealReport.SetItemText(0, 2 , strData);
	double dData = m_pAPI->GetOBReportValue(nDataType, nDataIndex, 117/*STRIKE_PRICE*/);
	strData.Format(_T("%.3f"), dData/1000 );
	strData.TrimRight(_T("0"));
	strData.TrimRight(_T("."));
	m_listObDealReport.SetItemText(0, 3 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 147/*ORDNO*/);
	m_listObDealReport.SetItemText(0, 4 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 148/*BUYSELL*/);
	m_listObDealReport.SetItemText(0, 5 , strData);
	dData = m_pAPI->GetOBReportValue(nDataType, nDataIndex, 257/*OBOD_PRICE*/);
	strData.Format(_T("%.6f"), dData/1000000 );
	strData.TrimRight(_T("0"));
	strData.TrimRight(_T("."));
	m_listObDealReport.SetItemText(0, 6 , strData);
	dData = m_pAPI->GetOBReportValue(nDataType, nDataIndex, 364/*DEAL_QTY*/);
	strData.Format(_T("%.f"), dData );
	m_listObDealReport.SetItemText(0, 7 , strData);
}
void CIceTradeAPISampleDlg::OnOBChgDealReport(long nDataType, long nDataIndex) 
{
	m_listbox.AddString("chg Obdeal");
	int nItemCount = m_listObDealReport.GetItemCount();
	int nItemIndex = nItemCount - nDataIndex - 1;

	CString strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 114/*FTR_ID*/); 
	m_listObDealReport.SetItemText(nItemIndex , 0 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 115/*FTR_MTH*/); 
	m_listObDealReport.SetItemText(nItemIndex , 1 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 116/*CALLPUT*/);
	m_listObDealReport.SetItemText(nItemIndex , 2 , strData);
	double dData = m_pAPI->GetOBReportValue(nDataType, nDataIndex, 117/*STRIKE_PRICE*/);
	strData.Format(_T("%.3f"), dData/1000 );
	strData.TrimRight(_T("0"));
	strData.TrimRight(_T("."));
	m_listObDealReport.SetItemText(nItemIndex , 3 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 147/*ORDNO*/);
	m_listObDealReport.SetItemText(nItemIndex , 4 , strData);
	strData = m_pAPI->GetOBReportString(nDataType, nDataIndex, 148/*BUYSELL*/);
	m_listObDealReport.SetItemText(nItemIndex , 5 , strData);
	dData = m_pAPI->GetOBReportValue(nDataType, nDataIndex, 257/*OBOD_PRICE*/);
	strData.Format(_T("%.6f"), dData/1000000 );
	strData.TrimRight(_T("0"));
	strData.TrimRight(_T("."));
	m_listObDealReport.SetItemText(nItemIndex , 6 , strData);
	dData = m_pAPI->GetOBReportValue(nDataType, nDataIndex, 364/*DEAL_QTY*/);
	strData.Format(_T("%.f"), dData );
	m_listObDealReport.SetItemText(nItemIndex , 7 , strData);
}

void CIceTradeAPISampleDlg::OnChangeEditCAPath() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(m_pAPI)
	{
		CString strCAPath;
		GetDlgItem(IDC_EDIT_CAPATH)->GetWindowText(strCAPath);
		m_pAPI->SetCAPath(strCAPath);
	}	
}

void CIceTradeAPISampleDlg::OnChangeEditCAPwd() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(m_pAPI)
	{
		CString strCAPwd;
		GetDlgItem(IDC_EDIT_CAPWD)->GetWindowText(strCAPwd);
		m_pAPI->SetCAPassword(strCAPwd);
	}
}
