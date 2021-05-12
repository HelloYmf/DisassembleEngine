#pragma once
#include <Windows.h>
#include <CommCtrl.h>
#include <stdio.h>
#pragma comment(lib,"comctl32.lib")

/*
* 封装的一套vc库，包括常用控件函数
*/

/*
* ListView控件
*	初始化一个列表的表头
*		参数：列表句柄，表头数组，表头个数
*/
BOOL InitListHeaders(HWND hList, const TCHAR** HeaderNames, DWORD Size);

/*
* ListView控件
*	添加数据
*		参数：列表句柄，要添加的行，要添加的列，要添加的值
*/
VOID AddDataToList(HWND hList, DWORD Row, DWORD Line, TCHAR* szText);

/*
* ListView控件
*	获取选中行中某一列的数据
*/
VOID GetSelRowData(HWND hList, DWORD Line, TCHAR* szResult);

/*
* 打开文件浏览器，选择文件，可以设置过滤器
*/
TCHAR* GetFileName(HWND hwndDlg);

/*
* 指定进程中分配内存
*/
LPVOID VirtualAllocate(HANDLE hProcess, DWORD size_t);