# 💻 Tasq Engine 💻

&nbsp;&nbsp;&nbsp;&nbsp;uma engine que por enquanto simples, mas semeia prosperidade.

![License](https://img.shields.io/github/license/RicardoMC310/TasqEngine)
![Top Language](https://img.shields.io/github/languages/top/RicardoMC310/TasqEngine)
![Last Commit](https://img.shields.io/github/last-commit/RicardoMC310/TasqEngine)
![Version](https://img.shields.io/badge/version-1.0.0-blue)
![Engine](https://img.shields.io/badge/engine-Tasq-blueviolet)
![Language Created](https://img.shields.io/badge/language-cpp-red)

## ☁️ Dependências ☁️

| Dependências             |
|--------------------------|
| - Lua 5.0                |
| - SDL2                   |
| - SDL2_image             |

## 👉 Instalação 👈

&nbsp;&nbsp;&nbsp;&nbsp;clone a engine do repositório e a compile

```bash
  git clone https://github.com/RicardoMC310/TasqEngine.git
  cd TasqEngine
  cd build
  cmake ..
  make
  cmake --install .
```

&nbsp;&nbsp;&nbsp;&nbsp;agora você terá o binário em dist/bin.

## ⁉️ Como iniciar ⁉️
- primeiramente você terá que ter uma arquivo lua para interpretar
- após isso, você tem a disponibilidade de tais funções
```lua
  function start()
    -- variáveis aqui
  end

  function update(deltaTime)
    -- chamada a cada frame
  end

  function cleanup()
    -- limpar dados
  end

  function onKeyDown(key)
    -- quando a tecla for pressionada
  end

  function onKeyUp(key)
    -- quando a tecla for liberada
  end
  
  function onMouseButton(button, action, x, y)
    -- quando o mouse for clicado
  end

  function onMouseMotion(x, y, xrel, yrel)
    -- quando o mouse se mover
  end

  function onMouseWheel(x, y)
    -- quando quando a rodinha do mouse girar ou o touch
  end
  ```

> unicas que são obrigatórias são as start, update e cleanup

## 😂 Finalmente Rodando 😂

&nbsp;&nbsp;&nbsp;&nbsp; Com o seu código lua pronto. você terá que rodar a seguinte linha de comando
```bash
 ./tLaucher {nome do arquivo}.lua
```