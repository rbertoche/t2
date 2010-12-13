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

REM compila graphdbg
pushd .
nmake /F..\composicao\testgraphdbg.make
popd

REM compila usr
pushd .
nmake /F..\composicao\testusr.make
popd

REM compila cli
pushd .
nmake /F..\composicao\testcli.make
popd

REM compila netmgr
pushd .
nmake /F..\composicao\testnetmgr.make
popd

REM compila rede_social
pushd .
nmake /F..\composicao\rede_social.make
popd

copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err

