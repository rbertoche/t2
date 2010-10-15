#if ! defined( GENERICO_ )
#define GENERICO_
/***************************************************************************
*
*  $MCD Módulo de definição: TSTG Controlador de teste genérico
*
*  Arquivo gerado:              GENERICO.H
*  Letras identificadoras:      TST
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: C:\AUTOTEST\PROJETOS\INSTRUM.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*     O módulo de teste genérico contém um conjunto de funções de
*     coordenação, apoio e controle da execução de testes de módulos
*     quaisquer.
*
*     Embora na prática a função de teste específica seja uma extensão da
*     função de teste genérica, a função de teste específica encontra-se em
*     outro módulo. Desta forma as alterações necessárias para cada
*     módulo a testar concentram-se exclusivamente naquele módulo.
*
*  $EIU Interface com o usuário pessoa
*     Os seguintes comandos genéricos estão definidos:
*
*     linha em branco - faz nada
*
*     //      - comentário, é impresso no LOG
*
*     ==      - título de caso de teste, o título é impresso no LOG
*
*     =recuperar
*             - Caso o comando imediatamente anterior ao comando
*               =recuperar retorne TST_CondRetOK, obviemanete o comando
*               executou corretamente, portanto o comando =recuperar
*               reportará uma falha no script de teste, uma vez que não
*               foi encontrada a falha esperada ao executar o comando.
*             - Caso o comando antecessor retorne TST_CondRetErro,
*               ou TST_CondRetParm (erro de parâmetros do comando)
*               a falha reportada será desconsiderada, uma vez que
*               era esperada. O comando =recuperar destina-se a
*               apoiar o teste da corretude dos validadores de
*               parâmetros dos comandos e das funções por eles
*               ativadas.
*             - caso o comando antecessor retorne outras condições, o
*               comando =recuperar será tratado como falha.
*
*     =bkpt   - permite interagir com o depurador utilizado para
*               desenvolver os módulos sob teste. O comando =bkpt
*               executa um código "dummy" no qual pode ser inserido
*               um "breakpoint" do depurador. Desta forma o teste pode
*               prosseguir sem interrupção até o comando =bkpt.
*               Para isto
*               - apague ou desative todos os breakpoints do depurador
*               - insira o comando =bkpt no script pouco antes do ponto
*                 de interrupção desejado
*               - usando o depurador, estabeleça um breakpoint na linha de
*                 código: "Dummy = 0 ;" contida no módulo de teste
*                 genérico. Esta linha pode ser encontrada
*                 procurando por "BKPT_CMD"
*               - dê partida no programa e espere até chegar ao breakpoint
*                 associado ao comando "dummy". Agora reative ou instale
*                 os breakpoints requeridos pela a sessão de depuração.
*                 e continue depurando
*
*     =cancelar
*             - termina a interpretação dos comandos de teste.
*               Sempre sinaliza falha.
*
*     =AceitaFalhasAcumuladas  numFalhas
*             - caso o contador de falhas registre numFalhas, ele será
*               tornado zero. Este comando é similar a =recuperar.
*               Difere deste por ser executado desde que o comando
*               anterior não tenha reportado erro, tal como acontece
*               com todos os comandos, exceto =recuperar.
*               O comando permite recuperar falhas sinalizadas por
*               módulos de apoio, tais como, leitor de parâmetros,
*               contador de passagens e controle de espaço dinâmico.
*               Caso o contador de número de falhas contenha um valor
*               diferente de numFalhas, será reportado um erro e
*               o contador é incrementado de 1.
*
*     Os demais comandos são passados para as funções de teste específico.
*     Primeiro para as do arcabouço, depois para a específica do módulo
*     a testar. A última função de teste específico deve retornar a condição
*     TST_CondRetNaoConhec caso não consiga interpretar a diretiva.
*
*  $EIM Interface com outros módulos
*     A primeira função do arcabouço ("framework") a ser chamada deve a
*     sempre ser TST_InicializarTeste. Caso não o seja, ocorrerão erros
*     de execução (assert).
*
*     Após abra o arquivo de script executando a função
*     TST_AbrirArquivoScript. Se for desejado gerar um log abra
*     o arquivo corresponente com a função TST_AbrirArquivoLog.
*
*     Depois de abrir os arquivos, execute os testes chamando a função
*     TST_RealizarTeste. A função de teste genérico lerá todo o arquivo
*     de script, retornando após concluir o teste.
*
*     Após, termine o teste através da função TST_TerminarTeste.
*     Esta função exibe as estatísticas do teste e, caso solicitado,
*     acumula essas estatísticas em um arquivo acumulador (ver
*     parâmetro /a do programa principal.
*
*     As funções "TST_ObterXXX" podem ser utilizadas antes de fechar o
*     módulo de teste para exibir o resumo do teste no módulo cliente do
*     módulo de controle genérico.
*
*     O programa cliente do módulo controle de teste genérico pode
*     efetuar as operações acima repetidas vezes, permitindo, assim o
*     teste envolvendo diversos arquivos scripts de teste. A saída
*     de cada teste deve ser dirigida para um log específico, ou para
*     stdout, uma vez que, ao abrir um arquivo log, o seu conteúdo será
*     sempre destruído.
*
*     O módulo de teste genérico também implementa diversas funções
*     de comparação "TST_CompararXXX" use-as no módulo de controle de
*     teste específico. Desta forma será assegurado o tratamento uniforme
*     de todas as falhas possivelmente encontradas.
*
*     O módulo disponibiliza ainda a função TST_ExibirPrefixo
*     que gera uma linha de saída obedecendo aos padrões de interface
*     estabelecidos. Sendo desejado pode-se adicionar textos à linha
*     usando a funcao fprintf( TST_pArqLog , ... ). Um exemplo disso
*     é quando se deseja imprimir informação complementar ao interpretar
*     uma determinada diretiva.
*
*     Finalmente, o módulo disponibiliza a função TST_NotificarFalha
*     que incrementa o contador de falhas além de emitir uma mensagem
*     de erro.
*
***************************************************************************/
 
