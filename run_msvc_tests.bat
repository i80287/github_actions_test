if not exist ".\cmake-build-tests-windows-msvc" mkdir cmake-build-tests-windows-msvc
cd .\cmake-build-tests-windows-msvc

cmake -G "Visual Studio 17 2022" -A x64 -S .. -B .
@REM dir
@REM -verbosity:diag
msbuild tests.sln -t:rebuild -property:Configuration=Release
