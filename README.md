<img src="ResiFlow/img/ifsc-logo.png"
     width="30%"
     style="padding: 10px">
     
# Projeto Potentia
O projeto Potentia é o projeto desenvolvido pelos alunos Henrique Amaral Onuki e Gabriel Garcia para a unidade curricular de Projeto Integrador II, que faz a integração de outras unidades curriculares como Programação Orientada por Objetos, Microcontroladores I e Instrumentação Eletrônica.

O projeto consiste em realizar o controle de forma digital - através de um aplicativo de computador - de um AHDSR.
## Interface de Controle de Envelope AHDSR para VCA
Um AHDSR é um dos muitos módulos componentes de um sintetizador modular, que tem como objetivo realizar o controle de outros módulos através de sinais de tensão, sinais estes que no caso do AHDSR podem ser envelopados - moldados - para apresentarem uma natureza - geometria - diferente, que como resultado pode ser utilizado de inúmeras formas diferentes para se obter sinais de tensão que podem ser utilizados para fazer o controle de outros módulos com o intuito de gerar sons diferentes.

O objetivo é fazer o controle dos parâmetros Attack, Hold, Decay, Sustain e Release deste AHDSR de forma completamente digital, através de uma interface intuitiva em um computador.

Mais além, alguns objetivos secundários do projeto são:

1 - Desenvolvimento de um VCA (Voltage Controlled Amplifier), que será controlado pelo AHDSR.

2 - Geração e controle de uma onda senoidal fornecida para o VCA. O controle de frequência - pitch - da onda será realizado através de um sensor de distância.

![](concept/concept.png)

# ResiFlow
O aplicativo, de nome ResiFlow, deve fornecer formas de fazer o controle em tempo real dos parâmetros do AHDSR, disponibilizar suas formas de onda, 
salvar, alterar e carregar presets de parâmetros criados pelo usuário, e também disponibilizar de um sequenciador para o uso dinâmico dessas funcionalidades.
[**Mais sobre o ResiFlow**](./ResiFlow/README.md)<br>

