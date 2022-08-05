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
 *  修改日期:22/08/05
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

// ReSharper disable CppClangTidyConcurrencyMtUnsafe
#include <iostream>
#include <Windows.h>
#include <ShlObj.h>


/**
 * \brief 请求管理员权限运行程序
 * \param filename 
 * \return 成功返回true, 失败返回false.
 */
bool open(LPCWSTR filename) {
    LPCWSTR lpOperation = nullptr;

    if (!IsUserAnAdmin()) {
        lpOperation = L"runas";
    }


    HINSTANCE h = ShellExecute(
            nullptr,
            lpOperation,
            filename,
            nullptr,
            nullptr,
            SW_SHOW
    );

    if (reinterpret_cast<int>(h) <= 32) {
        return FALSE;
    }

    return TRUE;
}


/**
 * \brief 显示使用说明
 */
void usage() {
    MessageBox(
            nullptr,
            L"Usage: RunAsAdmin.exe <filenames>",
            L"RunAsAdmin",
            MB_OK
    );
}


/**
 * \brief 显示错误消息
 * \param msg 
 */
void error(LPCWSTR msg) {
    LPVOID lpMsgBuf;
    TCHAR lpText[MAX_PATH + 256];

    FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<LPTSTR>(&lpMsgBuf),
            0,
            nullptr
    );

    swprintf_s(
            lpText,
            MAX_PATH + 256,
            L"%s\r\n\r\n%s",
            msg,
            static_cast<LPCWSTR>(lpMsgBuf)
    );

    MessageBox(
            nullptr,
            lpText,
            L"RunAsAdmin",
            MB_OK | MB_ICONSTOP
    );

    LocalFree(lpMsgBuf);
}

int wmain(int argc, wchar_t *argv[]) {
    WCHAR erring[MAX_PATH] = L"无法打开文件: ";

    if (argc == 1) {
        usage();
		return 1;
    }


    // ReSharper disable once CppLocalVariableMayBeConst
    bool rv = open(argv[1]);

    if (!rv) {
        wcscat_s(erring, argv[1]);
        error(erring);
        return 1;
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
