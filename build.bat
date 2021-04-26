@echo off
cls
del /q .\output\*.d
del /q .\output\*.o
del /q .\output\*.map
del /q .\output\debug.hex
del /q .\output\debug.map
del /q .\output\release_440F256H.hex
del /q .\output\release_440F256H.map
del /q .\output\release_795F512H.hex
del /q .\output\release_795F512H.map
del /q .\output\release.hex
del /q .\output\release.map

.\make\make.exe -f Makefile_440F256H clean
.\make\make.exe -f Makefile_440F256H all -j8
copy .\output\release.hex .\output\release_440F256H.hex
copy .\output\release.map .\output\release_440F256H.map
.\make\make.exe -f Makefile_440F256H clean
del /q .\output\release.hex
del /q .\output\release.map
del /q .\output\*.d
del /q .\output\*.o
del /q .\output\*.elf

.\make\make.exe -f Makefile_795F512H clean
.\make\make.exe -f Makefile_795F512H all -j8
copy .\output\release.hex .\output\release_795F512H.hex
copy .\output\release.map .\output\release_795F512H.map
.\make\make.exe -f Makefile_795F512H clean
del /q .\output\release.hex
del /q .\output\release.map
del /q .\output\*.d
del /q .\output\*.o
del /q .\output\*.elf


rem pause