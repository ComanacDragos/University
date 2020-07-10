#pragma once

// https://docs.microsoft.com/en-us/visualstudio/debugger/mfc-debugging-techniques?view=vs-2019
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

