cd src
SET ZGB_PATH=C:\GB\ZGBNEW\common
%ZGB_PATH%\..\env\make-3.81-bin\bin\make run BUILD_TYPE=Debug
%ZGB_PATH%\..\tools\romusage-main\bin\romusage C:\GB\ZGBNEW\ZGB-template-master\Debug\ARROWS_Debug.ihx -g

cd ..
pause