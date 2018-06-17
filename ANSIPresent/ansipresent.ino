#include <AnsiStream.h>
#include <math.h>
#include <stdlib.h>
#include <SoftwareSerial.h>

#define slideTotal 30 // highest slide + 1
#define height 25
#define width 87


void (*functionPtrs[slideTotal])(); //the array of function pointers
int slideCount = 0;

using namespace ANSI;

SoftwareSerial remoteSerial(11, 10); // RX, TX

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // debug led
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), showSlide, FALLING); // emergency next button
  attachInterrupt(digitalPinToInterrupt(3), showSlide, FALLING); // emergency back button

  Serial.begin(115200);
  remoteSerial.begin(2400);
  while (!Serial);

  // Boot screen, you know old style
  Serial << "booting";
  delay(100);
  clear();
  Serial << setForegroundColor(RED) << "A" << setForegroundColor(GREEN) << "N" << setForegroundColor(BLUE) << "S" << setForegroundColor(MAGENTA) << "I" << setForegroundColor(WHITE) << setBackgroundColor(BLACK) << "Present";
  hideCursor();

  // load in slides + wait for boot screen to be seen by the world
  loadSlides();
  delay(2000);

  // show slide 0
  showSlide();
}

void loop() {

  //clear();
  //slide15();
  //delay(4000);
  //return;

  // test code
  //delay(5000);
  //showSlide();
  //return;


  digitalWrite(LED_BUILTIN, HIGH);
  String c = remoteSerial.readStringUntil('\n');
  digitalWrite(LED_BUILTIN, LOW);

  if (c.indexOf("forward") > -1) {
    showSlide();
  }
  if (c.indexOf("back") > -1) {
    goBackSlide();
  }
}

void showSlide() {
  clear();
  (*functionPtrs[slideCount])();
  hideCursor();
  slideCount++;
  if (slideCount == slideTotal) {
    slideCount = 0;
  }
}

void goBackSlide() {
  if (slideCount == 0) {
    slideCount = slideTotal - 2;
  }
  slideCount -= 2;
  if (slideCount < 0) {
    slideCount = 0;
  }
  showSlide();
}

void clear() {
  Serial << eraseScreen();
  Serial << home();
  Serial << defaultBackground() << defaultForeground();
  Serial << xy(0, 0);

  // delete me to have default cursor set to top
  Serial << down(1);
}

void hideCursor() {
  Serial << xy(1000, 1000);
}

void centerLine(int len) {
  int ident = width / 2 - ( len / 2 );
  Serial << forward(ident);
}

void centerScreen() {
  Serial << xy(0, 0);
  Serial << down(height / 2);
}

void typewriteText(String text, int d) {
  for (int i = 0; i < text.length(); i++) {
    Serial << text[i];
    delay(d);
  }
}

void drawCircle(int cx, int cy, int radius, char fill)
{
  for (int y = -radius; y < radius; y++) {
    int half_row_width = sqrt(radius * radius - y * y);
    for (int x = -half_row_width; x < half_row_width; x++)
      Serial << xy(cx + x * 2, cy + y) << fill;
  }

}

void drawRect(int x1, int x2, int y1, int y2, char fill)
{
  for (int x = x1; x <= x2; x++) {
    for (int y = y1; y <= y2; y++) {
      Serial << xy(x, y) << fill;
    }
  }
  Serial << home();
}

void drawLine(int x1, int y1, int x2, int y2, char fill) {
  // y =  (yB - yA) /(xB - xA) * (x-xA) +xA
  for (int x = x1; x <= x2; x++) {
    for (int y = y1; y <= y2; y++) {
      if (y == ((y2 - y1) / (x2 - x1) * (x - x1) + y1)) {
        Serial << xy(x, y) << fill;
      }
    }
  }
  Serial << home();
}

void gopher() {
  Serial << down(height - 12);
  Serial << forward(50) << F("         ,_---~~~~~----._         ") << endl;
  Serial << forward(50) << F("  _,,_,*^____      _____``*g*\"*, ") << endl;
  Serial << forward(50) << F(" / __/ /'     ^.  /      \\ ^@q   f ") << endl;
  Serial << forward(50) << F("[  @f | @))    |  | @))   l  0 _/  ") << endl;
  Serial << forward(50) << F(" \\`/   \\~____ / __ \\_____/    \\   ") << endl;
  Serial << forward(50) << F("  |           _l__l_           I   ") << endl;
  Serial << forward(50) << F("  }          [______]           I  ") << endl;
  Serial << forward(50) << F("  ]            | | |            |  ") << endl;
  Serial << forward(50) << F("  ]             ~ ~             |  ") << endl;
  Serial << forward(50) << F("  |                            |   ") << endl;
  Serial << forward(50) << F("   |                           |   ") << endl;
  Serial << home();
}

