new p5(function (k) {
    var cnv;
    const WIDTH = 640;
    const HEIGHT = 240;
    k.setup = function(){
        cnv = k.createCanvas(WIDTH, HEIGHT);
        k.background(0);
        k.fill(colors[4]);
        k.rect(0, 0, WIDTH, HEIGHT, 40);
        k.fill(0);
        k.textSize(120);
        k.text("PLAY", 0.25*WIDTH, 0.65*HEIGHT);
    };

    k.mouseClicked = function () {
        if((k.mouseY >= 0 && k.mouseY <= HEIGHT) && (k.mouseX >= 0 && k.mouseX <= WIDTH)){
            k.save(cnv, "botaoPlay.png");
        }
    };

    k.draw = function(){

    };
}, "botaPlay");