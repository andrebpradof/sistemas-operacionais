# Trabalho 2 - Comunicação. Sincronismos, Deadlock, Threads
<h4>SSC0640 - Sistemas Operacionais I (2020)</h4>
<p>Prof. Assoc. Júlio Cezar Estrella</p>

<h3>Grupo 08:</h3>

André Baconcelo Prado Furlanetti - Nº USP: 10748305 </br>
Diego da Silva Parra - Nº USP: 10716550</br>
Mateus Fernandes Doimo - Nº USP: 10691971</br>

</br>

<b>:video_camera: Vídeo:</b> <a href="https://youtu.be/bw-eYroNs7w">LINK AQUI</a><br><br>
<b>:page_facing_up: Apresentação:</b> <a href="https://github.com/andrebpradof/sistemas-operacionais/tree/master/trabalho_2/apresentacao">Trabalho 2 - Produtor e Consumidor - grupo 08</a><br>
<br>
<hr>

<h3>:pencil: Descrição do trabalho:</h3>
<h3>Produtor Consumidor</h3>
<p>O problema do Produtor e o Consumidor consiste em um conjunto de processos que compartilham um mesmo buffer. Os processos chamados produtores colocam informação no buffer. Os processos chamados consumidores retiram informação deste buffer. 
<br>
Trata-se de um problema clássico em sistemas operacionais, que busca exemplificar de forma clara, situações de impasses que ocorrem no gerenciamento de processos de um sistema operacional. É preciso se preocupar com acessos indevidos a certos recursos que são compartilhados entre os processos, e manter sincronismo entre os mesmos. 
<br>
Para controlarmos o acesso a essas variáveis e garantir o sincronismo nas operações, vamos utilizar semáforos. Em ciência da computação, semáforo é uma variável especial protegida (ou tipo abstrato de dados) que tem como função o controle de acesso a recursos compartilhados (por exemplo, um espaço de armazenamento) num ambiente multitarefa. Com as variáveis do tipo pthread_mutex_t da biblioteca pthreads - Posix, podemos controlar esses dados com toda segurança. 
<br>
Outro controle importante é a demanda de processamento, espera ociosa, que o programa irá gerar, pois quando um processo não está liberado para gravar ou ler, deve entrar em estado de espera para não consumir processamento, e deve ser avisado quando pode voltar a processar.</p>
<br>
<h3>O Problema</h3>
<ul>
    <li>O produtor insere em uma região: Ainda não houve consumo</li>
    <li>O consumidor remove de uma região: Já foi consumida</li>
    <li>Espera ociosa X Escalonamento do processo X Uso CPU</li>
</ul>
<h3>A Solução</h3>
<ul>
    <li>Utilizar Exclusão mutua (semáforos)</li>
    <li>Eliminar a espera ociosa:</li>
    <li>Dormir (dow) /acordar (up) X Semáforos full/empty</li>
    <li>Mutex (Mutual exclusion)</li>
</ul>
<p>A solução do problema deve utilizar a biblioteca pthreads, a qual possibilita a programação de forma concorrente com as funções de: controle de threads, criação de threads, suspensão de threads, execução e controle de exclusão mútua por semáforos binários, para controle da seção crítica.</p>