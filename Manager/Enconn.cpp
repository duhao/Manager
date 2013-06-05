#include "StdAfx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Enconn.h"
#include "Define.h"

Enconn::Enconn(void)
{
	Connflag=0;	
	m_hMessageWnd = NULL;
	Enctype=0;
	m_hSocket=0;
	m_cVideoBuffer = new unsigned char[1920*1080*2];
	m_hDataEvent = CreateEvent(NULL,TRUE,TRUE,NULL);
	filePath = _T("");
	saveStream = 0;
}


Enconn::~Enconn(void)
{
}
BOOL Enconn::PostMessage(int nMsg,LPARAM lParam)
{
	if (m_hMessageWnd == NULL)
		return FALSE;
	if (!IsWindow(m_hMessageWnd))
		return FALSE;

	return ::PostMessage(m_hMessageWnd,nMsg,0,lParam);
}
void Enconn::SetMessageHwnd(HWND hWnd)
{
	m_hMessageWnd = hWnd;
}
void Enconn::SetRichHandle(CRichEditCtrl* hWnd)
{
	m_RichEdit = hWnd;
}
int Enconn::Connect(int nType, const char *pAddr, int nPort, PCTSTR pPassword, int nChannel)
{
	
	
	strcpy_s(m_pAddr,16,pAddr);
	_tcscpy_s(m_pPassword,20,pPassword);		
	Connflag = 1;		

	DWORD dwID;
	HANDLE handle = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ConnectThread,(LPVOID)this,0,&dwID);
	if(handle)
		{
			CloseHandle(handle);return false;
		}
	else
	{
		return true;
	}
}
int Enconn::Disconnect(void)
{
	closesocket(m_hSocket);
	m_hSocket=0;
	return 0;	
}
int Enconn::Send(char* buf,size_t len)
{
	int sendsize=0;
	size_t relsendsize=0;
	if(m_hSocket<1)return -1;
	while(relsendsize<len)
	{
		sendsize=send(m_hSocket,buf+relsendsize,len-relsendsize,0);
		if(sendsize==SOCKET_ERROR)
		{
			closesocket(m_hSocket);
			m_hSocket=0;
			return -1;	
		}
		relsendsize+=sendsize;

    }	
	return 0;	
}
int Enconn::Recv(char* buf,size_t len)
{
	int recvsize=0;
	size_t relrecvsize=0;
	if(m_hSocket<1)return -1;
	while(relrecvsize<len)
	{
		recvsize=recv(m_hSocket,buf+relrecvsize,len-relrecvsize,0);
		if(recvsize ==WSAETIMEDOUT)
		{
			continue;
		}
		if(recvsize<1)
		{
			
			closesocket(m_hSocket);
			m_hSocket=0;
			return -1;	
		}
		relrecvsize+=recvsize;

    }	
	return 0;	
}
int Enconn::SendCmd(char* buf,size_t len,int key)
{
	int rcvLen = 0;
	char pData[512] = {0};
	if((HEAD_LEN+len)>512)return -1;
	if(Enctype==1)//ENC1200
	{
		PackHeaderMSG((BYTE *)pData, key, (HEAD_LEN+len));
		memcpy(pData+HEAD_LEN,buf,len);
		rcvLen=Send((char*)pData,HEAD_LEN+len);//发送消息
	}
	else//ENC110
	{
		*(short*)(&pData)=htons(3+len);
		pData[2]=key;
		memcpy(pData+3,buf,len);
		rcvLen=Send((char*)pData,3+len);//发送消息
	}	
	return rcvLen;
}

/*消息头打包*/
int Enconn::PackHeaderMSG(BYTE *data,
                   BYTE type, WORD len)
{
	MSGHEAD  *p;
	p = (MSGHEAD *)data;
	memset(p, 0, HEAD_LEN);
	p->nLen = htons(len);
	p->nMsg = type;
	return 1;
}

