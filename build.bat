call clean.bat
REM xcopy /s C:\GB\ZGB\ZGB-template-master\res C:\GB\ZGB\ZGB-template-master\bkup_res /Y
cd src
SET ZGB_PATH=C:\GB\ZGBNEW\common
%ZGB_PATH%\..\env\make-3.81-bin\bin\make run
%ZGB_PATH%\..\tools\romusage-main\bin\romusage C:\GB\ZGB\ZGB-template-master\Release\ARROWS.map -g
cd ..
pause