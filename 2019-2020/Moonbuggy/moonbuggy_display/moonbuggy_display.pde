import processing.serial.*;
Serial myPort;

String ver = "1.4.2";

float cs = 1;
color carCol = color(240);

PGraphics disp;

PFont font;
String[] imageF = {"code", "nasa", "moonbuggy"};
PImage[] images;

boolean demo = true;

float mph = 0.0;
float hei = 0.0;
float rol = 0.0;
float pit = 0.0;
float heartRate = 100;

float pCh = 0.0;

color[] cols = {color(235, 50, 10), color(50, 235, 10), color(0, 20, 235)};
int co = 0;

void setup() {
  // Load Images
  images = new PImage[imageF.length];
  for (int a = 0; a < imageF.length; a++) {
    images[a] = loadImage(imageF[a]+".png");
  }
  
  //size(900, 900, P3D);
  fullScreen(P3D);
  disp = createGraphics(900, 900, P3D);
  surface.setResizable(true);
  
  disp.beginDraw();
  disp.textAlign(LEFT, TOP);
  font = loadFont("CourierNewPS-BoldMT-60.vlw");
  disp.textFont(font, 50);
  disp.endDraw();
  
  textFont(font, 50);
  noCursor();
  
  background(0);
  
  //myPort = new Serial(this, Serial.list()[0], 9600);
}

float n(float x) {
  float ret =  noise(x/100) + noise((x+2)/50);
  return map(ret, 0, 2, -PI/5, PI/5);
}

float r(float i, int p) {
  float pp = pow(10, p);
  return float(round(i*pp))/pp;
}

void draw() {
  if (demo) {
    //mph = floor(lerp(mph, float(mouseX)/10, 0.2));
    mph = r(map(noise(float(frameCount+100)/80)+1, 1, 2, 20, 60), 2);
    rol = r((noise((float(frameCount)/map(mph, 0, 90, 50, 2)))-0.5)*map(mph, 0, 90, 0.1, 0.3), 2) + pCh;
    hei = r(max(0.01, lerp(hei, max(0, 35*(noise(float(frameCount)/100)-0.6)), 0.2)), 2);
    //pit = float(round(lerp(pit, map(mouseY, 0, height, -0.5, 0.5), 0.1)*100))/100;
    pit = r(n(float(frameCount)), 2);
    
    heartRate = r(map(noise(float(frameCount)/250+100), 0, 1, 100, 170), 2);
  }
  
  if (width != disp.width || height != disp.height) {
    disp = createGraphics(width, height, P3D);
    disp.beginDraw();
    disp.textAlign(LEFT, TOP);
    disp.textFont(font, 50);
    disp.endDraw();
  }
  
  // Car size for when window resizes
  cs = ((width+height)-(900*2))/min(width, height);
  cs += 1;
  
  // Background lines
  background(0);
  stroke(255);
  strokeWeight(3);
  for (int a = int(width*0.2); a < width; a+= 30) {
    for (int b = 0; b < height; b+= 20) {
      float o = map(dist(a, b, width/2, height/2), 0, width*0.4, 255, 0);
      int p = 20;
      // Red
      stroke(o, 0, 0, 130);
      beginShape(LINES);
      vertex(-1+a+noise(float(b)/20, float(a)/10)*15, b, -1);
      vertex(-1+a+noise(float(b+p)/20, float(a)/10)*15, b+p, -1);
      endShape();
      
      // Blue
      stroke(0, 0, o, 130);
      beginShape(LINES);
      vertex(1+a+noise(float(b)/20, float(a)/10)*15, b, -1);
      vertex(1+a+noise(float(b+p)/20, float(a)/10)*15, b+p, -1);
      endShape();
      
      // Green
      stroke(0, o, 0, 100);
      beginShape(LINES);
      vertex(a+noise(float(b)/20, float(a)/10)*15, b, -1);
      vertex(a+noise(float(b+p)/20, float(a)/10)*15, b+p, -1);
      endShape();
    }
  }
  
  // Begin drawing on separate display
  disp.beginDraw();
  disp.clear();
  
  // GUI Stuff
  disp.stroke(255);
  disp.textSize(20*cs);
  
  // Left text
  int y = -1;
  disp.textAlign(LEFT, TOP);
  y++; disp.text("MoonBuggy disp v"+ver, 5*cs, (5+(y*20))*cs);
  y++; disp.text("Height: "+hei, 5*cs, (5+(y*20))*cs);
  y++; disp.text("Roll: "+rol, 5*cs, (5+(y*20))*cs);
  y++; disp.text("Pitch: "+pit, 5*cs, (5+(y*20))*cs);
  y++; disp.text("Heart rate: "+heartRate, 5*cs, (5+(y*20))*cs);
  
  // Right text
  /*y = -1;
  disp.textAlign(RIGHT, TOP);
  y++; disp.text("MoonBuggy disp v"+ver, width-5*cs, (5+(y*20))*cs);
  y++; disp.text("Height: "+hei, width-5*cs, (5+(y*20))*cs);
  y++; disp.text("Roll: "+rol, width-5*cs, (5+(y*20))*cs);
  y++; disp.text("Pitch: "+pit, width-5*cs, (5+(y*20))*cs);*/
  
  // Shift everything to the center for C A R
  disp.translate(width/2, height/2, 0);
    
  // Light
  disp.pointLight(red(cols[co]), blue(cols[co]), green(cols[co]), 0, -200, 400);
  disp.ambientLight(50, 50, 50);
  
  // Fancy Rotations
  disp.rotateX(PI/3);
  disp.rotateZ((-PI/4) + ((float(frameCount)/200) + sin(float(frameCount)/400)));
  disp.rotateY(rol);
  disp.rotateX(pit);
  
  // Car
  disp.noStroke();
  disp.fill(carCol);
  disp.translate(0, 0, hei);
  disp.box(150*cs, 200*cs, 50*cs);
  disp.translate(0, 0, -hei);
  
  disp.endDraw();
  
  image(disp, 0, 0);
  
  textAlign(CENTER, BOTTOM);
  textSize(20*cs);
  text(str(mph)+" mph", (width/2)+(200*cs), height/2);
  
  float m = width/25;
  for (int a = 0; a < images.length; a++) {
    println(a);
    image(images[a], width-m*(a+1), height-m, m, m);
  }
  
  if (mousePressed && frameCount % 3 == 0) {
    co ++;
    if (co >= 3) {
      co = 0;
    }
  }
}

void mousePressed() {
  
  /*if (pCh == 0) {
    pCh = 1;
  } else if (pCh == 1) {
    pCh = -1;
  } else {
    pCh = 0;
  }*/
}