UINT Enconn::ConnectThread(LPVOID pParam)//接收线程
{		
	int rcvLen = 0;
	int nDataLen = 0;
	int recvedlen =0;
	char pData[256] = {0};	 
	unsigned char msgcmd=0;
		IPicture   *pPic;     
	IStream   *pStm;
				
	HGLOBAL hMem;
	LPVOID lpBuf;
	HDC			hdc;
	HWND		hwnd;
	MSGHEAD head;

	CString finename;
	int pptindex=0;
	Enconn* pEnconn = (Enconn*) pParam;


	pEnconn->m_hSocket = socket(AF_INET,SOCK_STREAM,0);	
	struct sockaddr_in        client_addr;
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr(pEnconn->m_pAddr);
	client_addr.sin_port = htons(PORT);
	int nSize = 4000;
	pEnconn->PostMessage(RM_ST_CONNING,0);//给窗体发送消息
	setsockopt(pEnconn->m_hSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&nSize ,sizeof(nSize));	//设置socket接收超时,4秒钟
	if(connect(pEnconn->m_hSocket, (LPSOCKADDR)&client_addr, sizeof(client_addr)) != 0)
	{	
		pEnconn->PostMessage(RM_ST_FAIL,NULL);	
		closesocket(pEnconn->m_hSocket);
		pEnconn->m_hSocket=0;		
		return 0;
	}
	pEnconn->Connflag=1;
	pEnconn->PostMessage(RM_ST_SUCCESS,0);
	if(pEnconn->Enctype==1)//ENC1200
	{
		pEnconn->PackHeaderMSG((BYTE *)pData, MSG_PASSWORD, (HEAD_LEN+1+_tcslen(pEnconn->m_pPassword)));
		pData[HEAD_LEN]='A';//表示管理员	
		WideCharToMultiByte(CP_ACP,NULL,pEnconn->m_pPassword,_tcslen(pEnconn->m_pPassword),&pData[HEAD_LEN+1],8,NULL,FALSE);
		rcvLen=pEnconn->Send((char*)pData,HEAD_LEN+1+_tcslen(pEnconn->m_pPassword));//发送密码
	}
	else//ENC110
	{
		*(short*)(&pData)=htons(4+_tcslen(pEnconn->m_pPassword));
		pData[2]=MSG_PASSWORD;
		pData[3]='A';//表示管理员	
		WideCharToMultiByte(CP_ACP,NULL,pEnconn->m_pPassword,_tcslen(pEnconn->m_pPassword),&pData[4],8,NULL,FALSE);
		rcvLen=pEnconn->Send((char*)pData,4+_tcslen(pEnconn->m_pPassword));//发送密码
	}
	if(rcvLen==-1)goto Exit;
	while(pEnconn->m_hSocket>0)
	{
		int nn = GetTickCount();
		if(pEnconn->Enctype==1)//ENC1200
		{
			rcvLen=pEnconn->Recv((char*)pEnconn->m_cVideoBuffer, HEAD_LEN);//接收编码器的数据
		}
		else//ENC110
		{
			rcvLen=pEnconn->Recv((char*)pEnconn->m_cVideoBuffer, 2);//接收编码器的数据
		}
		
		if(rcvLen == -1)
		{
			goto Exit;
		}		
		if(pEnconn->Enctype==1)//ENC1200
		{
			memcpy(&head,(pEnconn->m_cVideoBuffer),HEAD_LEN);	
			nDataLen=ntohs(head.nLen)-HEAD_LEN;
			if(nDataLen < 0)goto Exit;
			rcvLen=pEnconn->Recv((char*)pEnconn->m_cVideoBuffer, nDataLen);		
			msgcmd=head.nMsg;

		}
		else//ENC110
		{
			nDataLen=htons(*((unsigned short*)(pEnconn->m_cVideoBuffer)))-2;	
			if(nDataLen < 1)goto Exit;
			rcvLen=pEnconn->Recv((char*)pEnconn->m_cVideoBuffer, nDataLen);		
			msgcmd=pEnconn->m_cVideoBuffer[0];

		}
			
		if(rcvLen == -1)
		{
			goto Exit;
		}			
		switch(msgcmd) 
		{
		case MSG_CONNECTSUCC:				
			(pEnconn->m_RichEdit)->SetWindowTextW(_T("链接成功"));
			break;
		case MSG_PASSWORD_ERR:	
			pEnconn->PostMessage(RM_PASSWD_ERR,NULL);	
			(pEnconn->m_RichEdit)->SetWindowTextW(_T("密码错误"));
			break;
		case MSG_MAXCLIENT_ERR:				
			(pEnconn->m_RichEdit)->SetSel(-1,-1);
			(pEnconn->m_RichEdit)->ReplaceSel(_T("最大客户数\n"),0);
			break;
		case MSG_SCREENDATA:	
			//(pEnconn->m_RichEdit)->SetSel(-1,-1);
			//(pEnconn->m_RichEdit)->ReplaceSel(_T("h264 Data\n"),0);		
			//(pEnconn->m_RichEdit)->SetWindowTextW(_T("h264"));
			//printf("Recv h264 Data\n");
			
			if(pEnconn->saveStream==1)
			{
				if(pEnconn->Enctype==1)//ENC1200
					pEnconn->H264File.Write((char*)pEnconn->m_cVideoBuffer+sizeof(FRAMEHEAD),nDataLen-sizeof(FRAMEHEAD));
				else
					pEnconn->H264File.Write((char*)pEnconn->m_cVideoBuffer+1+sizeof(DataHeader),nDataLen-1-sizeof(DataHeader));
					
			}
			break;
		case MSG_AUDIODATA:							
			//(pEnconn->m_RichEdit)->SetSel(-1,-1);
			//(pEnconn->m_RichEdit)->ReplaceSel(_T("AAC Data\n"),0);
			//printf("Recv AAC Data\n");
			if(pEnconn->saveStream==1)
			{
				if(pEnconn->Enctype==1)//ENC1200
				pEnconn->AacFile.Write((char*)pEnconn->m_cVideoBuffer+sizeof(FRAMEHEAD),nDataLen-sizeof(FRAMEHEAD));
				else
				pEnconn->AacFile.Write((char*)pEnconn->m_cVideoBuffer+1+sizeof(DataHeader),nDataLen-1-sizeof(DataHeader));
			}
			break;
		case MSG_SYSPARAMS:
			
			printf("Recv MSG_SYSPARAMS \n");
			break;
		case MSG_TRACKAUTO:
			
			printf("Recv MSG_TRACKAUTO \n");
			break;
		case MSG_DATAINFO:
			
			printf("Recv MSG_DATAINFO \n");
			break;	
		case MSG_LOW_BITRATE:
			
			printf("Recv LowStream ok \n");
			break;
		case  MSG_LOW_SCREENDATA:			
			printf("Recv LowStream Data\n");
			break;
		case MSG_PIC_DATA:					
			//memcpy(&nDataLen, &pEnconn->m_cVideoBuffer[1],sizeof(nDataLen));
			memcpy(&nDataLen, (char*)pEnconn->m_cVideoBuffer+1,sizeof(nDataLen));
			printf("PPT索引图片=%d 字节\n", nDataLen);
			//hMem = ::GlobalAlloc(GMEM_MOVEABLE,nDataLen);
			//lpBuf = ::GlobalLock(hMem);
			rcvLen = pEnconn->Recv((char*)pEnconn->m_cVideoBuffer+4, nDataLen);
			finename.Format(_T("%d.jpg"),pptindex);
			if (!(pEnconn->JpgFile.Open(finename,CFile::modeCreate | CFile::modeWrite)))
			{
				printf("open jpegFile fail! \n");
				pptindex++;
				break;
			}
			pEnconn->JpgFile.Write((char*)pEnconn->m_cVideoBuffer+4,nDataLen);
			pEnconn->JpgFile.Close();
			pptindex++;
			hMem = ::GlobalAlloc(GMEM_MOVEABLE,nDataLen);
			lpBuf = ::GlobalLock(hMem);
			memcpy(lpBuf,(char*)pEnconn->m_cVideoBuffer+4,nDataLen);
			::GlobalUnlock(hMem);
			::CreateStreamOnHGlobal(hMem, TRUE, &pStm); //装入图形文件	
			if(SUCCEEDED(OleLoadPicture(pStm,nDataLen,TRUE,IID_IPicture,(LPVOID*)&pPic)))
			{
					
				OLE_XSIZE_HIMETRIC hmWidth;
				OLE_YSIZE_HIMETRIC hmHeight;
				pPic->get_Width(&hmWidth); //用接口方法获得图片的宽和高
				pPic->get_Height(&hmHeight);				
				printf("PPTJPEG=%d=%d\n",hmWidth,hmHeight);
				//获取桌面窗口句柄
				hwnd = ::GetDesktopWindow();
				//获取桌面窗口DC
				hdc = ::GetWindowDC(hwnd);				
				CRect rect;
				CDC *pDC=CDC::FromHandle(hdc);
				//////显示原图大小/////////////////////////////////////////////////////////////
				CSize sz(hmWidth,hmHeight);
				pDC->HIMETRICtoDP(&sz); //转换MM_HIMETRIC模式单位为MM_TEXT像素单位			
				pPic->Render(hdc,80,80,sz.cx,sz.cy,0,hmHeight,hmWidth,-hmHeight,NULL);
				//按窗口尺寸显示///////////////////						  
				GetClientRect(hwnd,&rect);
				if(pPic) pPic->Release();					
				::ReleaseDC(hwnd, hdc);
				
			}				
			pStm->Release();  

			printf("Recv PPT Data\n");
			break;
		case MSG_GET_LOGOINFO:	
			printf("Recv MSG_GET_LOGOINFO \n");
			break;
		case MSG_PIC_DATAEX:	
			printf("Recv MSG_PIC_DATAEX \n");
			recvedlen=0;			
			break;
		default:
	
			break;
		}
		
	}

Exit:	
	pEnconn->Connflag=0;
	pEnconn->PostMessage(RM_DISCONN,NULL);
	return 1;

}
UINT Enconn::MsgThread(LPVOID pParam)
{
	int length=0;
	int sendlen=0;
	int filesize=0;
	int progress=0;
	CFile file;
	char pData[8*1024] = {0};
	Enconn* pEnconn = (Enconn*) pParam;
	if(file.Open(pEnconn->filePath,CFile::typeBinary|CFile::modeRead)==FALSE)
	{
		::AfxMessageBox(_T("打开文件失败"));
		return -1;
	}
	filesize=file.GetLength();
	printf("bin file length=%d\n",length);
	filesize-=8;
	if(filesize<1)return -1;	
	if(pEnconn->Enctype==1)//ENC1200
	{	
		pEnconn->PackHeaderMSG((BYTE *)pData, MSG_UpdataFile, (HEAD_LEN+sizeof(int)));				
		memcpy(pData+HEAD_LEN,&filesize,4);
		pEnconn->Send(pData,HEAD_LEN+4);
	}
	else
	{	
		*(short*)(&pData)=htons(7);	
		pData[2]=MSG_UpdataFile;
		memcpy(pData+3,&filesize,4);		
		pEnconn->Send(pData,7);
	}
	length=file.Read(pData,8);
	while(length)
	{		
		length=file.Read(pData,8*1024);
		pEnconn->Send(pData,length);
		sendlen+=length;
		progress=(sendlen*100)/filesize;
		printf("%d\%\n",progress);
		pEnconn->PostMessage(RM_UPDATE_STATUS,progress);
	}
	return 0;
	return 1;
}

