function start()
    init()
    createWindow("Window", 640, 480)

    player = {
        x = 0,
        y = 0,
        w = 64,
        h = 64,
        spd = 250,
        image = saveTexture("./spaceship.png")
    }

end

function update(deltaTime)

    local dx = 0
    local dy = 0

    if isKeyDown("Right") then
        dx = dx + 1
    end

    if isKeyDown("Left") then
        dx = dx - 1
    end

    if isKeyDown("Down") then
        dy = dy + 1
    end

    if isKeyDown("Up") then
        dy = dy - 1
    end

    player.x = player.x + dx * player.spd * deltaTime
    player.y = player.y + dy * player.spd * deltaTime

    if player.x < 0 then
        player.x = 0
    elseif player.x + player.w > 640 then
        player.x = 640 - player.w
    end

    if player.y < 0 then
        player.y = 0
    elseif player.y + player.h > 480 then
        player.y = 480 - player.h
    end

    drawTexture(player.image, player.x, player.y, player.w, player.h)
end

function cleanup()
    destroyTexture(player.image)
    destroyWindow()
end

function onKeyEvent(key, action)
    
    if key == "Left Shift" and action == "Pressed" then
        player.x = 0
        player.y = 0
    end

end
