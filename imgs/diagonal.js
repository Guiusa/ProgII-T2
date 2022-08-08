new p5(function (k) {
    
    k.setup = function () {
        var cnv = k.createCanvas(1080, 1080);
        k.fill(255, 130, 0);
        k.noStroke();
        k.stroke(255, 0, 0);
        k.strokeWeight(5);
        k.ellipse(540, 540, 500, 500);
        //k.save(cnv, "ball.png");
    };
    k.draw = function () {
    };
}, "diagonal");