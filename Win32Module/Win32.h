#pragma once
#include <Windows.h>
#include <CommCtrl.h>
#include <stdio.h>
#pragma comment(lib,"comctl32.lib")

/*
* ��װ��һ��vc�⣬�������ÿؼ�����
*/

/*
* ListView�ؼ�
*	��ʼ��һ���б�ı�ͷ
*		�������б�������ͷ���飬��ͷ����
*/
BOOL InitListHeaders(HWND hList, const TCHAR** HeaderNames, DWORD Size);

/*
* ListView�ؼ�
*	�������
*		�������б�����Ҫ��ӵ��У�Ҫ��ӵ��У�Ҫ��ӵ�ֵ
*/
VOID AddDataToList(HWND hList, DWORD Row, DWORD Line, TCHAR* szText);

/*
* ListView�ؼ�
*	��ȡѡ������ĳһ�е�����
*/
VOID GetSelRowData(HWND hList, DWORD Line, TCHAR* szResult);

/*
* ���ļ��������ѡ���ļ����������ù�����
*/
TCHAR* GetFileName(HWND hwndDlg);

/*
* ָ�������з����ڴ�
*/
LPVOID VirtualAllocate(HANDLE hProcess, DWORD size_t);