#if defined( GENERICO_OWN )
   #define GENERICO_EXT
#else
   #define GENERICO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

#include    "tst_espc.h"


/***********************************************************************
*
*  $TC Tipo de dados: TST Cond ret módulo de teste genérico
*
*
***********************************************************************/

   typedef enum {

         TST_CondOK ,
               /* Generico executou correto */

         TST_CondNaoAbriu
               /* Genérico não abriu arquivo */

   } TST_tpCond ;


/***********************************************************************
*
*  $FC Função: TSTG &Inicializar o módulo de teste
*
*  $ED Descrição da função
*     Inicializa todas as variáveis globais exportadas e encapsuladas
*     do módulo de teste genérico.
*
*     Embora pouco recomendável (ver descrição do módulo TesteSpc)
*     esta função pode ser alterada para assegurar o estabelecimento
*     do contexto inicial do módulo TesteSpc. Este deve conter uma
*     função de inicialização a ser chamada pela presente função.
*
***********************************************************************/

   void TST_InicializarTeste( void ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Terminar a execução do módulo de teste
*
*  $ED Descrição da função
*     Fecha todos os arquivos e desaloca todos os espaços de dados
*     alocados sob controle do módulo de teste genérico
*
***********************************************************************/

   void TST_TerminarTeste( void ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Obter origem do nome da extensão de arquivo
*
*  $ED Descrição da função
*     Procura o início do nome da extensão contido no nome do arquivo
*     dado por parâmetro
*
*     Evite o uso de nomes de arquivos com dois ou mais caracteres ".".
*     Isto pode confundir no caso de se desejar a adição de algum nome
*     de extensão padrão.
*
*  $EP Parâmetros
*     $P NomeArqParm - nome de arquivo a ser analisado
*
*  $FV Valor retornado
*     Ponteiro para o caractere '.' que separa a extensão.
*     Será NULL caso o nome do arquivo não contenha extensão.
*
***********************************************************************/

   char * TST_ObterInicioExtensao( char * NomeArqParm ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Abrir arquivo log
*
*  $ED Descrição da função
*     Abre o arquivo log a ser utilizado como saída durante os testes.
*     Todas as saídas geradas pelo módulo de teste são dirigidos para
*     este arquivo. Caso não tenha sido aberto, será utilizado o
*     arquivo stdout.
*
*     A extensão default do arquivo log é ".log" e será acrescida ao nome
*     do arquivo caso este não contenha nome de extensão.
*
*  $EP Parâmetros
*     $P NomeArqParm - nome do arquivo. Pode (deve) ser um nome relativo
*                      ao diretório corrente. Caso o arquivo
*                      exista, será destruido sem perguntar se pode.
*
*  $FV Valor retornado
*     TST_CondRetOK       - abriu corretamente
*     TST_CondRetNaoAbriu - ocorreu algum problema ao tentar abrir.
*                           O problema não é descriminado.
*                           O arquivo de saída do log volta a ser stdout
*
*  $EIU Interface com usuário pessoa
*     Esta função deve ser chamada antes de iniciar a execução dos testes.
*
***********************************************************************/

   TST_tpCondRet TST_AbrirArquivoLog( char * NomeArqParm ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Obter ponteiro para arquivo LOG
*
*  $ED Descrição da função
*     Retorna o ponteiro para o FILE do log.
*     Será stdout caso não seja definido explicitamente por
*     TSTG_DefinirLog
*
*  $FV Valor retornado
*     Ponteiro válido para um arquivo de texto de saída
*
***********************************************************************/

   FILE * TST_ObterArqLog( void ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Registrar nome do arquivo acumulador
*
*  $ED Descrição da função
*     Registra o nome do arquivo acumulador. Este arquivo é utilizado
*     para acumular as estatísticas de um teste formado por um conjunto
*     de massas de teste. Cada massa de teste gera o seu conjunto de
*     estatísticas de execução. O arquivo acumulador acumula estas
*     estatísticas permitindo ver o total de todas as massas de teste.
*
*  $EIU Interface com usuário pessoa
*     O arquivo acumulador tem serventia somente se o teste é formado
*     por um conjunto de duas ou mais massas de teste.
*     Antes de executar a primeira deve ser apagado o arquivo acumulador.
*     Após terminar a execução da última massa de teste exiba o resultado
*     como o programa "ExbeEstat" que faz parte do arcabouço.
*
***********************************************************************/

   void TST_RegistrarArquivoAcumulador( char * pNomeArquivoAcumulador ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Interpretar toda a massa de teste
*
*  $ED Descrição da função
*     Interpreta o arquivo de diretivas (script) de teste já aberto
*
*     A função de teste é dividida em três classes de comandos:
*
*     - os de teste genérico, que coordenam e controlam a realização do
*       teste. Estes comandos são interpretados por esta função.
*     - os de teste e controle de módulos componentes do arcabouço.
*       Estes comandos são interpretados por funções de teste específicas
*       para cada um dos módulos componentes.
*     - os de teste específico do módulo (ou módulos) a ser testado.
*       O módulo de teste específico interpreta os comandos projetados
*       para realizar os testes do módulo a testar.
*
*     A função de teste genérico lê um arquivo de diretivas de teste.
*     Cada linha deste arquivo é um comando de teste.
*     A função de teste lê uma a uma as linhas do arquivo, limpa os
*     caracteres em branco no final da linha e procura interpretar o
*     comando.
*
*     As funções de teste específicas comunicam os resultados da execução
*     de cada comando por meio de uma condição de retorno.
*
*     Cada linha do arquivo script de teste corresponde a um comando de
*     teste.
*
*     Caso seja encontrada uma falha não esperada (ver comando =recuperar)
*     os restantes comandos do caso de teste serão ignorados e contados
*     como problemas.
*
*     A sintaxe utilizada pelos comandos de teste é semelhante a assembler.
*     Esta sintaxe facilita a análise:
*
*        =<cmd> <parâmetros>
*
*     em que:
*        =            - todos os comandos a serem interpretados iniciam
*                       com este caractere
*        <cmd>        - é o string que identifica o comando
*        <parâmetros> - são zero ou mais itens a serem utilizados
*                       pelo comando de teste. Os itens devem, de preferência,
*                       ser separados um do outro por um caractere "espaço"
*
*     Deve ser adotado o seguinte padrão de uso:
*
*     - procure sempre utlizar uma das funções TST_CompararXXX, na forma:
*          return TST_CompararXXX( valoresperado, funcao a testar , mensagem )
*
*     - as funções de comparação fornecidas sempre geram as mensagens no
*       padrão estipulado
*
*     - quando não for possível utilizar uma função de comparação, reporte
*       a falha, esperadas ou não, através da função
*          TST_ImprimirPrefixo( Mensagem )
*
*     - a seguir mostre o valor esperado e o obtido
*
*     - Informações relativas a falhas dos testes são sinalizadas por
*       uma mensagem iniciando com ">>>" o número da linha do comando de teste
*       e o número de falhas encontradas até o momento.
*
*     - Informações relativas à execução dos testes são sinalizadas por
*       uma mensagem iniciando com "!!!".
*
*  $FV Valor retornado
*     TST_CondRetErro   - caso tenha sido encontrado um ou mais problemas
*     TST_CondRetOK     - caso o teste tenha terminado com zero problemas
*                         não esperados.
*
*  $FGP Tipos e Variáveis globais externas do próprio módulo
*     pArqScript - deve referenciar o arquivo script aberto
*     pArqLog    - deve referenciar o arquivo log aberto
*
***********************************************************************/

   TST_tpCondRet TST_RealizarTeste( char * Construto ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Obter número de casos de teste efetuados
*
*  $ED Descrição da função
*     Retorna o número de casos de teste lidos.
*     Cada caso de teste inicia com o comando "== <nome do caso de teste>".
*
***********************************************************************/

   int TST_ObterNumCasosTeste( ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Obter número de comandos específicos corretamente interpretados
*
*  $ED Descrição da função
*     Retorna o número de comandos de teste específicos lidos e
*     corretamente interpretados. Não conta comandos que retornem não OK
*     independentemento do motivo. Também não conta comandos recuperar.
*
***********************************************************************/

   int ObterNumComandosExecutados( void ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Obter número de problemas encontrados
*
*  $ED Descrição da função
*     Retorna o número de problemas encontrados.
*     O módulo de teste específico sinaliza problemas através de
*     uma condição de retorno diferente de TST_CondRetOK.
*     São tratados como problema também comandos de teste em erro,
*     e todos os comandos de teste de um dado caso de teste ignorados
*     em virtude de alguma falha encontrada.
*     Portanto, é possível que o número de problemas venha a ser maior do
*     que o número de casos de teste existente no script.
*
***********************************************************************/

   int TST_ObterNumFalhas( void ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Incrementar contador de falhas
*
***********************************************************************/

   void TST_ContarFalhas( ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Comparar booleano
*
*  $ED Descrição da função
*     Compara valor booleano esperado com valor booleano obtido,
*     reportamdo uma falha caso não sejam iguais.
*     Note que "!= 0" corresponde a TRUE e "== 0" corresponde a FALSE
*
*  $EP Parâmetros
*     ValorEsperado  - é um valor fornecido como parâmetro do comando
*                      de teste
*     ValorObtido    - é o valor retornado pela função em teste
*     pMensagem      - mensagem explanatória da falha encontrada
*
*  $FV Valor retornado
*     TST_CondRetErro  se o valor esperado não for consistente com o obtido
*     TST_CondRetOK    se os valores forem consistentes
*
***********************************************************************/

   TST_tpCondRet TST_CompararBool( int    ValorEsperado ,
                                   int    ValorObtido   ,
                                   char * pMensagem      ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Comparar caractere
*
*  $ED Descrição da função
*     Compara um caractere esperado com um caractere obtido, emitindo mensagem de
*     erro caso não sejam iguais.
*
*  $EP Parâmetros
*     ValorEsperado  - é um valor fornecido como parâmetro do comando
*                      de teste
*     ValorObtido    - é o valor retornado pela função em teste
*     pMensagem      - mensagem explanatória da falha encontrada
*
*  $FV Valor retornado
*     TST_CondRetErro  se o valor esperado não for igual ao obtido
*     TST_CondRetOK    se os valores forem iguais
*
***********************************************************************/

   TST_tpCondRet TST_CompararChar( char   ValorEsperado ,
                                   char   ValorObtido   ,
                                   char * pMensagem       ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Comparar inteiro
*
*  $ED Descrição da função
*     Compara valor inteiro long esperado com valor inteiro obtido,
*     reportamdo uma falha caso não sejam iguais.
*
*  $EP Parâmetros
*     ValorEsperado  - é um valor fornecido como parâmetro do comando
*                      de teste
*     ValorObtido    - é o valor retornado pela função em teste
*     pMensagem      - mensagem explanatória da falha encontrada
*
*  $FV Valor retornado
*     TST_CondRetErro  se o valor esperado não for igual ao obtido
*     TST_CondRetOK    se os valores forem iguais
*
***********************************************************************/

   TST_tpCondRet TST_CompararInt( long   ValorEsperado ,
                                  long   ValorObtido   ,
                                  char * pMensagem       ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Comparar flutuante
*
*  $ED Descrição da função
*     Compara valor flutuante esperado com valor flutuante obtido,
*     reportando uma falha caso
*     1 - Tolerancia > esperado / obtido ou
*     1 + Tolerancia < esperado / obtido
*
*  $EP Parâmetros
*     ValorEsperado  - é um valor fornecido como parâmetro do comando
*                      de teste
*     ValorObtido    - é o valor retornado pela função em teste
*     Tolerância     - indica os limites da relação entre esperado e obtido.
*                      Deve ser um valor positivo, menor do que 1.
*                      Use um valor do tipo 10 ** -n, no qual n é o
*                      número de dígitos significativos desejado.
*     pMensagem      - mensagem explanatória da falha encontrada
*
*  $FV Valor retornado
*     TST_CondRetErro  se o valor obtido não estiver dentro do domínio da
*                      tolerância em torno do valor esperado
*     TST_CondRetOK    se os valores estiverem dentro da tolerância
*
***********************************************************************/

   TST_tpCondRet TST_CompararFloat( double   ValorEsperado ,
                                    double   ValorObtido   ,
                                    double   Tolerancia    ,
                                    char *   pMensagem      ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Comparar string
*
*  $ED Descrição da função
*     Compara string esperado com string obtido, reportamdo uma falha
*     caso não sejam iguais. Ambos os strings devem obedecer o
*     padrão C, terminando em zero.
*
*  $EP Parâmetros
*     ValorEsperado  - é um string fornecido como parâmetro do comando
*                      de teste.
*     ValorObtido    - é o string retornado pela função em teste
*     pMensagem      - mensagem explanatória da falha encontrada
*
*  $FV Valor retornado
*     TST_CondRetErro  se o valor esperado não for igual ao obtido
*     TST_CondRetOK    se os valores forem iguais
*
***********************************************************************/

   TST_tpCondRet TST_CompararString( char * ValorEsperado ,
                                     char * ValorObtido   ,
                                     char * pMensagem       ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Comparar espaço
*
*  $ED Descrição da função
*     Compara espaços de dados, reportando uma falha caso não sejam iguais.
*     Esta função pode ser utilizada para comparar qualquer coisa,
*     inclusive valores do tipo  "struct"
*     O tipo do valor é indefinido e os valores serão exibidos em
*     formato hexadecimal, caso não sejam iguais
*
*  $EP Parâmetros
*     ValorEsperado  - ponteiro para o espaço que contém o valor esperado
*     ValorObtido    - ponteiro para o espaço que contém o valor obtido
*     TamEspaco      - tamanho do espaço a ser comparado
*     pMensagem      - mensagem explanatória da falha encontrada
*
*  $FV Valor retornado
*     TST_CondRetErro  se o valor esperado não for igual ao obtido
*     TST_CondRetOK    se os valores forem iguais
*
***********************************************************************/

   TST_tpCondRet TST_CompararEspaco( void * ValorEsperado ,
                                     void * ValorObtido   ,
                                     int    TamEspaco     ,
                                     char * pMensagem       ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Comparar ponteiro
*
*  $ED Descrição da função
*     Compara dois ponteiros emitindo uma mensagem caso não sejam iguais
*
*  $FV Valor retornado
*     TST_CondRetErro  se os dois ponteiros forem diferentes
*     TST_CondRetOK    se forem iguais
*
***********************************************************************/

   TST_tpCondRet TST_CompararPonteiro( void * PonteiroEsperado ,
                                       void * PonteiroObtido   ,
                                       char * pMensagem       ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Comparar ponteiro nulo
*
*  $ED Descrição da função
*     Verifica
*       - quando ModoEsperado     é 0 se o ponteiro é nulo
*       - quando ModoEsperado não é 0 se o ponteiro é não nulo
*
*  $FV Valor retornado
*     TST_CondRetErro  se os dois ponteiros forem diferentes
*     TST_CondRetOK    se forem iguais
*
***********************************************************************/

   TST_tpCondRet TST_CompararPonteiroNulo( int ModoEsperado ,
                                           void * PonteiroObtido   ,
                                           char * pMensagem       ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Assertiva controlada
*
*  $ED Descrição da função
*     Esta função substitui a função assert de C.
*     É utilizada no contexto do arcabouço de teste.
*     Ela imprime mensagens mais visíveis tanto no log como na
*     janela de comando.
*
*     Recomenda-se, no entanto, utilizar a função assert de C em aplicações.
*
*  $FV Valor retornado
*     Termina a execução do programa com código de retorno == 4
*
***********************************************************************/

   #define  TST_ASSERT( Expressao ) \
      TST_Assert( Expressao , __LINE__ , __FILE__ )

   void TST_Assert( int Expressao , int Linha , char * NomeArq ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Notificar falha
*
*  $ED Descrição da função
*     Exibe uma mensagem de falha no formato padrão do arcabouço.
*
*  $FV Valor retornado
*     TST_CondRetErro  sempre
*
***********************************************************************/

   TST_tpCondRet TST_NotificarFalha( char * pMensagem ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Exibir prefixo da mensagem
*
*  $ED Descrição da função
*     Imprime o prefixo de mensages de falha
*
*  $EH Hipóteses assumidas pela função
*     O contador de falhas é incrementado somente pela função de teste
*     genérica e após à conclusão da interpretação do comando.
*
***********************************************************************/

   void TST_ExibirPrefixo( char * Indicador , char * pMensagem ) ;


/***********************************************************************
*
*  $FC Função: TSTG &Exibir um espaço qualquer em formato hexadecimal e char
*
*  $EP Parâmetros
*     $P tamEspaco - tamanho em bytes do espaço a exibir
*     $P Ponteiro  - ponteiro para o primeiro byte do espaço a exibir
*
***********************************************************************/

   void TST_ExibirEspacoHexa( int    tamEspaco ,
                              void * Ponteiro   ) ;

#undef GENERICO_EXT

/********** Fim do módulo de definição: TSTG Controlador de teste genérico **********/

#else
#endif
