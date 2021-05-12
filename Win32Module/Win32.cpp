#include "Win32.h"

BOOL InitListHeaders(HWND hList, const TCHAR** HeaderNames, DWORD Size)
{
	if (!HeaderNames || !Size)
	{
		return FALSE;
	}

	LV_COLUMN lv;
	//初始化
	memset(&lv, 0, sizeof(LV_COLUMN));
	//设置整行选中
	SendMessage(hList, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	//设置样式
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

	for (DWORD i = 0; i < Size; i++)
	{
		if (i == 2)
		{
			lv.cx = 362;
		}
		else if(i == 1)
		{
			lv.cx = 225;
		}
		else
		{
			lv.cx = 125;
		}
		lv.pszText = (LPSTR)HeaderNames[i];
		lv.iSubItem = i;
		SendMessage(hList, LVM_INSERTCOLUMN, i, (long long)&lv);
	}

	return TRUE;
}

VOID AddDataToList(HWND hList, DWORD Row, DWORD Line, TCHAR* szText)
{
	LV_ITEM vitem;				//List的数据项
	//初始化						
	memset(&vitem, 0, sizeof(LV_ITEM));
	//清空表中数据
	//SendMessageA(hList, LVM_DELETEALLITEMS, 0, 0);
	//设置样式
	vitem.mask = LVIF_TEXT;

	vitem.iItem = Row;
	vitem.iSubItem = Line;
	vitem.pszText = szText;
	if (Line == 0)
	{
		SendMessage(hList, LVM_INSERTITEM, 0, (long long)&vitem);
	}
	else
	{
		SendMessage(hList, LVM_SETITEM, 0, (long long)&vitem);
	}
}

VOID GetSelRowData(HWND hList, DWORD Line, TCHAR* szResult)
{
	//获取选中行数
	DWORD dwRowId = SendMessage(hList, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
	//获取该行数据
	LV_ITEM vitem;								//List的数据项
	memset(&vitem, 0, sizeof(LV_ITEM));
	vitem.iSubItem = Line;							//要提取的列
	vitem.pszText = szResult;					//指定存储查询结果的缓冲区
	vitem.cchTextMax = 0x80;					//要提取的尺寸
	SendMessage(hList, LVM_GETITEMTEXT, dwRowId, (long long)&vitem);
}

TCHAR* GetFileName(HWND hwndDlg)
{
	OPENFILENAME stOpenFile;
	//设置过滤器信息
	TCHAR szPeFileExt[30] = TEXT("*.exe;*.dll;*.sys");
	//保存文件名字缓冲区
	TCHAR* szFileName = (TCHAR*)malloc(sizeof(TCHAR) * 256);
	//初始化
	memset(szFileName, 0, 256);
	memset(&stOpenFile, 0, sizeof(OPENFILENAME));
	//设置参数
	stOpenFile.lStructSize = sizeof(OPENFILENAME);
	stOpenFile.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	stOpenFile.hwndOwner = hwndDlg;
	stOpenFile.lpstrFilter = (LPCSTR)szPeFileExt;
	stOpenFile.lpstrFile = szFileName;
	stOpenFile.nMaxFile = MAX_PATH;
	//获取文件完整路径
	GetOpenFileName(&stOpenFile);
	return szFileName;
}

LPVOID VirtualAllocate(HANDLE hProcess, DWORD size_t)
{
	PVOID pAddress = NULL;
	HMODULE hModuleKernel = LoadLibrary(TEXT("kernel32.dll"));
	if (!hModuleKernel)
	{
		MessageBox(NULL, TEXT("获取kernel失败！"), TEXT("[失败]"), MB_OK);
		TerminateProcess(hProcess, 1);
		return NULL;
	}
	typedef void* (__stdcall* pfVirtualAllocEx)(
		HANDLE hProcess,
		LPVOID lpAddress,
		DWORD dwSize,
		DWORD flAllocationType,
		DWORD flProtect);
	pfVirtualAllocEx VirtualAllocEx = NULL;
	VirtualAllocEx = (pfVirtualAllocEx)GetProcAddress((hModuleKernel), "VirtualAllocEx");

	pAddress = VirtualAllocEx(
		hProcess,
		NULL,
		size_t,
		MEM_RESERVE | MEM_COMMIT,
		PAGE_EXECUTE_READWRITE
	);

	FreeLibrary(hModuleKernel);
	return pAddress;
}