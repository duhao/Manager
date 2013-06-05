
// ManagerDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "Manager.h"
#include "ManagerDlg.h"
#include "afxdialogex.h"
#include "Enconn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CManagerDlg 对话框




CManagerDlg::CManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_Cpro);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RichEdit);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_SLIDER1, m_enable);
	DDX_Control(pDX, IDC_SLIDER2, m_TargetGain);
	DDX_Control(pDX, IDC_SLIDER3, m_AttactTime);
	//  DDX_Control(pDX, IDC_SLIDER4, m_Allowed);
	//  DDX_Control(pDX, IDC_SLIDER5, m_Hysteresis);
	//  DDX_Control(pDX, IDC_SLIDER6, m_Threshold);
	DDX_Control(pDX, IDC_SLIDER4, m_DecayTime);
	DDX_Control(pDX, IDC_SLIDER5, m_Allowed);
	DDX_Control(pDX, IDC_SLIDER6, m_Hysteresis);
	DDX_Control(pDX, IDC_SLIDER7, m_Threshold);
	DDX_Control(pDX, IDC_SLIDER8, m_Stepping);
}

BEGIN_MESSAGE_MAP(CManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CManagerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CManagerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CManagerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CManagerDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CManagerDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CManagerDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON22, &CManagerDlg::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON7, &CManagerDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON12, &CManagerDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON8, &CManagerDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON11, &CManagerDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON10, &CManagerDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON9, &CManagerDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON13, &CManagerDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CManagerDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON19, &CManagerDlg::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, &CManagerDlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON21, &CManagerDlg::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON23, &CManagerDlg::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON16, &CManagerDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON15, &CManagerDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON17, &CManagerDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CManagerDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON24, &CManagerDlg::OnBnClickedButton24)
	ON_BN_CLICKED(IDOK, &CManagerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON25, &CManagerDlg::OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON26, &CManagerDlg::OnBnClickedButton26)
	ON_BN_CLICKED(IDC_BUTTON27, &CManagerDlg::OnBnClickedButton27)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CManagerDlg 消息处理程序

