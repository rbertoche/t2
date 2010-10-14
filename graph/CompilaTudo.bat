@ECHO  OFF
REM  Compila todos os exemplos simples 

pushd  .

del *.err
del TestGraph.exe

del *.obj
nmake /Ftestgraph.make 

copy  *.err  tudo.err

notepad tudo.err

popd
