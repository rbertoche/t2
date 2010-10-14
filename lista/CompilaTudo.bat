@ECHO  OFF
REM  Compila todos os exemplos simples 

pushd  .

del *.err
del TesteLista.exe

del *.obj
nmake /Ftestelista.make 

copy  *.err  tudo.err

notepad tudo.err

popd
