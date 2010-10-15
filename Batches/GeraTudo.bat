@ECHO  OFF
REM  Gera todos os scripts de make

cls

pushd  .


gmake  /b..\composicao  /cTesteLista
gmake  /b..\composicao  /cTestGraph

popd
