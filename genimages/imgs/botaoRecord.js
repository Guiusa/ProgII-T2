new p5(function (k) {
    var cnv;
    const WIDTH = 640;
    const HEIGHT = 240;
    k.setup = function(){
        cnv = k.createCanvas(WIDTH, HEIGHT);
        k.fill(colors[4]);
        k.noStroke();
        k.rect(0.1*WIDTH, 0.1*HEIGHT, 0.8*WIDTH, 0.8*HEIGHT, 50);
        k.fill(0);
        k.textSize(120);
        k.text("RECORD", 0.1*WIDTH, 0.65*HEIGHT);
    };

    k.mouseClicked = function () {
        if((k.mouseY >= 0 && k.mouseY <= HEIGHT) && (k.mouseX >= 0 && k.mouseX <= WIDTH)){
            k.save(cnv, "botaoRecord.png");
        }
    };

    k.draw = function(){

    };
}, "botaPlay");