// Slides
void loadSlides() {
  functionPtrs[0] = slide0;
  functionPtrs[1] = slide1;
  functionPtrs[2] = slide2;
  functionPtrs[3] = slide3;
  functionPtrs[4] = slide4;
  functionPtrs[5] = slide5;
  functionPtrs[6] = slide6;
  functionPtrs[7] = slide7;
  functionPtrs[8] = slide8;
  functionPtrs[9] = slide9;
  functionPtrs[10] = slide10;
  functionPtrs[11] = slide11;
  functionPtrs[12] = slide12;
  functionPtrs[13] = slide13;
  functionPtrs[14] = slide14;
  functionPtrs[15] = slide15;
  functionPtrs[16] = slide16;
  functionPtrs[17] = slide17;
  functionPtrs[18] = slide18;
  functionPtrs[19] = slide19;
  functionPtrs[20] = slide20;
  functionPtrs[21] = slide21;
  functionPtrs[22] = slide22;
  functionPtrs[23] = slide23;
  functionPtrs[24] = slide24;
  functionPtrs[25] = slide25;
  functionPtrs[26] = slide26;
  functionPtrs[27] = slide27;
  functionPtrs[28] = slide28;
  functionPtrs[29] = slide29;
}

void slide0() {
  centerScreen();
  centerLine(15);
  Serial << boldOn() << "Maartje Eyskens" << boldOff() << endl;
  centerLine(9);
  Serial << "Portfolio";
}

void slide1() {
  centerLine(17);
  Serial << boldOn() << "Mijn Competenties" << boldOff() << endl;
  drawCircle(width / 2, height / 2, 10, 'X');
  drawCircle(width / 2, height / 2, 9, ' ');

  drawCircle(width / 2, height / 2, 7, 'X');
  drawCircle(width / 2, height / 2, 6, ' ');

  drawCircle(width / 2, height / 2, 3, 'X');
  drawCircle(width / 2, height / 2, 2, ' ');
}

void slide2() {
  String txt = "Wacht... dit is geen powerpoint...";
  centerScreen();
  centerLine(txt.length());
  typewriteText(txt, 50);
}

void slide3() {
  centerLine(11);
  Serial << setForegroundColor(RED) << "A" << setForegroundColor(GREEN) << "N" << setForegroundColor(BLUE) << "S" << setForegroundColor(MAGENTA) << "I" << setForegroundColor(WHITE) << setBackgroundColor(BLACK) << "Present" << endl;
  Serial << defaultBackground() << defaultForeground();
  centerLine(16);
  Serial << underlineOn() << "\"8-bit powerpoint\"" << underlineOff();

}


void slide4() {
  centerLine(11);
  Serial << setForegroundColor(RED) << "A" << setForegroundColor(GREEN) << "N" << setForegroundColor(BLUE) << "S" << setForegroundColor(MAGENTA) << "I" << setForegroundColor(WHITE) << setBackgroundColor(BLACK) << "Present" << endl;
  Serial << defaultBackground() << defaultForeground();
  centerLine(16);
  Serial << underlineOn() << "\"8-bit powerpoint\"" << underlineOff();

  Serial << xy(0, 10);
  Serial << F(" > 8-bit") << endl;
  Serial << F(" > VT100 Emulatie") << endl;
  Serial << F(" > 100% C++") << endl;
  Serial << F(" > Low End Hardware") << endl;
  Serial << F(" > Speciaal voor deze presentatie") << endl;
}

