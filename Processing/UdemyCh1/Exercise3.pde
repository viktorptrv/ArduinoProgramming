int y, x, increment;

void setup(){
  y = 100;
  x = 50;
  size(600, 600);
  increment = 1;
}

void draw(){
  background(255);
  for(int i = 0; i < 5; i++){
    ellipse(x,y * (i+1), 100, 100);
    x+=increment;
    if ((x + 50 > width) || (x - 50 < 0)){
      increment = -increment;
    }
  }
}
