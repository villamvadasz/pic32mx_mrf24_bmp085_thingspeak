@echo off
cd .\src\wifi\mpfs_gen
del /q ..\..\http_print.idx
java -jar mpfs2.jar /c /2 ..\..\..\html ..\..\ mpfs_img2.c
copy /Y ..\..\http_print.h ..\..\..\inc\http_print.h
del /q ..\..\http_print.h
del /q ..\..\http_print.idx
