new p5(function (k) {
    var cnv;
    const HEIGHT = 15;
    const WIDTH = 15;
    k.setup = function () {
        cnv = k.createCanvas(WIDTH, HEIGHT);
        k.fill(colors[4]);
        k.noStroke();
        
        k.ellipse(WIDTH/2, HEIGHT/2, WIDTH, HEIGHT);
        //k.save(cnv, "ball.png");
    };
    k.mouseClicked = function () {
        if((k.mouseY >= 0 && k.mouseY <= HEIGHT) && (k.mouseX >= 0 && k.mouseX <= WIDTH)){
            k.save(cnv, "ball.png");
        }
    };

    k.draw = function () {
    };
}, "ball");