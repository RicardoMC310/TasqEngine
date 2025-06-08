# 💻 Tasq Engine 💻

Uma engine simples, leve e versátil! Perfeita para jogos _**indie**_

---

<br/>

## 💯 Algumas Features 💯
1. 😎 Possibilidade de interpretar o código do seu jogo fácilmente.
2. 🧠 Super leve e fácil de criar jogos, não é muito verbosa, graças a implementação com a linguagem lua.
3. 🔥 Implementação com SDL2, o que permite o jogo ser multiplataforma ( mais para frente ).
4. 💼 Sistema de funções muito bem organizadas.


<br/>

---

<br/>

## ☁️ Dependências Para Compilar ☁️
> Necessário enquanto não faço a disponibilização do build final.

<br/>

| Biblioteca  |
| ----------  |
| SDL2        |
| SDL2_image  |
| Lua^5.0     |

<br/>

---

<br/>

### ⁉️ Como Faço Para Compilar ⁉️

> Após certifica-se de resolver as dependências do projeto, agora é so usar o cmake para compilar.

<br/>

```bash
git clone https://github.com/RicardoMC310/TasqEngine.git
cd TasqEngine
mkdir build
cmake -B build
make
cmake --install .
```

<br/>

após compilar o bińario estará disponivel na pasta **./dist/bin**

<br/>

---

<br/>

## 😊 Como Executo Meu Jogo 😊

> após compilar e ter o executável, precisamos definir algumas coisas

<br/>

---

<br/>

### 👾 O Que Já possuo 👾

poucas funções, mas depois falo disso.

| Name              | O que faz                  |
| ----------------- | -------------------------- |
| start()           | Ponto de entrada da engine |
| update(deltatime) | Chamada a cada frame       |
| cleanup()         | Ponto de saída da engine   |
| onKeyDown(key)    | Recebe a tecla pressionada |
| onKeyUp(key)      | Recebe a tecla liberada    |
| onMouseButton(button, action, x, y) | Recebe o click do mouse |
| onMouseMotion(x, y, xrel, yrel) | Recebe o movimento do mouse |
| onMouseWheel(x, y) | Recebe o scrool do mouse |

> onKeyDown e onKeyUp logo serão unidas em uma única função.

<br/>

---

<br/>

### 💀 Especificações De Uso 💀

bom enterder o conceito antes de sair usando

<br/>

_**❗Funções Obrigatórias❗**_
- **start()**: Ponto de entrada da engine, onde serão criadas as variáveis dentre outras coisas que precisaram na engine.
- **update(deltaTime)**: Ponto de chamada a cada frame, e tem como passagem de parâmetros o _**deltaTime**_, que é usado para controlar as atualizações uniformemente independentemente de quantos FPS está rodando o jogo.
- **cleanup()**: Ponto de saída do programa, aqui é onde você exclui variáveis, limpa cache, salva o game num arquivo, pode ter várias funcionalidades.

_**🤷‍♂️Funções Opcionais🤷‍♂️**_

- **onKeyDown(key)**: Chamado quando alguma tecla for pressionada, o parâmetro _**key**_ é o nome da tecla, exemplo: *"Up"*, *"Down"*, *"A"*, *"Space"* e etc.
- **onKeyUp(key)**: Mesma coisa do **OnKeyDown(key)**, mas é chamada apenas quando alguma tecla for liberada.
- **onMouseButton(button, action, x, y)**: Função chamada quando houver clique do mouse, seus parâmetros são: 
  - **button**: Botão pressionado, exemplo: *"Right"*, *"Middle"* ou *"Left"*.
  - **action**: Explica se o botão foi pressionado ou liberado, você pode checar com o enum `MouseButton.PRESSED` ou `MouseButton.RELEASED`
  - **X e Y**: São as coordenadas onde o clique foi disparado, assim sabendo exatamente onde o **usuário** clicou
- **onMouseMotion(x, y, xrel, yrel)**: Chamada quando houver movimentação do mouse, seguintes parâmetros:
  - **X e Y**: são as coordenadas brutas, exemplos: *"380 e 893"*, *"26 e 423"*, *"326 e 37"* e etc.
  - **Xrel e Yrel**: São os deltas da movimentação, o quanroto que o mouse se moveu, exemplos: *"-1 e 0"*, *"10 e 4"*, *"2 e -7"*, *0 e 3* e etc.
- **onMouseWheel**: Chamada quando houver scrool, já trata se o **usuário** estiver com o scrool invertido, seu parâmetros são simples, **X e Y**, sendo X para scrool lateral -1, 0 ou 1, e Y para scrool vertical -1, 0 ou 1.
  
<br/>

---

<br/>

## 👼 O Que Pretendo Incluir Agora 👼
lista do que já possui e o que ainda vai possuir

<br/>

- [x] Integração com lua.
- [x] Criação da janela.
- [x] Renderizar BackGround.
- [x] Eventos.
- [ ] Unir **onKeyUp(key)** com **onKeyDown(key)**.
- [ ] Desenhar retângulos.
- [ ] Criação de entidades.

<br/>

> mais para frente vou adicionando tópicos.