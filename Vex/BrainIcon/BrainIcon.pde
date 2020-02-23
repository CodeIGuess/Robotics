
color[] colors;

color closeColor(color col) {
  int mi = -1;
  float mv = 1000;
  for (int a = 0; a < colors.length; a++) {
    float v = colorDist(col, colors[a]);
    //int v = int(abs(red(col) - red(colors[a])) + abs(green(col) - green(colors[a])) + abs(blue(col) - blue(colors[a])));
    if (mv > v) {
      mv = v;
      mi = a;
    }
  }
  return mi;
}

float colorDist(color col, color col2) {
  return dist(red(col), green(col), blue(col), red(col2), green(col2), blue(col2));
}

void setup() {
  size(960, 480);
  PImage img = loadImage("image.jpg"); img.filter(BLUR, 0.5);
  PImage img2 = loadImage("image2.jpg"); img2.filter(BLUR, 6.5);
  PImage img3 = loadImage("image4.png");
  
  PGraphics screen = createGraphics(480, 240);
  screen.beginDraw();
  screen.background(255);
  
  if (true) {
    screen.image(img, screen.height*0.1, screen.height*0.1, screen.height*0.8, screen.height*0.8);
    screen.image(img2, screen.height*1, screen.height*0.25, screen.height*1, screen.height*0.5);
  } else {
    screen.fill(0);
    screen.text("Mechanics: Don't use the brain for non-work related purposes", 10, 20);
    screen.text("Programmers: *Use the brain for non-work related purposes*", 10, 40);
    screen.text("Mechanics: ", 10, 60);
    screen.image(img3, (screen.width/2)-(img3.width*0.2/2), 74, img3.width*0.2, img3.height*0.2);
  }
 
  
  screen.endDraw();
  
  PGraphics screenCols = createGraphics(screen.width, screen.height);
  screenCols.beginDraw();
  screenCols.image(screen, 0, 0);
  screenCols.noStroke();
  screenCols.endDraw();
  
  IntList filterColors = new IntList();
  
  for (int a = 0; a < screen.width*screen.height; a++) {
    color col = screenCols.get(a % screen.width, a / screen.width);
    float t = (red(col) + green(col) + blue(col));
    int cThresh = 550;
    if (t >= cThresh) {
      screenCols.beginDraw();
      float v = map(t, cThresh, 765, 255, 100);
      v = lerp(v, 255, map(a/screen.width, 0, screen.height, 1, 0));
      screenCols.fill(v);
      screenCols.rect(a % screen.width, a / screen.width, 1, 1);
      screenCols.endDraw();
    }
    float m = 1000;
    for (color c : filterColors) {
      m = min(m, colorDist(col, c));
    }
    if (m > 20) {
      filterColors.append(col);
    }
  }
  colors = new color[filterColors.size()];
  for (int a = 0; a < colors.length; a++) {
    colors[a] = filterColors.get(a);
  }
  println(colors.length);
  
  String[] arr = new String[screen.width*screen.height];
  
  noStroke();
  float r = width/screen.width;
  for (int x = 0; x < screen.width; x++) {
    for (int y = 0; y < screen.height; y++) {
      color col = screenCols.get(int(x), int(y));
      col = closeColor(col);
      arr[x % screen.width + (y * screen.width)] = str(col);
      fill(colors[col]);
      rect(x*r, y*r, r, r);
    }
  }
  
  String out = "vex::color cs[] = {";
  for (int a = 0; a < colors.length; a++) {
    out += "vex::color(" + int(red(colors[a])) + "," + int(green(colors[a])) + "," + int(blue(colors[a])) + "),";
  }
  out = out.substring(0, out.length()-1);
  out += "};\nint arr[] = {"+join(arr, ",")+"};\nfor (int a = 0; a < " + str(arr.length) + "; a++) {Brain.Screen.setFillColor(cs[arr[a]]);Brain.Screen.setPenColor(cs[arr[a]]);Brain.Screen.drawRectangle((a % " + screen.width + "), (a/" + screen.width + "), 1, 1);}";
  
  saveStrings("out.txt", new String[]{out});
  print(arr.length, screen.width, screen.height);
}
