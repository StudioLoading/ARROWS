REM call clean.bat
REM xcopy /s C:\GB\ZGB\ZGB-template-master\res C:\GB\ZGB\ZGB-template-master\bkup_res /Y
cd src
%ZGB_PATH%\..\env\make-3.81-bin\bin\make run
cd ..
pause