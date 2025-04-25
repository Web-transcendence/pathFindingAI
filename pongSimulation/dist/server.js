import express from "express";
import { WebSocketServer } from "ws";
import http from "http";
import path from "path";
import { fileURLToPath } from "url";
import fs from 'fs';
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);
const app = express();
const server = http.createServer(app);
const wss = new WebSocketServer({ server });
app.use(express.static(path.join(__dirname, "../public")));
wss.on("connection", (ws) => {
    console.log("Client connected");
    ws.on("message", (message) => {
        const data = JSON.parse(message.toString());
        if (data.type === "input") {
            // console.log(`Touche ${data.key} est ${data.state}`);
            // Traiter le mouvement de la raquette ici
        }
        if (data.type === "save") {
            const path = "gameState.json";
            const newEntry = data.data; // un objet JSON
            let fileContent = [];
            if (fs.existsSync(path)) {
                const raw = fs.readFileSync(path, "utf8");
                if (raw.trim()) {
                    const parsed = JSON.parse(raw);
                    fileContent = Array.isArray(parsed) ? parsed : [];
                }
            }
            fileContent.push(newEntry);
            fs.writeFileSync(path, JSON.stringify(fileContent, null, 2), "utf8");
        }
    });
    ws.on("close", () => console.log("Client disconnected"));
});
server.listen(8080, () => {
    console.log("Server running on http://localhost:8080");
});