BOOL CManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	conn = new Enconn();
	conn->SetMessageHwnd(m_hWnd);
	conn->SetRichHandle(&m_RichEdit);
	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_IPADDRESS1)->SetWindowText(_T("192.168.9.106"));
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T("123"));	
	GetDlgItem(IDC_EDIT5)->SetWindowText(_T("1024"));	
	GetDlgItem(IDC_EDIT4)->SetWindowText(_T("768"));	
	GetDlgItem(IDC_EDIT2)->SetWindowText(_T("30"));	
	GetDlgItem(IDC_EDIT3)->SetWindowText(_T("1024"));
	GetDlgItem(IDC_EDIT13)->SetWindowText(_T("4"));
	GetDlgItem(IDC_EDIT9)->SetWindowText(_T("20"));
	GetDlgItem(IDC_EDIT10)->SetWindowText(_T("20"));
	GetDlgItem(IDC_EDIT11)->SetWindowText(_T("50"));
	GetDlgItem(IDC_EDIT12)->SetWindowText(_T("1"));

	GetDlgItem(IDC_EDIT7)->SetWindowText(_T("10"));
	GetDlgItem(IDC_EDIT8)->SetWindowText(_T("1"));

	GetDlgItem(IDC_EDIT15)->SetWindowText(_T("0"));
	GetDlgItem(IDC_EDIT16)->SetWindowText(_T("126"));
	GetDlgItem(IDC_EDIT17)->SetWindowText(_T("0"));


	//m_Cpro.SetWindowTextW(_T("ENC110"));
	m_Cpro.SetCurSel(0);

	m_enable.SetRange(0,1);
	m_TargetGain.SetRange(0,7);
	m_AttactTime.SetRange(0,3);
	m_DecayTime.SetRange(0,3);
	m_Allowed.SetRange(0,63);
	m_Hysteresis.SetRange(0,3);
	m_Threshold.SetRange(0,31);
	m_Stepping.SetRange(0,1);
	m_Allowed.SetPos(63);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CManagerDlg::PreTranslateMessage(MSG* pMsg)  
{  
	  
   	switch(pMsg->message) {
	case RM_ST_FAIL:	//连接失败		
		GetDlgItem(IDC_STATIC1)->SetWindowTextW(_T("未连接"));
		::AfxMessageBox(_T("连接失败"));
		GetDlgItem(IDC_BUTTON1)->SetWindowTextW(_T("连接"));
		(GetDlgItem(IDC_BUTTON1))->EnableWindow(true);
		break;
	case RM_ST_SUCCESS://连接成功
		//::AfxMessageBox(_T(""));
		GetDlgItem(IDC_STATIC1)->SetWindowTextW(_T("已连接"));
		GetDlgItem(IDC_BUTTON1)->SetWindowTextW(_T("断开"));
		(GetDlgItem(IDC_BUTTON1))->EnableWindow(true);
		break;
	case RM_ST_CONNING://连接中		
		GetDlgItem(IDC_STATIC1)->SetWindowTextW(_T("连接中..."));
		break;	
	case RM_DISCONN://断开
		GetDlgItem(IDC_STATIC1)->SetWindowTextW(_T("已断开"));
		(GetDlgItem(IDC_BUTTON1))->EnableWindow(true);
		GetDlgItem(IDC_BUTTON1)->SetWindowTextW(_T("连接"));
		::AfxMessageBox(_T("编码器断开"));
		break;
	case RM_PASSWD_ERR://密码错误
		GetDlgItem(IDC_STATIC1)->SetWindowTextW(_T("已断开"));
		(GetDlgItem(IDC_BUTTON1))->EnableWindow(true);
		GetDlgItem(IDC_BUTTON1)->SetWindowTextW(_T("连接"));
		::AfxMessageBox(_T("连接密码错误"));
		break;	
	case RM_UPDATE_STATUS://升级状态				
		m_Progress.SetPos(pMsg->lParam);	
	
		break;
	default:
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
void CManagerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	char ip[20];	
	TCHAR passwd[20];
	size_t sz=0;
	CString str;
	conn->Enctype=m_Cpro.GetCurSel();	
	GetDlgItem(IDC_IPADDRESS1)->GetWindowTextW(str);	
	wcstombs_s(&sz,ip,str.GetBuffer(0),str.GetLength());
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(str);	
	_tcscpy_s(passwd,20,str.GetBuffer());
	str.ReleaseBuffer();
	(GetDlgItem(IDC_BUTTON1))->EnableWindow(false);
	if(conn->Connflag==0)
	{
		conn->Connect(0,ip,3100,passwd,0);//连接			
	}
	else 
	{
		conn->Disconnect();//断开		
	};
	
	//Beep(900,300);
}




void CManagerDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	char data[128];
	int qulity=0;
	int bitrate=256;
	CString str;
	SizeType  sizeType = {0};
	GetDlgItem(IDC_EDIT5)->GetWindowTextW(str);	
	sizeType.width=_ttoi(str);
	GetDlgItem(IDC_EDIT4)->GetWindowTextW(str);	
	sizeType.height=_ttoi(str);
	GetDlgItem(IDC_EDIT3)->GetWindowTextW(str);	
	bitrate=_ttoi(str);
	if(sizeType.width==0 && sizeType.height==0)
		sizeType.nflag=0;
	else
		sizeType.nflag=1;
	if(conn->Enctype==0)
	{
		conn->SendCmd((char*)&sizeType,sizeof(sizeType),MSG_FIX_RESOLUTION);
	}
	else
	{		
		data[0]=qulity;
		memcpy(data+1,&sizeType.width,4);
		memcpy(data+5,&sizeType.height,4);
		memcpy(data+9,&bitrate,4);
		conn->SendCmd(data,13,MSG_QUALITYVALUE);
	}
	
}


void CManagerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

}


void CManagerDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	char sound=1;
			
	conn->SendCmd(&sound,1,MSG_MUTE);
		
}


void CManagerDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	char sound=0;
			
	conn->SendCmd(&sound,1,MSG_MUTE);
}


void CManagerDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	int cmd = 1;//=1表示请求自动索引，=2表示立即强制一个索引
	conn->SendCmd((char*)&cmd,sizeof(cmd),MSG_PIC_DATA);
}


void CManagerDlg::OnBnClickedButton22()
{
	// TODO: 在此添加控件通知处理程序代码
	int cmd = 2;//=1表示请求自动索引，=2表示立即强制一个索引
	conn->SendCmd((char*)&cmd,sizeof(cmd),MSG_PIC_DATA);
}


void CManagerDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码	
	int cmd = 2;//=1表示请求自动索引，=2表示立即强制一个索引
	conn->SendCmd((char*)&cmd,sizeof(cmd),MSG_PIC_DATAEX);
}


void CManagerDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	low_bitrate lb;

	lb.nFrame=30;
	lb.nBitrate=2000;
	lb.nWidth=352;
	lb.nHeight=288;

	conn->SendCmd((char*)&lb,sizeof(lb),MSG_LOW_BITRATE);
}


void CManagerDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码

	char cmd=1;

	conn->SendCmd(&cmd,1,MSG_LOCK_SCREEN);
}


void CManagerDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	char pData[256] = {0};
	int type,speed,add;
	type=12;
	speed=1;
	add=1;
	memcpy(pData, &type, sizeof(type));
	memcpy(pData+4, &speed, sizeof(speed));
	memcpy(pData+4+4, &add, sizeof(add));
	conn->SendCmd((char*)&pData,12,MSG_FARCTRL);
}


void CManagerDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	char pData[256] = {0};
	int type,speed,add;
	type=12;
	speed=0;
	add=1;
	memcpy(pData, &type, sizeof(type));
	memcpy(pData+4, &speed, sizeof(speed));
	memcpy(pData+4+4, &add, sizeof(add));
	conn->SendCmd((char*)&pData,12,MSG_FARCTRL);
}


void CManagerDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	char cmd=0;

	conn->SendCmd(&cmd,1,MSG_LOCK_SCREEN);
}


void CManagerDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	char pData[256] = {0};
	int type,speed,add;
	CString str;
	type=11;
	GetDlgItem(IDC_EDIT7)->GetWindowTextW(str);	
	speed=_ttoi(str);
	GetDlgItem(IDC_EDIT8)->GetWindowTextW(str);	
	add=_ttoi(str);
	memcpy(pData, &type, sizeof(type));
	memcpy(pData+4, &speed, sizeof(speed));
	memcpy(pData+4+4, &add, sizeof(add));
	conn->SendCmd((char*)&pData,12,MSG_FARCTRL);
}


void CManagerDlg::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	char pData[256] = {0};
	int type,speed,add;
	CString str;
	type=10;
	GetDlgItem(IDC_EDIT7)->GetWindowTextW(str);	
	speed=_ttoi(str);
	GetDlgItem(IDC_EDIT8)->GetWindowTextW(str);	
	add=_ttoi(str);
	memcpy(pData, &type, sizeof(type));
	memcpy(pData+4, &speed, sizeof(speed));
	memcpy(pData+4+4, &add, sizeof(add));
	conn->SendCmd((char*)&pData,12,MSG_FARCTRL);
}


void CManagerDlg::OnBnClickedButton19()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDlg(TRUE, _T("bin"), NULL, 0, _T("文件(*.bin)|*.bin||"), this);   
	CString strFilePath;	
	if(IDOK==fileDlg.DoModal())
	{

		conn->filePath= fileDlg.GetPathName();  		   
		m_Progress.SetRange(0,100);
		m_Progress.SetPos(0);
		conn->Upload(strFilePath);
	}
}


void CManagerDlg::OnBnClickedButton20()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDlg(TRUE, _T("png"), NULL, 0, _T("图片(*.png)|*.png||"), this);   
	CString strFilePath;
	CString str;
	LogoInfo logoif;
	GetDlgItem(IDC_EDIT13)->GetWindowTextW(str);	
	logoif.alpha=_ttoi(str);	
	GetDlgItem(IDC_EDIT12)->GetWindowTextW(str);
	logoif.enable=_ttoi(str);
	memset(logoif.filename,0,16);	
	WideCharToMultiByte(CP_ACP,NULL,_T("logo.png"),_tcslen(_T("logo.png")),logoif.filename,8,NULL,FALSE);
	logoif.isThrough=0;
	GetDlgItem(IDC_EDIT9)->GetWindowTextW(str);
	logoif.x=_ttoi(str);
	GetDlgItem(IDC_EDIT10)->GetWindowTextW(str);
	logoif.y=_ttoi(str);
	logoif.width=20;
	logoif.height=20;
	logoif.errcode=0;
	if(IDOK==fileDlg.DoModal())
	{
	
		strFilePath = fileDlg.GetPathName();   
		   // SetDlgItemText(IDC_OPEN_EDIT, strFilePath); 
		conn->UploadImg(strFilePath,logoif,1);
	}

}


void CManagerDlg::OnBnClickedButton21()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDlg(TRUE, _T("png"), NULL, 0, _T("图片(*.png)|*.png||"), this);   
	CString strFilePath;
	CString str;
	LogoInfo logoif;
	GetDlgItem(IDC_EDIT11)->GetWindowTextW(str);	
	logoif.alpha=_ttoi(str);	
	GetDlgItem(IDC_EDIT12)->GetWindowTextW(str);
	logoif.enable=_ttoi(str);
	memset(logoif.filename,0,16);	
	WideCharToMultiByte(CP_ACP,NULL,_T("logo.png"),_tcslen(_T("logo.png")),logoif.filename,8,NULL,FALSE);
	logoif.isThrough=2;
	GetDlgItem(IDC_EDIT9)->GetWindowTextW(str);
	logoif.x=_ttoi(str);
	GetDlgItem(IDC_EDIT10)->GetWindowTextW(str);
	logoif.y=_ttoi(str);
	logoif.width=20;
	logoif.height=20;
	logoif.errcode=0;
	strFilePath = fileDlg.GetPathName();   
	   // SetDlgItemText(IDC_OPEN_EDIT, strFilePath); 
	conn->SetImage(logoif);
	
}


