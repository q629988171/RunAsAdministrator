# 请求管理员身份运行

简单的 win32 应用程序，判断当前用户不是管理员组的成员，将请求管理员权限（UAC 提示）启动可执行文件。此应用程序**不会**绕过操作系统的保护措施。

# 示例

RunAsAdmin calc



# 原理

该应用程序使用带有*runas*关键字的*ShellExecute*调用。这会触发 UAC 提示，允许您的应用程序从 UAC 获得管理员权限，而无需使用可执行文件的特殊清单文件。
