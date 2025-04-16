import Fastify from "fastify";
import websocketPlugin, {WebSocket} from "@fastify/websocket";
import routes from "./routes.js";


const app = Fastify();

app.register(websocketPlugin);
app.register(routes);

app.listen({ port: 7000, host: '0.0.0.0' }, (err, adrr) => {
    if (err) {
        console.error(err);
        process.exit(1);
    }
    console.log(`server running on ${adrr}`);
});