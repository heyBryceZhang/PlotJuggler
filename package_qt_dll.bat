
set DIR=%~dp0


@REM 目标路径,及打包所产生得文件夹所存放得路径
set SOURCEDIR=%DIR%\install\bin

@REM 执行打包命令
echo Setting up environment for Qt usage...
set PATH=C:\Qt\5.15.2\msvc2019_64\bin
cd C:/Qt/5.15.2/msvc2019_64
windeployqt %SOURCEDIR%\plotjuggler.exe


pause