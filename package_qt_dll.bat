
set DIR=%~dp0


@REM Ŀ��·��,��������������ļ�������ŵ�·��
set SOURCEDIR=%DIR%\install\bin

@REM ִ�д������
echo Setting up environment for Qt usage...
set PATH=C:\Qt\5.15.2\msvc2019_64\bin
cd C:/Qt/5.15.2/msvc2019_64
windeployqt %SOURCEDIR%\plotjuggler.exe


pause