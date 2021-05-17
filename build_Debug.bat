cd src
SET ZGB_PATH=C:\GB\ZGBNEW\common
%ZGB_PATH%\..\env\make-3.81-bin\bin\make run BUILD_TYPE=Debug
copy /Y C:\GB\ZGBNEW\ZGB-template-master\bin\FLYINGARROWS_Debug.gb C:\GB\ZGBNEW\ZGB-template-master\bin\FLYING_ARROWS_GAME\rom\rom.gb
cd ..
pause