#pragma once

#ifdef FH_PLATFORM_WINDOWS
	#ifdef FH_BUILD_DLL
		#define FOUNTAINHEAD_API __declspec(dllexport)
	#else
		#define FOUNTAINHEAD_API __declspec(dllimport)
	#endif // 导入和导出DLL宏定义，在Fountainhead中只会调用导出，在Sandbox中只会调用导入，因为在解决方案属性的预处理器定义中进行了相关设置
#else 
	#error Fountainhead only supports Windows!
#endif // 如果当前平台为WINDOWS