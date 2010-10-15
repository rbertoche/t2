ECHO compila todos os programas exemplo
REM Requer o ambiente (environment) inicializado para compilar com o VisualStudio Microsoft
cls

del ..\produto\*.err
del ..\objetos\*.obj

REM compila lista
pushd .
nmake /F..\composicao\testelista.make 
popd

REM compila graph
pushd .
nmake /F..\composicao\testgraph.make 
popd

copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err

