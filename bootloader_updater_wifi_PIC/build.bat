@echo off
cls
del /q .\output\*.d
del /q .\output\*.o
del /q .\output\*.map
del /q .\output\*.hex
del /q .\output\*.elf

.\make\make.exe -f Makefile_440F256H clean
.\make\make.exe -f Makefile_440F256H all -j8
copy .\output\WiFiBootloader_MRF24WB.hex .\output\WiFiBootloader_MRF24WB_440F256H.hex
copy .\output\WiFiBootloader_MRF24WB.map .\output\WiFiBootloader_MRF24WB_440F256H.map
.\make\make.exe -f Makefile_440F256H clean

del /q .\output\WiFiBootloader_MRF24WB.map
del /q .\output\*.d