void slide5() {
  centerLine(11);
  Serial << setForegroundColor(RED) << "A" << setForegroundColor(GREEN) << "N" << setForegroundColor(BLUE) << "S" << setForegroundColor(MAGENTA) << "I" << setForegroundColor(WHITE) << setBackgroundColor(BLACK) << "Present" << endl;
  Serial << defaultBackground() << defaultForeground();
  centerLine(16);
  Serial << underlineOn() << "\"8-bit powerpoint\"" << underlineOff();

  Serial << xy(0, 10);
  Serial << F(" > ATMEGA328P") << endl;
  Serial << F("   >> 8-bit CPU") << endl;
  Serial << F("   >> 16 MHz RISC-based CPU") << endl;
  Serial << F("   >> 2 KB SRAM") << endl;

  Serial << F(" > Afstandsbediening over 433MHz") << endl;

  Serial << F(" > Beeld over Seriele Verbinding") << endl;
  Serial << F("   >> 115200 baud") << endl;
  Serial << F("   >> ANSI karakterset") << endl;
  Serial << F(" > Open source: https://github.com/meyskens/ANSIPresent") << endl;

}

void slide6() {
  centerLine(11);
  Serial << setForegroundColor(RED) << "A" << setForegroundColor(GREEN) << "N" << setForegroundColor(BLUE) << "S" << setForegroundColor(MAGENTA) << "I" << setForegroundColor(WHITE) << setBackgroundColor(BLACK) << "Present" << endl;
  Serial << defaultBackground() << defaultForeground();

  centerScreen();
  centerLine(11);
  Serial << "Maar " << boldOn() << "waarom?" << boldOff() << endl;
}

void slide7() {
  centerScreen();

  centerLine(15);
  Serial << "Project " << underlineOn() << "Keulen" << underlineOff() << endl;
}

void slide8() {
  centerScreen();
  centerLine(15);
  Serial << F("Project ") << endl;
  centerLine(15);
  Serial << forward(8) << "Cooling Monitoring Using SigFox";
}

void slide9() {
  centerLine(30);
  Serial << F("Cooling Monitoring Using SigFox") << endl;

  Serial << xy(0, 10);
  Serial << F(" > In samenwerking met TH Köln") << endl;
  Serial << F(" > Complete oplossing") << endl;
  Serial << F(" > Comminucatie over SigFox") << endl;
}

void slide10() {
  centerLine(30);
  Serial << F("Cooling Monitoring Using SigFox") << endl;
  centerScreen();
  centerLine(70);
  Serial << "Koelkast --(mesh)--> Central Unit --(SigFox)--> AppEngine --> BigQuery";
}

void slide11() {
  centerLine(30);
  Serial << F("Cooling Monitoring Using SigFox") << endl;

  drawRect(5, 7, 6, 8, 'K');
  drawRect(5, 7, 15, 17, 'K');
  drawRect(11, 13, 11, 13, 'K');

  drawRect(24, 26, 11, 13, 'C');

  drawLine(14, 12, 23, 12, '-');
  drawRect(6, 6, 9, 14, '|');
  drawLine(7, 12, 10, 12, '-');

  Serial << xy(10, 20) << "SimpleMesh";
}

void slide12() {
  centerLine(9);
  Serial << F("SimpleMesh") << endl;

  Serial << xy(0, 10);
  Serial << F(" > Sequence numbers + addresses") << endl;
  Serial << F(" > Repeat if > counter") << endl;
  Serial << F(" > “Chirping” like birds") << endl;
  Serial << F(" > Arrives everywhere") << endl;
  Serial << F(" > Encryption between nodes") << endl;
  Serial << F(" > (not very efficient for much data)") << endl;
}

void slide13() {
  // render title and simplemesh part
  slide11();

  drawCircle(55, 12, 3, 'G');
  Serial << xy(50, 20) << "Google Cloud";

  drawLine(27, 12, 48, 12, '=');
  Serial << xy(35, 20) << "SigFox";
}

void slide14() {
  gopher();
  Serial << down();
  centerLine(30);
  Serial << F("Cooling Monitoring Using SigFox") << endl;
  centerLine(7);
  Serial << F("Backend") << endl;
  Serial << xy(0, 13);
  Serial << F(" > Google AppEngine") << endl;
  Serial << F(" > Verwerkt \"verkleinde\" data") << endl;
  Serial << F(" > 100% Go") << endl;
  Serial << F(" > Dataopslag in BigQuery") << endl;
}

