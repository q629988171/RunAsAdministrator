/*******************************************************************
 *  Copyright(c) 2021-2021 Allen
 *  All rights reserved.
 *
 *  文件名称:RunAsAdmin
 *  简要描述:指定程序请求管理员权限运行
 *
 *  创建日期:2021/11/21
 *  作者:Allen
 *  说明:指定程序请求管理员权限运行
 *
 *  修改日期:2021/11/22
 *  作者:Allen
 *  说明:判断当前用户是管理员组的成员
 *	
 *  参考:
 *  https://github.com/yoggy/open-command-for-Windows
 *  https://github.com/statiolake/open-windows
 *  https://luethje.eu/prog/runas_en.htm
 ******************************************************************/

// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include <Shlobj.h>

/**
 *  功能描述:请求管理员权限运行程序
 *  @param 要打开的文件名称
 *  @return 成功返回true, 失败返回false.
 */
bool open(LPCWSTR filename)
{
	HINSTANCE h;
	LPCWSTR lpOperation = NULL;

	if (!IsUserAnAdmin()) lpOperation = L"runas";

	h = ShellExecute(
		NULL, 
		lpOperation,
		filename, 
		NULL, 
		NULL, 
		SW_SHOW);
	if ((int)h <= 32) {
		return false;
	}
	return true;
}

/**
 *  功能描述:显示使用说明
 *  @param 无
 *  @return 无
 */
void usage()
{
	MessageBox(
		NULL, 
		L"Usage: RunAsAdmin.exe <filenames>", 
		L"RunAsAdmin", 
		MB_OK);
	exit(1);
}

/**
 *  功能描述:显示错误信息
 *  @param 传递文件名称
 *  @return 无
 */
void error(LPCWSTR filename)
{
	LPVOID lpMsgBuf;
	TCHAR msg[MAX_PATH + 256];
	
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL);

	swprintf_s(
		msg, 
		MAX_PATH + 256, 
		L"无法打开文件 %s\r\n%s", 
		filename, 
		(LPCWSTR)lpMsgBuf);

	MessageBox(
		NULL, 
		msg,
		L"Error", 
		MB_OK | MB_ICONSTOP);
	LocalFree(lpMsgBuf);
	exit(1);
}

int wmain(int argc, wchar_t *argv[])
{
	bool rv;

	if (argc == 1) usage();


	rv = open(argv[1]);
	if (!rv)
	{
		error(argv[1]);
		exit(1);
	}
	return 0;
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
