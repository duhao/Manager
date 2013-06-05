
// ManagerDlg.h : ͷ�ļ�
//
#pragma once

#include "Enconn.h"

// CManagerDlg �Ի���
class CManagerDlg : public CDialogEx
{
// ����
public:
	CManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	Enconn *conn;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_Cpro;
	CRichEditCtrl m_RichEdit;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	CProgressCtrl m_Progress;
	afx_msg void OnBnClickedButton24();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton25();
	afx_msg void OnBnClickedButton26();
	CSliderCtrl m_enable;
	CSliderCtrl m_TargetGain;
	CSliderCtrl m_AttactTime;
	CSliderCtrl m_DecayTime;
	CSliderCtrl m_Allowed;
	CSliderCtrl m_Hysteresis;
	CSliderCtrl m_Threshold;
	CSliderCtrl m_Stepping;
	afx_msg void OnBnClickedButton27();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