void CManagerDlg::OnBnClickedButton23()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDlg(FALSE, NULL, NULL, 0, _T("文件(*.*)|*.*||"), this);   
	CString strFilePath;	
	if(IDOK==fileDlg.DoModal())
	{
		
		strFilePath= fileDlg.GetPathName();  	
		conn->H264File.Open(strFilePath+".264",CFile::modeCreate | CFile::modeWrite);
		conn->AacFile.Open(strFilePath+".aac",CFile::modeCreate | CFile::modeWrite);
		conn->saveStream=1;
	}
}


void CManagerDlg::OnBnClickedButton16()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CManagerDlg::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CManagerDlg::OnBnClickedButton17()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CManagerDlg::OnBnClickedButton18()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CManagerDlg::OnBnClickedButton24()
{
	// TODO: 在此添加控件通知处理程序代码
	conn->saveStream=0;
	conn->H264File.Close();
	conn->AacFile.Close();
		
}


void CManagerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CManagerDlg::OnBnClickedButton25()
{
	// TODO: 在此添加控件通知处理程序代码
	AllocConsole();
	freopen("CONOUT$","w",stdout);
}


void CManagerDlg::OnBnClickedButton26()
{
	// TODO: 在此添加控件通知处理程序代码
	char pData[256] = {0};
	int val,addr;
	CString str;
	
	GetDlgItem(IDC_EDIT15)->GetWindowTextW(str);	
	val=_ttoi(str);		
	//AGC-A
	addr=26;
	memcpy(pData, &addr, sizeof(addr));
	memcpy(pData+4, &val, sizeof(val));
	conn->SendCmd((char*)&pData,8,0xA0);
	addr=29;
	memcpy(pData, &addr, sizeof(addr));
	memcpy(pData+4, &val, sizeof(val));
	conn->SendCmd((char*)&pData,8,0xA0);
	//AGC-B
	GetDlgItem(IDC_EDIT16)->GetWindowTextW(str);
	val=_ttoi(str);
	addr=27;
	memcpy(pData, &addr, sizeof(addr));
	memcpy(pData+4, &val, sizeof(val));
	conn->SendCmd((char*)&pData,8,0xA0);
	addr=30;
	memcpy(pData, &addr, sizeof(addr));
	memcpy(pData+4, &val, sizeof(val));
	conn->SendCmd((char*)&pData,8,0xA0);
	//AGC-C
	GetDlgItem(IDC_EDIT17)->GetWindowTextW(str);
	val=_ttoi(str);
	addr=28;
	memcpy(pData, &addr, sizeof(addr));
	memcpy(pData+4, &val, sizeof(val));
	conn->SendCmd((char*)&pData,8,0xA0);
	addr=31;
	memcpy(pData, &addr, sizeof(addr));
	memcpy(pData+4, &val, sizeof(val));
	conn->SendCmd((char*)&pData,8,0xA0);
	
}


void CManagerDlg::OnBnClickedButton27()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	unsigned int pos=0,tmp=0;
	pos=m_enable.GetPos();
	tmp |=pos<<7;
	pos=m_TargetGain.GetPos();
	tmp |=pos<<4;
	pos=m_AttactTime.GetPos();
	tmp |=pos<<2;
	pos=m_DecayTime.GetPos();
	tmp |=pos;
	str.Format(_T("%d"),tmp);
	GetDlgItem(IDC_EDIT15)->SetWindowText(str);

	tmp=0;
	pos=m_Allowed.GetPos();
	tmp |=pos<<1;
	str.Format(_T("%d"),tmp);
	GetDlgItem(IDC_EDIT16)->SetWindowText(str);

	tmp=0;
	pos=m_Hysteresis.GetPos();
	tmp |=pos<<6;
	pos=m_Threshold.GetPos();
	tmp |=pos<<1;
	pos=m_Stepping.GetPos();
	tmp |=pos;	
	str.Format(_T("%d"),tmp);
	GetDlgItem(IDC_EDIT17)->SetWindowText(str);	
	
}


void CManagerDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
	OnBnClickedButton27();
	//OnBnClickedButton26();
}