void slide15() {
  centerLine(17);
  Serial << F("Competentie check") << endl;
  Serial << down(4);
  Serial << F(" ~ Je onderzoekt en evalueert mogelijke oplossingen en maakt onderbouwde keuzes, zowel voor ") << underlineOn() << F("hardware als software") << underlineOff() << endl;
  Serial << F(" ~ Je ontwerpt en ontwikkelt ") << underlineOn() << F("veilige") << underlineOff() << F(" IT-oplossingen") << endl;
  Serial << F(" ~ Je maakt hierbij gebruik van standaarden, patronen en/of frameworks") << endl;
  Serial << F(" ~ Je bouwt werkende hardware- of softwaresystemen met ") << underlineOn() << F("bestaande bouwstenen") << underlineOff() << endl;
  Serial << F(" ~ Je ") << underlineOn() << F("test") << underlineOff() << F(" zowel alle deelaspecten als de integratie ervan") << endl;
  Serial << F(" ~ Je ") << underlineOn() << F("installeert, configureert, beveiligt") << underlineOff() << F(" en onderhoudt IT-oplossingen") << endl;
  Serial << F(" ~ Je communiceert mondeling en schriftelijk in het Nederlands, ") << underlineOn() << F("Engels") << underlineOff() << F(" en Frans") << endl;
  Serial << F(" ~ Je pakt opdrachten ") << underlineOn() << F("planmatig en projectmatig") << underlineOff() << F(" aan") << endl;
  Serial << F(" ~ Je werkt zowel zelfstandig als in ") << underlineOn() << F("team") << underlineOff() << F(" opdrachten en projecten uit") << endl;
  Serial << F(" ~ Je houdt hierbij rekening met de ") << underlineOn() << F("economische randvoorwaarden") << underlineOff() << endl;
  Serial << F(" ~ Je bent ") << underlineOn() << F("creatief") << underlineOff() << F(" en je neemt initiatief") << endl;
}

void slide16() {
  centerScreen();
  centerLine(39);
  Serial << "Nu we het over Google Cloud hebben...";
}

void slide17() {
  centerScreen();
  Serial << up(3);
  centerLine(54);
  Serial << F("    _____        _____              _ _               ") << endl;
  centerLine(54);
  Serial << F("   / ____|      / ____|            | | |              ") << endl;
  centerLine(54);
  Serial << F("  | |  __  ___ | |     __ _ _ __ __| | | ___  ___ ___ ") << endl;
  centerLine(54);
  Serial << F("  | | |_ |/ _ \\| |    / _` | '__/ _` | |/ _ \\/ __/ __|") << endl;
  centerLine(54);
  Serial << F("  | |__| | (_) | |___| (_| | | | (_| | |  __/\\__ \\__ \\") << endl;
  centerLine(54);
  Serial << F("   \\_____|\\___/ \\_____\\__,_|_|  \\__,_|_|\\___||___/___/") << endl;
}

void slide18() {
  centerLine(10);
  Serial << "GoCardless";

  centerScreen();
  centerLine(36);
  Serial << F("Online Payments Is A Broken Indusrty") << endl;
  delay(1000);
  centerLine(15);
  Serial << F("We're fixing it") << endl;
}

void slide19() {
  centerLine(10);
  Serial << "GoCardless";

  centerScreen();
  centerLine(30);
  Serial << F("Focus op periodieke betalingen") << endl;
  delay(1000);
  centerLine(60);
  Serial << F("Op basis van automatische incasso/domiciliëring/direct debit") << endl;
  delay(1000);
  centerLine(36);
  Serial << F("Voorheen alleen voor grote bedrijven") << endl;
}

void slide20() {
  centerLine(21);
  Serial << "The Move To The Cloud";
  centerScreen();
  centerLine(41);
  Serial << F("Softlayer      ========>     Google Cloud") << endl << endl << endl;
  centerLine(41);
  Serial << F("Bare betal                   Managed cluster") << endl;
  centerLine(41);
  Serial << F("Own orchestrator             Kubernetes") << endl;
  centerLine(41);
  Serial << F("Manual setup                 Security/reduncancy") << endl;
  centerLine(41);
  Serial << F("                              out of the box") << endl;
}

void slide21() {
  centerScreen();
  centerLine(3);
  Serial << underlineOn() << F("ANU") << underlineOff() << endl;
  delay(1000);
  centerLine(34);
  Serial << F("Earliest attested Sky Father deity") << endl;
  delay(1000);
  centerLine(53);
  Serial << "Or as we have it in GC, the thing that starts it all.";
}

