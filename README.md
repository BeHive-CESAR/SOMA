# CentaurusMed 

> Este é um projeto para a cadeira de projetos 2 que visa auxiliar na administração e organização do programa de residencia do HC.
> Somos um grupo formado por estudantes de Design e Ciências da Computação da Cesar School e buscamos ajudar pessoas através de nossas soluções tecnológicas. 

# Somos Quíron

## 🤝 Equipe:
### 🎨 Designers 
<p>Camila Chagas<br>
Leonardo Lima<br>
Rodrigo Fialho<br>
Victória Siqueira</p>

### 💻 Devs
<p>Caio Barreto<br>
  Carlos Eduardo<br>
  Gabriel Chaves Oliveira<br>
  Lucas Gabriel de Brito<br>
  Maria Fernanda Marques<br>
  Pedro Villas Boas
</p>

<h3>Nosso produto: O SOMA</h3>
<p>Nosso produto trás aos preceptores e aos residentes do Hospital das Clinicas uma forma mais simples de realizar o processo de avaliação. Sendo um aplicativo mobile, gratuito e que possui três interfaces: Interface para Residente, Preceptor e uma para a coordenação. Permitindo a visualização do histórico das notas do residente assim como os feedbacks recebidos e além disso dando a possibilidade do residente tambem dar um feedback para o preceptor. Com isso tornando o ambiente da residencia mais eficiente.

Nesse código desenvolvido na linguagem C criamos um protótipo ilustrativo de como seria o funcionamento do app. Usando escrita e leitura de arquivos como banco de dados e o proprio terminal como uma interface </p>
##
<h3>Arquivos presentes no sistema</h3>
<dl>
  <dt>main.c</dt> <dd> Roda a função main.</dd>
  <dt>interface.c , interface.h</dt> <dd> Armazena as interfaces de todos os usuarios as organizando ao puxar funções das outras bibliotecas.</dd>
  <dt>login_cadastro.c , login_cadastro.h</dt> <dd> Realiza tarefa de registro dos novos usuarios no programa.</dd> 
  <dt>preceptor.c , preceptor.h</dt> <dd> Armazena funções utilizadas principalmente na interface no preceptor.</dd>
  <dt>residente.c , residente.h</dt> <dd> Armazena funções utilizadas principalmente na interface no residente.</dd>
  <dt>residentes_preceptores.c , residentes_preceptores.h</dt> <dd> Armazena funções utilizadas em todas interfaces. </dd>
  
  <dt>Alem desses,estaremos utilizando arquivos de texto gerados pelo proprio código como banco de dados. São esses:</dt>
  <dd>cadastrados.txt</dd>
  <dd>feedback_preceptor.txt </dd>
  <dd>feedbacks_residentes </dd>
  <dd>notas_residentes.txt </dd>
  <dd>atividades.txt </dd>

</dl>

##

<h3>(Explicar como utilizar o sistema, na perspectiva dos 3 usuários)</h3><br>
<dl>
  <dt>Coordenação</dt>
  <dd>A principio a interface da coordenação será acessada com um login e senha predefinidos `(admin, admin)`. Uma vez acessado, a    coordenação terá permissão de visualizar todas as informações dos residentes e preceptores, alem de poder cadastrar novos usuarios e criar novas atividades para os residentes.</dd>
  <dt>Preceptor</dt>
  <dd>Após a realização, por parte da coordenação, do cadastro do preceptor com seu email e senha, o mesmo poderá acessar a interface ao fazer o login. Já dentro de sua interface o usuario terá a opção de criar atividades, visualizar e avaliar os residentes dentro de sua residencia, além de fornecer feedbacks para seus alunos, e ver feedbacks recebidos.</dd>
  <dt>Residente</dt>
  <dd> </dd>
  
</dl>


<p><a href="https://sites.google.com/cesar.school/qiron/início?authuser=1">Link para nosso site</a></p>
