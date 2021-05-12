#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "../View Module/resource.h"
#include "../Win32 Module/Win32.h"
#include "../Fun Module/Fun.h"

TCHAR* g_szFileBuffer = NULL;
DWORD CodeSize = 0;

BOOL CALLBACK DialogProc(
	HWND hwndDlg,			
	UINT uMsg,	
	WPARAM wParam,			
	LPARAM lParam		
)
{
	switch (uMsg)
	{
		case  WM_INITDIALOG:
		{
			HWND hList = GetDlgItem(hwndDlg, IDC_LIST_MAIN);
			const TCHAR* HeaderNames[3] =
			{
				TEXT("地址"),
				TEXT("硬编码"),
				TEXT("反汇编")
			};
			InitListHeaders(hList, HeaderNames, 3);

			return TRUE;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDC_BUTTON_CHOOSEFILE:
				{
					TCHAR* szFilePath = GetFileName(hwndDlg);
					SendDlgItemMessage(hwndDlg, IDC_EDIT1, WM_SETTEXT, 0, (LPARAM)szFilePath);
					HANDLE hfile = CreateFile(szFilePath, GENERIC_READ, FILE_SHARE_READ, NULL,
						OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					DWORD FileSize = 0;
					FileSize = GetFileSize(hfile, NULL);
					CodeSize = FileSize;
					g_szFileBuffer = (PTCHAR)malloc(sizeof(BYTE) * FileSize);
					ReadFile(hfile, g_szFileBuffer, FileSize, NULL, NULL);
					
					return TRUE;
				}
				case IDC_BUTTON_DASM:
				{
					DWORD BaseAddress;										//指令起始地址
					PBYTE currentInstruction, lastInstruction;				//双指针，一前一后
					INSTRUCTION Instruction;								//指令结构，不断更新
					TCHAR InstructionStr[MAX_INSTRUCTION_LEN];				//反汇编内容

					//初始化
					BaseAddress = 0x401000;
					currentInstruction = lastInstruction = (PBYTE)g_szFileBuffer;
					HWND hList = GetDlgItem(hwndDlg, IDC_LIST_MAIN);
					int i = 0;

					while (lastInstruction - (PBYTE)g_szFileBuffer < CodeSize)
					{
						DWORD s1 = lastInstruction - (PBYTE)g_szFileBuffer;
						DWORD s2 = sizeof(g_szFileBuffer);

						TCHAR szTemp[256] = { 0 };
						Instruction.LinearAddress = BaseAddress + lastInstruction - (PBYTE)g_szFileBuffer;		//更新指令首地址
						sprintf(szTemp, "%x", Instruction.LinearAddress);
						AddDataToList(hList, i, 0, szTemp);
						/*
						* 从lastInstruction位置开始解析,最终会把解析出来的指令长度加在currentInstruction上返回
						*	同时更新Instruction结构的内容
						*		最终翻译结果会存放到InstructiuonStr中
						*/
						currentInstruction = Disassemble(lastInstruction, &Instruction, InstructionStr);		
						//循环输出硬编码
						memset(szTemp, 0, sizeof(szTemp));
						for (; lastInstruction < currentInstruction; lastInstruction++)
						{
							TCHAR szTemp1[20] = { 0 };
							TCHAR szTemp2[20] = { 0 };
							sprintf(szTemp1, "%X", (*lastInstruction >> 4) & 0xF);
							strcat(szTemp, szTemp1);
							sprintf(szTemp2, "%X", (*lastInstruction) & 0xF);
							strcat(szTemp, szTemp2);
							strcat(szTemp, "  ");
						}
						AddDataToList(hList, i, 1, szTemp);
						//输出翻译结果
						AddDataToList(hList, i, 2, InstructionStr);
						i++;
					}
					return TRUE;
				}
			}
			return FALSE;
		}
		case WM_CLOSE:
		{
			EndDialog(hwndDlg, 0);
			return TRUE;
		}
	}
	return FALSE;
}

int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,	
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow
)
{
	DialogBox(hInstance, (LPCSTR)IDD_DIALOG_MAIN, NULL, DialogProc);

	return 0;
}