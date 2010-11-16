@ECHO  OFF
REM  Gera todos os scripts de make

cls

pushd  .


gmake  /b..\composicao  /cTesteLista
gmake  /b..\composicao  /cTestGraph
gmake  /b..\composicao  /cTestusr
gmake  /b..\composicao  /cTestcli
gmake  /b..\composicao  /crede_social

popd
