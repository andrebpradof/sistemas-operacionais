# Trabalho 3 - Gerenciamento de Memória
<h4>SSC0640 - Sistemas Operacionais I (2020)</h4>
<p>Prof. Assoc. Júlio Cezar Estrella</p>

<h3>Grupo 08:</h3>

André Baconcelo Prado Furlanetti - Nº USP: 10748305 </br>
Diego da Silva Parra - Nº USP: 10716550</br>
Mateus Fernandes Doimo - Nº USP: 10691971</br>

</br>

<b>:video_camera: Vídeo:</b> <a href="#">LINK AQUI</a><br><br>
<b>:page_facing_up: Apresentação:</b> <a href="https://github.com/andrebpradof/sistemas-operacionais/tree/master/trabalho_3/apresentacao">Trabalho 3 - Gerenciamento de Memória - grupo 08</a><br>
<br>
<hr>

<h3>Executar o simulador:</h3>

#### Compilar programa:
`$ make`
#### Executar programa:
`$ ./memoria`

<br>
<hr>
<h3>:pencil: Descrição do trabalho:</h3>
<p>Desenvolver um simulador  de gerenciamento de memória virtual com paginação</p>
<p>Processos são submetidos e sua execução simulada, por meio de uma série de referências a memória. </p>
<p>Essas referências podem ser de leitura ou de gravação em um endereço de virtual memória.<br>
O simulador deve ler em arquivo(s) as informações sobre a "vida" do processo, contendo para cada processo, o tamanho de sua imagem e uma sequência de operações de acesso à memória principal que o respectivo processo realiza. </p>

<p>Algoritmo implementado: <b>Algoritmo de substituição de páginas relógio</b></p>