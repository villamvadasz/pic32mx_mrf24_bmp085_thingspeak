@echo off
cls
call build.bat

cd .\bootloader_wifi_PIC 
call build.bat
cd ..

cd .\bootloader_updater_wifi_PIC 
call build.bat
cd ..

