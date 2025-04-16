
import { z } from "zod";



export class Ball {
    x: number;
    y: number;
    angle: number;
    speed: number;

    i: number;

    constructor(x: number, y: number, angle: number, speed: number) {
        this.x = x;
        this.y = y;
        this.angle = angle;
        this.speed = speed;
    }
    toJSON() {
        return {x: this.x, y: this.y, angle: this.angle, speed: this.speed};
    }
    getData() {
        return {
            x: this.x,
            y: this.y,
            angle: this.angle,
            speed: this.speed,
        }
    }
}







function norAngle(ball: Ball) {
    if (ball.angle < 0)
        ball.angle += 2 * Math.PI;
    if (ball.angle > 2 * Math.PI)
        ball.angle -= 2 * Math.PI;
}


export function moveBall(ball: Ball) {
    ball.x += Math.cos(ball.angle) * ball.speed;
    ball.y += Math.sin(ball.angle) * ball.speed;
    if (ball.y > 800) {
        ball.y = 800 - (ball.y - 800);
        ball.angle = 2 * Math.PI - ball.angle;
    } else if (ball.y < 0) {
        ball.y = -ball.y;
        ball.angle = 2 * Math.PI - ball.angle;
    }
    norAngle(ball);
    setTimeout(() => moveBall(ball), 10);
}




