const canvas = document.getElementById("gameCanvas") as HTMLCanvasElement;
const ctx = canvas.getContext("2d")!;

import {Ball, moveBall} from "./simulation.js"

const ball = new Ball (0, 0, 0.75, 8.0);

class gameState {
    state: number = 0;
    start: boolean = false;
}



let game = new gameState();
let ball = new Ball(canvas.width / 2, canvas.height / 2, 10, "#fcc800");



function mainLoop() {
    // Background
    ctx.fillStyle = "#101828";
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    // Mid
    ctx.fillStyle = "#364153";
    for (let i = 0; i < canvas.height; i += 60)
        ctx.fillRect(canvas.width * 0.5 - 4, i, 8, 30);

    // Ball : Square or Circle ?
    ctx.fillStyle = ball.color;
    ctx.fillRect(ball.x - ball.radius, ball.y - ball.radius + 4, ball.radius * 2, (ball.radius - 4) * 2)
    ctx.fillRect(ball.x - ball.radius + 4, ball.y - ball.radius, (ball.radius - 4) * 2, ball.radius * 2)

}

function gameLoop () {
    mainLoop()
    requestAnimationFrame(gameLoop);
}

gameLoop();