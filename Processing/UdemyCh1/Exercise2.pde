int y, x;

void setup(){
  y = 100;
  x = 50;
  size(600, 600);
}

void draw(){
  background(0,255,0);
  line(50, 50, 100, 50);
  stroke(16);
  line(50, 50, 75, 0);
  stroke(126);
  line(75, 0 , 100, 50);
  stroke(126);
}
