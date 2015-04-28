#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include "MainDlg.h"
#include <stdio.h> 


BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Main_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Main_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Main_OnClose);
    }

    return FALSE;
}

VOID CALLBACK TimerProc (HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)   // 定时器响应函数
{
	SYSTEMTIME stLocal;
	GetLocalTime(&stLocal);  // 得到系统当前时间
	char strTime[256];
	sprintf(strTime,TEXT("%02d/%02d/%04d %02d:%02d:%02d"), stLocal.wMonth, stLocal.wDay, stLocal.wYear, stLocal.wHour, 
		  stLocal.wMinute, stLocal.wSecond);	
	SetDlgItemText(hwnd,IDC_TIME,strTime);
}

BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)  // 初始化对话框
{
	SendMessage(hwnd, WM_SETICON, (WPARAM)TRUE, (LPARAM)LoadIcon(GetModuleHandle(NULL), (LPCTSTR)1));  // 设置对话框左上角图标
	SetDlgItemText(hwnd,IDC_SHOW,TEXT("0"));    // 初始化屏幕显示为0
	SetTimer(hwnd, 0, 100, TimerProc);     // 设置定时器，100毫秒刷新一次
    
	SkinH_AttachEx("E:\\course & project\\C++\\Calculator2\\iTunes.she","1");
		
	TCHAR username[256]; 
    DWORD size = 256; 
    GetUserName (username, &size);    // 得到当前系统用户名
	SetDlgItemText(hwnd,IDC_USERNAME,username);

    return TRUE;
}

void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	KeyPress(hwnd, id);  
}

void Main_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}
