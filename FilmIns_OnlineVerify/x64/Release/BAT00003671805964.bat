@echo off
IF NOT EXIST D:\Source_Backup MD D:\Source_Backup
7z.exe a D:\Source_Backup\FilmIns_OnlineVerify.7z D:\Project\Source\FilmIns_OnlineVerify\
if errorlevel 1 goto VCReportError
goto VCEnd
:VCReportError
echo Project : error PRJ0019: �������� ���� �ڵ带 ��ȯ�߽��ϴ�. ��ġ: "���� �� �̺�Ʈ�� �����ϰ� �ֽ��ϴ�..."
exit 1
:VCEnd