void slide22() {
  centerLine(3);
  Serial << underlineOn() << F("ANU") << underlineOff() << endl;
  centerLine(34);
  Serial << F("Earliest attested Sky Father deity") << endl;

  Serial << xy(0, 13);
  Serial << F(" > Monorepo voor alle infrastructuur") << endl;
  Serial << F(" > CLI voor developers en platform team") << endl;
  Serial << F(" > Kubernetes + Helm deploy flow") << endl;
  Serial << " > Chef cookbooks voor PostgreSQL";
}

void slide23() {
  centerLine(3);
  Serial << underlineOn() << F("ANU") << underlineOff() << endl;
  centerLine(11);
  Serial << F("Deploy Flow") << endl;

  centerScreen();
  Serial << F("ANU CLI ==> GitHub ==> Buildkite    ==> Helm ==> Kubernetes") << endl;
  Serial << F("                   ==> Buildkite SL ==> Conductor (app01, app02, app03)") << endl;
  Serial << F("                       \\-- Slack") << endl;
}

void slide24() {
  typewriteText(F("http https://api-staging.gocardless.com/health_check"), 50);
  Serial << endl;
  delay(500);
  Serial << endl;
  Serial << F("HTTP/1.1 ") << setForegroundColor(GREEN) << "200 OK" << defaultForeground() << endl;
  delay(200);
  Serial << F("Server: cloudflare") << endl;
  Serial << F("Via: 1.1 google") << endl;
  Serial << endl;
  delay(200);
  Serial << F("{\"active_record\":\"up\",\"system\":\"up\"}");
}

void slide25() {
  centerLine(17);
  Serial << F("Competentie check") << endl;
  centerScreen();
  Serial << up(2);
  Serial << F(" ~ Start with why") << endl;
  Serial << F(" ~ Take Pride") << endl;
  Serial << F(" ~ Act with integrity") << endl;
  Serial << F(" ~ Be humble") << endl;
}

void slide26() {
  centerScreen();
  centerLine(7);
  Serial << F("Oeps...");
}

void slide27() {
  centerLine(17);
  Serial << F("Competentie check") << endl;
  Serial << down(4);
  Serial << F(" ~ Je ontwerpt en ontwikkelt veilige IT-oplossingen met aandacht voor ") << underlineOn() << F("gemaakte afspraken") << underlineOff() << endl;
  Serial << F(" ~ Je bouwt werkende hardware- of softwaresystemen met bestaande bouwstenen") << endl;
  Serial << F(" ~ Je ") << underlineOn() << F("test") << underlineOff() << F(" zowel alle deelaspecten als de integratie ervan") << endl;
  Serial << F(" ~ Je ") << underlineOn() << F("installeert, configureert, beveiligt en onderhoudt") << underlineOff() << F(" IT-oplossingen") << endl;
  Serial << F(" ~ Je communiceert mondeling en schriftelijk in het Nederlands, ") << underlineOn() << F("Engels") << underlineOff() << F(" en Frans, rekening houdend met je doelpubliek") << endl;
  Serial << F(" ~ Je ") << underlineOn() << F("rapporteert") << underlineOff() << F(" correct en nauwkeurig over processen, systemen en producten, zowel schriftelijk als mondeling") << endl;
  Serial << F(" ~ Je ") << underlineOn() << F("neemt deel aan vergaderingen") << underlineOff() << F(" of zit deze voor") << endl;
  Serial << F(" ~ Je pakt opdrachten ") << underlineOn() << F("planmatig en projectmatig") << underlineOff() << F(" aan") << endl;
  Serial << F(" ~ Je werkt zowel ") << underlineOn() << F("zelfstandig als in team") << underlineOff() << F(" opdrachten en projecten uit") << endl;
  Serial << F(" ~ Je evalueert je eigen functioneren en ") << underlineOn() << F("je stuurt dit bij") << underlineOff() << endl;
  Serial << F(" ~ Je wil levenslang leren en roept tijdig ") << underlineOn() << F("externe deskundigheid") << underlineOff() << F(" in") << endl;
  Serial << F(" ~ Je kunt functioneren in een ") << underlineOn() << F("internationale werkomgeving") << underlineOff() << endl;
}

void slide28() {
  centerScreen();

  centerLine(7);
  Serial<<"Vragen?";
}

void slide29() {
  Serial<<setBackgroundColor(BLACK);
  Serial<<setForegroundColor(WHITE);
  drawRect(0, width, 0, height, ' ');
  Serial<<xy(0,0);
  Serial<<F("Trek de stekker uit om deze presentatie te eindigen");
  //end
}
