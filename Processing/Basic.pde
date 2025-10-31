void setup(){
  println("setup");
  size (600, 600);
  background(0,255, 255);
}

void draw(){
  int centerX = 100;
  int centerY = 50;
  ellipse(centerX, centerY, 100, 100);
  ellipse(centerX+200, centerY, 100, 100);
  ellipse(centerX+400, centerY, 100, 100);
  line(centerX, centerY, 500, 50);
}
