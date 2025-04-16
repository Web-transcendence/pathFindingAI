import {FastifyInstance} from "fastify";
import {Ball, moveBall} from "./simulation.js";
import {z} from "zod";
import {join} from "node:path";
import {readFileSync} from "node:fs";
import {writeFile} from "node:fs/promises";
import {clearInterval} from "node:timers";

export default async function routes(app: FastifyInstance) {
    // app.get('/ws', { websocket: true }, (req: FastifyRequest, socket) => {
    //     console.log("Client connected");
    //     let ball = new Ball (0, 0, 0.75, 8);
    //
    //     const intervalId = setInterval(() => {
    //         socket.send(JSON.stringify(ball));
    //     }, 10);
    //
    //     socket.on("close", () => {
    //         clearInterval(intervalId);
    //         console.log("Client disconnected");
    //     });
    //
    //     moveBall(ball);

    // });

    app.get("/pong.js", (req, res) => {
        const pongPath = join(import.meta.dirname, "pong.js");
        console.log(pongPath);
        const file = readFileSync(pongPath, 'utf8');
        res.type('text/js').send(file);
        return;
    })

    app.get("/dl", () => {
            let ball = new Ball (0, 0, 0.75, 8);
            let obj = [];

            let i = 60000;

            const intervalId = setInterval(() => {
                if (i <= 0) {
                    clearInterval(intervalId);
                    return ;
                }
                console.log(i);
                obj.push(ball.getData())
                i--;
            }, 10);

            await writeFile('parsing.json', JSON.stringify(obj, null, 2), 'utf8');


            moveBall(ball);
    })
}
