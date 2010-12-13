@ECHO  OFF
REM  Gera todos os scripts de make

cls

pushd  .

mkdir ..\Produto
mkdir ..\Tabelas


gmake  /b..\composicao  /cTesteLista
gmake  /b..\composicao  /cTestGraph
gmake  /b..\composicao  /cTestGraphDbg
gmake  /b..\composicao  /cTestUsr
gmake  /b..\composicao  /cTestCli
gmake  /b..\composicao  /cTestNetMgr
gmake  /b..\composicao  /crede_social

popd
