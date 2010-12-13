rem testa todos os scripts

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\testelista        /s..\scripts\testelista             /l..\produto\testelista              /a..\scripts\estatisticas

..\produto\testgraph        /s..\scripts\testgraph             /l..\produto\testgraph              /a..\scripts\estatisticas

..\produto\testgraphdbg        /s..\scripts\testgraph             /l..\produto\testgraphdbg              /a..\scripts\estatisticas

..\produto\testusr        /s..\scripts\testeusr             /l..\produto\testusr              /a..\scripts\estatisticas

..\produto\testcli        /s..\scripts\testecli             /l..\produto\testcli              /a..\scripts\estatisticas

..\produto\testnetmgr     /s..\scripts\testenetmgr             /l..\produto\testnetmgr              /a..\scripts\estatisticas

:sai

