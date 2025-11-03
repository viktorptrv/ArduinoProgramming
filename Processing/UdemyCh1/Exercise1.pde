int y, x;

void setup(){
  y = 100;
  x = 50;
  size(600, 600);
}

void draw(){
  background(0,255,0);
  for (int i = 0; i < 4; i++){
     line(x-50, y-100, x, y);
     line(x, y, x-50, y+100);
     line(x-50,y+100,x, y+200);
     line(x, y+200, x-50, y+300);
     x+=100;
     delay(2000);
  }
 
}
