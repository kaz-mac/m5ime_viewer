/* 
  m5ime_jpon.ino
  M5Stack ATOM MatrixでPCのIMEの状態をLEDで表示するやつ
  シャポコさんのImeTo232C使用を想定 https://github.com/shapoco/ImeTo232C

  Copyright (c) 2024 Kaz  (https://akibabara.com/blog/)
  Released under the MIT license.
  see https://opensource.org/licenses/MIT

  ImeTo232C側の設定
    状態     DTR  RTS  点滅
    IME OFF  [ ]  [ ]  1回
    IME ON   [ ]  [X]  なし
  どうしてかはわかないが点滅1回にすると動く

  TODO:
    ESPNOWを使って子機を追加できるようにしたい
    発光パターンを選べるようにしたい（たぶんすぐ飽きるから落ち着いた発光パターンもあるとよい）
    ATOM Lite + RGB LEDテープライトを使いたい
    IMEの状態に応じてサーボを動かしたい
*/
#include <M5Unified.h>

// RGB LED関連
#include <FastLED.h>
const size_t LED_NUM = 25;
CRGB leds[LED_NUM];

// 設定 GPIOポート
#define GPIO_M5LED 27
#define GPIO_RTS    0

// LEDの光らせ方
const uint8_t GAMING_SPEED = 600;   // スピード
const uint8_t DELTA_HUE = 3;        // 色の密度(?)
const uint8_t IME_ON_BRIGHT = 128;  // IMEがONのときの明るさ max 255
const uint8_t IME_OFF_BRIGHT = 10;  // IMEがOFFのときの明るさ max 255
const CRGB IME_OFF_COLOR = CRGB::Blue;  // IMEがOFFのときの色

// 初期化
void setup() {
  M5.begin();
  Serial.begin(115200);
  delay(200);

  // GPIO設定
  pinMode(GPIO_RTS, INPUT);

  // FastLEDの設定
  FastLED.addLeds<WS2811, GPIO_M5LED, GRB>(leds, LED_NUM);
  FastLED.setBrightness(128);
}

// ループ
void loop() {
  static float brightness = 1.0;
  M5.update();

  // ボタンで明るさ変更
  if (M5.BtnA.wasPressed()) {
    brightness -= 0.2;
    if (brightness < 0) brightness = 1.0;
  }

  // IMEの状態によってLEDの点灯パターンを変える
  if (digitalRead(GPIO_RTS) == LOW) {
    // IMEがON
    uint8_t hue = beat8(GAMING_SPEED,255); 
    fill_rainbow(leds, LED_NUM, hue, DELTA_HUE);            
    FastLED.setBrightness(IME_ON_BRIGHT * brightness);
    FastLED.show();
  } else {
    // IMEがOFF
    FastLED.setBrightness(IME_OFF_BRIGHT * brightness);
    fill_solid(leds, LED_NUM, IME_OFF_COLOR);
    FastLED.show();
  }
  delay(10);
}
