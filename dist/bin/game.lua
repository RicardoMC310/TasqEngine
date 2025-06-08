function start()
    print("LUA: Start...")

    init()
    window = createWindow("Window", 640, 480)

end

function update(deltaTime)
    
end

function cleanup()
    print("LUA: Finalizando...")
    destroyWindow(window)
end

