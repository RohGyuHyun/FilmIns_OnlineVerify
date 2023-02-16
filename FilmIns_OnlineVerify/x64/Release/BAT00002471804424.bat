@echo off
IF NOT EXIST D:\Source_Backup MD D:\Source_Backup
7z.exe a D:\Source_Backup\FilmIns_OnlineVerify.7z D:\Project\Source\FilmIns_OnlineVerify\
if errorlevel 1 goto VCReportError
goto VCEnd
:VCReportError
echo Project : error PRJ0019: 도구에서 오류 코드를 반환했습니다. 위치: "빌드 후 이벤트를 수행하고 있습니다..."
exit 1
:VCEnd