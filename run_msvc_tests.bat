if not exist ".\cmake-build-tests-windows-msvc" mkdir cmake-build-tests-windows-msvc
cd .\cmake-build-tests-windows-msvc

cmake -G "Visual Studio 17 2022" -A x64 -S .. -B .
@REM dir
@REM -verbosity:diag
msbuild tests.sln -t:rebuild -property:Configuration=Release -noWarn:C4514;C4710;C4711;D9025 -warnaserror
