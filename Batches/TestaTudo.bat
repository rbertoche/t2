rem testa todos os scripts

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\testelista        /s..\scripts\testelista             /l..\produto\testelista              /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\testgraph        /s..\scripts\testgraph             /l..\produto\testgraph              /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\testusr        /s..\scripts\testeusr             /l..\produto\testusr              /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\testcli        /s..\scripts\testecli             /l..\produto\testcli              /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\testnetmgr     /s..\scripts\testenetmgr             /l..\produto\testnetmgr              /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\..\ferramnt\exbestat /e..\scripts\estatisticas

:sai

