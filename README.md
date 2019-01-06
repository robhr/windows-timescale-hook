# windows-timescale-hook
After being injected into a target process, `windows-timescale-hook.dll` hooks various functions existing in `kernel32.dll` and `winmm.dll` that measure absolute and relative time intervals. It can be used to modify the timescale of any process that directly or indirectly invokes any of the functions noted below.
___
##  Hooks
* [`DWORD timeGetTime(VOID);`](https://docs.microsoft.com/en-us/windows/desktop/api/timeapi/nf-timeapi-timegettime)
* [`DWORD SleepEx(DWORD dwMilliseconds, BOOL bAlertable);`](https://docs.microsoft.com/en-us/windows/desktop/api/synchapi/nf-synchapi-sleepex)
* [`DWORD GetTickCount(VOID);`](https://docs.microsoft.com/en-us/windows/desktop/api/sysinfoapi/nf-sysinfoapi-gettickcount)
* [`ULONGLONG GetTickCount64(VOID);`](https://docs.microsoft.com/en-us/windows/desktop/api/sysinfoapi/nf-sysinfoapi-gettickcount64)
* [`BOOL QueryPerformanceCounter(PLARGE_INTEGER lpPerformanceCount);`](https://msdn.microsoft.com/en-us/library/windows/desktop/ms644904(v=vs.85).aspx)
___
## Usage
1. Clone this repository and its [submodules](https://github.com/Microsoft/Detours).
2. Use [premake](https://github.com/premake/premake-core) to generate the project files.
3. Compile the submodules within the `/dependencies` folder.
4. Move `Detours.lib` into the project's root directory.
5. Optionally modify the `fRateModifier` float value then compile the project.
6. Inject the compiled DLL into the target process of your choice 💸