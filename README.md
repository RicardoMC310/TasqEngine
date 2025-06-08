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
