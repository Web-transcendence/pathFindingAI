import {Ball} from "./simulation.js";


const canvas = document.getElementById("gameCanvas") as HTMLCanvasElement;
const ctx = canvas.getContext("2d")!;
let connect: boolean = true;

class Assets {
    BarUp: HTMLImageElement = new Image();
    BarDown: HTMLImageElement = new Image();
    BallUp: HTMLImageElement = new Image();
    constructor () {
        this.BarUp.src = "./assets/barup.png";
        this.BarDown.src = "./assets/bardown.png";
        this.BallUp.src = "./assets/ballup.png";
    }
}

let animFrame = 0;
let animLoop = 1;
let ball = new Ball(canvas.width / 2, canvas.height / 2, 10, "#fcc800");
let asset = new Assets;