// 上传img图片logo
int Enconn::UploadImg(CString filePath, LogoInfo position,int type)
{
	int length;
	CFile file;
	char pData[1024] = {0};
	if(file.Open(filePath,CFile::typeBinary|CFile::modeRead)==FALSE)
	{
		::AfxMessageBox(_T("打开文件失败"));
		return -1;
	}
	length=file.GetLength();
	printf("img file length=%d\n",length);
	if(length<1)return -1;	
	if(Enctype==1)//ENC1200
	{	
		PackHeaderMSG((BYTE *)pData, MSG_SET_LOGOINFO, (HEAD_LEN+1+sizeof(LogoInfo)));
		pData[HEAD_LEN]=type;
		memcpy(pData+HEAD_LEN+1,&position,sizeof(LogoInfo));
		*(int*)((pData+HEAD_LEN+1+sizeof(LogoInfo)))=(length);
		Send(pData,HEAD_LEN+1+sizeof(LogoInfo)+4);
	}
	else
	{	
		*(short*)(&pData)=htons(4+sizeof(LogoInfo));	
		pData[2]=MSG_SET_LOGOINFO;
		pData[3]=type;
		memcpy(pData+4,&position,sizeof(LogoInfo));
		*(int*)((pData+4+sizeof(LogoInfo)))=(length);	
		Send(pData,8+sizeof(LogoInfo));
	}
	while(length)
	{		
		length=file.Read(pData,512);
		Send(pData,length);
	}
	

	return 0;
}


int Enconn::SetImage(LogoInfo position)
{
		char pData[1024] = {0};
	if(Enctype==1)//ENC1200
	{	
		PackHeaderMSG((BYTE *)pData, MSG_SET_LOGOINFO, (HEAD_LEN+1+sizeof(LogoInfo)));
		pData[HEAD_LEN]=0;
		memcpy(pData+HEAD_LEN+1,&position,sizeof(LogoInfo));
	
		Send(pData,HEAD_LEN+1+sizeof(LogoInfo));
	}
	else
	{	
		*(short*)(&pData)=htons(4+sizeof(LogoInfo));	
		pData[2]=MSG_SET_LOGOINFO;
		pData[3]=0;
		memcpy(pData+4,&position,sizeof(LogoInfo));
		
		Send(pData,4+sizeof(LogoInfo));
	}
	return 0;
}


int Enconn::Upload(CString filePath)
{
	DWORD dwID;
	
	CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)MsgThread,(LPVOID)this,0,&dwID);
	return 0;
}
