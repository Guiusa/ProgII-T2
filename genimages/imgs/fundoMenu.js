new p5(function (k) {
    var cnv;
    const WIDTH = 800;
    const HEIGHT = 600;
    k.setup = function(){
        cnv = k.createCanvas(WIDTH, HEIGHT);
        k.background(0);
        k.strokeWeight(2);

        for(var i=0; i<=25; i++){
            k.stroke(colors[k.round(k.random(0, 3))]);
            var c = k.round(k.random(0, 2));
            if(c==0){
                k.line(WIDTH/2, HEIGHT, 0, k.random(0, HEIGHT));
            }
            else if(c==1){
                k.line(WIDTH/2, HEIGHT, k.random(0, WIDTH), 0);
            }
            else if(c==2){
                k.line(WIDTH/2, HEIGHT, WIDTH, k.random(0, HEIGHT));
            }
        }
    };

    k.mouseClicked = function () {
        if((k.mouseY >= 0 && k.mouseY <= HEIGHT) && (k.mouseX >= 0 && k.mouseX <= WIDTH)){
            k.save(cnv, "fundoMenu.png");
        }
    };

    k.draw = function(){

    };
}, "fundoMenu");