#include <GxEPD2_3C.h>

// ===== EDIT HERE =====
#define PIN_CS    10
#define PIN_DC     9
#define PIN_RST    8
#define PIN_BUSY   7
// Panel class: use the one that worked in your tests.
GxEPD2_3C<GxEPD2_213_Z98c, GxEPD2_213_Z98c::HEIGHT>
  display(GxEPD2_213_Z98c(PIN_CS, PIN_DC, PIN_RST, PIN_BUSY));
// GxEPD2_3C<GxEPD2_213c, GxEPD2_213c::HEIGHT>
//   display(GxEPD2_213c(PIN_CS, PIN_DC, PIN_RST, PIN_BUSY));
// =====================

#define MAXB 4000                 // enough for 250 x 122 (32 bytes x 122 rows)
uint8_t blk[MAXB];
uint8_t red[MAXB];

bool readN(uint8_t *b, int n) { return Serial.readBytes(b, n) == n; }

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(4000);
  display.init(115200);
  Serial.println("ready");
}

void loop() {
  // wait for the 0xAA 0x55 header
  if (Serial.available() < 2) return;
  if (Serial.read() != 0xAA) return;
  if (Serial.peek() != 0x55) return;
  Serial.read();

  uint8_t wh[2];
  if (!readN(wh, 2)) { Serial.println("ERR header"); return; }
  int w = wh[0], h = wh[1];
  int n = ((w + 7) / 8) * h;
  if (n == 0 || n > MAXB) { Serial.println("ERR size"); return; }

  if (!readN(blk, n) || !readN(red, n)) { Serial.println("ERR data"); return; }
  Serial.println("drawing");

  display.init(115200);           // wake the panel before every draw
  display.setRotation(1);
  Serial.print("panel ");
  Serial.print(display.width()); Serial.print("x"); Serial.println(display.height());
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.drawBitmap(0, 0, blk, w, h, GxEPD_BLACK);
    display.drawBitmap(0, 0, red, w, h, GxEPD_RED);
  } while (display.nextPage());
  display.hibernate();
  Serial.println("done");
}
