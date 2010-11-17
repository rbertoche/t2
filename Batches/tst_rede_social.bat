set SCRIPT=%1
set EXEC=..\Produto\rede_social
set INPUT=..\Scripts\%SCRIPT%.input
set OUTPUT=..\Scripts\%SCRIPT%.output
set EXPECTED=..\Scripts\%SCRIPT%.expected

%EXEC% -s <%INPUT% >%OUTPUT%
diff %EXPECTED% %OUTPUT%
