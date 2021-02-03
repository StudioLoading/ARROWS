call clean.bat
xcopy /s C:\GB\ZGB\ZGB-template-master\res C:\GB\ZGB\ZGB-template-master\bkup_res /Y
cd src
%ZGB_PATH%\..\env\make-3.81-bin\bin\make run
C:\GB\ZGB\tools\romusage-main\bin\romusage C:\GB\ZGB\ZGB-template-master\Release\ARROWS.map -g
cd ..
pause