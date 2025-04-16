
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



export function moveBall(ball: Ball) {
    ball.x += Math.cos(ball.angle * Math.PI - Math.PI / 2) * ball.speed / 1000;
    ball.y += Math.sin(ball.angle * Math.PI) * ball.speed / 1000;
    if (ball.y > 0.8) {
        ball.y = 0.8 - (ball.y - 0.8);
        ball.angle = ball.angle > 0 ? 1 - ball.angle : - 1 - ball.angle;
    } else if (ball.y < -0.8) {
        ball.y = -0.8 - (ball.y + 0.8);
        ball.angle = ball.angle > 0 ? 1 - ball.angle : - 1 - ball.angle;
    }
    if (ball.x > 1) {
        ball.x = 1 - (ball.x - 1);
        ball.angle = - ball.angle;
    } else if (ball.x < -1) {
        ball.x = -1 - (ball.x + 1);
        ball.angle = - ball.angle;
    }
    setTimeout(() => moveBall(ball), 10);
}




