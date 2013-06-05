#pragma once
#include "define.h"
class Enconn
{
public:
	Enconn(void);
	~Enconn(void);
public:
	int Enctype;
	int Connflag;	
	CDC   *pDC;
	int Connect(int nType, const char *pAddr, int nPort, PCTSTR pPassword, int nChannel);
	int Disconnect(void);
	int Send(char* buf,size_t len);
	int Recv(char* buf,size_t len);
	int SendCmd(char* buf,size_t len,int key);
	void SetMessageHwnd(HWND hWnd);
	void Enconn::SetRichHandle(CRichEditCtrl* hWnd);
	CString filePath;
private:
	
	char m_pAddr[16];
	TCHAR m_pPassword[20];
	int m_hSocket;
	unsigned char* m_cVideoBuffer;
	HWND m_hMessageWnd;
	HANDLE m_hDataEvent;
	CRichEditCtrl* m_RichEdit;
	int Enconn::PackHeaderMSG(BYTE *data,BYTE type, WORD len);
	BOOL PostMessage(int nMsg,LPARAM lParam = NULL);
protected:
	static UINT ConnectThread(LPVOID pParam);
	static UINT MsgThread(LPVOID pParam);
	
public:
	// ÉÏ´«imgÍ¼Æ¬logo
	int UploadImg(CString filePath, LogoInfo position,int type);
	int SetImage(LogoInfo position);
	int Upload(CString filePath);

	CFile JpgFile;
	CFile AacFile;
	CFile H264File;
	int saveStream;
	HWND showwnd;
};

