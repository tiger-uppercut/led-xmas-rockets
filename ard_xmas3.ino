#include <FastLED.h>

#define LED_PIN     8
#define NUM_LEDS    300

CRGB leds[NUM_LEDS];
CRGB Black = CRGB(0, 0, 0);
CRGB Star = CRGB(1, 1, 1);

float Brightness = 0.13;
const float BaseSpeed = 0.36;

// sprite data need to be adapted if you change these
const int SpriteAmount = 4;
const int RocketAmount = 8;
const int RocketSegmentAmount = 8;
const int ColorChannelAmount = 3;

// initial rocket positions
float SignalPosition[RocketAmount] = {0.2, 37.2, 75.2, 112.2, 150.2, 187.2, 225.2, 262.2};

// rocket animation sprites in RGB, RGB, etc. each line is one rocket type, there are four animation frames for boosting
int Sprites[SpriteAmount][RocketAmount][RocketSegmentAmount][ColorChannelAmount] = {
        // normal
        50, 0, 0, 100, 40, 0, 200, 80, 0, 240, 200, 0, 255, 255, 200, 255, 255, 200, 255, 255, 200, 255, 0, 0,
        50, 0, 0, 100, 40, 0, 200, 80, 0, 240, 200, 0, 255, 255, 200, 255, 255, 200, 255, 255, 200, 0, 255, 0,
        50, 0, 0, 100, 40, 0, 200, 80, 0, 240, 200, 0, 255, 255, 200, 255, 255, 200, 255, 255, 200, 255, 255, 0,
        50, 0, 0, 100, 40, 0, 200, 80, 0, 240, 200, 0, 255, 255, 200, 255, 255, 200, 255, 255, 200, 0, 255, 255,
        50, 0, 0, 100, 40, 0, 200, 80, 0, 240, 200, 0, 255, 255, 200, 255, 255, 200, 255, 255, 200, 255, 0, 255,
        50, 0, 0, 100, 40, 0, 200, 80, 0, 240, 200, 0, 255, 255, 200, 255, 255, 200, 255, 255, 200, 255, 0, 0,
        50, 0, 0, 100, 40, 0, 200, 80, 0, 240, 200, 0, 255, 255, 200, 255, 255, 200, 255, 255, 200, 0, 255, 0,
        50, 0, 0, 100, 40, 0, 200, 80, 0, 240, 200, 0, 255, 255, 200, 255, 255, 200, 255, 255, 200, 0, 0, 255,
        // boost1
        100, 50, 50, 150, 90, 50, 250, 130, 50, 255, 250, 50, 255, 255, 200, 255, 255, 200, 255, 255, 200, 255, 0, 0,
        100, 50, 50, 150, 90, 50, 250, 130, 50, 255, 250, 50, 255, 255, 200, 255, 255, 200, 255, 255, 200, 0, 255, 0,
        100, 50, 50, 150, 90, 50, 250, 130, 50, 255, 250, 50, 255, 255, 200, 255, 255, 200, 255, 255, 200, 255, 255, 0,
        100, 50, 50, 150, 90, 50, 250, 130, 50, 255, 250, 50, 255, 255, 200, 255, 255, 200, 255, 255, 200, 0, 255, 255,
        100, 50, 50, 150, 90, 50, 250, 130, 50, 255, 250, 50, 255, 255, 200, 255, 255, 200, 255, 255, 200, 255, 0, 255,
        100, 50, 50, 150, 90, 50, 250, 130, 50, 255, 250, 50, 255, 255, 200, 255, 255, 200, 255, 255, 200, 255, 0, 0,
        100, 50, 50, 150, 90, 50, 250, 130, 50, 255, 250, 50, 255, 255, 200, 255, 255, 200, 255, 255, 200, 0, 255, 0,
        100, 50, 50, 150, 90, 50, 250, 130, 50, 255, 250, 50, 255, 255, 200, 255, 255, 200, 255, 255, 200, 0, 0, 255,
        // boost2
        150, 100, 100, 200, 240, 100, 255, 180, 100, 255, 255, 100, 255, 255, 200, 255, 255, 200, 255, 255, 200, 255, 0, 0,
        150, 100, 100, 200, 240, 100, 255, 180, 100, 255, 255, 100, 255, 255, 200, 255, 255, 200, 255, 255, 200, 0, 255, 0,
        150, 100, 100, 200, 240, 100, 255, 180, 100, 255, 255, 100, 255, 255, 200, 255, 255, 200, 255, 255, 200, 255, 255, 0,
        150, 100, 100, 200, 240, 100, 255, 180, 100, 255, 255, 100, 255, 255, 200, 255, 255, 200, 255, 255, 200, 0, 255, 255,
        150, 100, 100, 200, 240, 100, 255, 180, 100, 255, 255, 100, 255, 255, 200, 255, 255, 200, 255, 255, 200, 255, 0, 255,
        150, 100, 100, 200, 240, 100, 255, 180, 100, 255, 255, 100, 255, 255, 200, 255, 255, 200, 255, 255, 200, 255, 0, 0,
        150, 100, 100, 200, 240, 100, 255, 180, 100, 255, 255, 100, 255, 255, 200, 255, 255, 200, 255, 255, 200, 0, 255, 0,
        150, 100, 100, 200, 240, 100, 255, 180, 100, 255, 255, 100, 255, 255, 200, 255, 255, 200, 255, 255, 200, 0, 0, 255,
        // boost3
        200, 150, 150, 250, 190, 150, 255, 230, 150, 255, 255, 150, 255, 255, 200, 255, 255, 200, 255, 255, 200, 255, 0, 0,
        200, 150, 150, 250, 190, 150, 255, 230, 150, 255, 255, 150, 255, 255, 200, 255, 255, 200, 255, 255, 200, 0, 255, 0,
        200, 150, 150, 250, 190, 150, 255, 230, 150, 255, 255, 150, 255, 255, 200, 255, 255, 200, 255, 255, 200, 255, 255, 0,
        200, 150, 150, 250, 190, 150, 255, 230, 150, 255, 255, 150, 255, 255, 200, 255, 255, 200, 255, 255, 200, 0, 255, 255,
        200, 150, 150, 250, 190, 150, 255, 230, 150, 255, 255, 150, 255, 255, 200, 255, 255, 200, 255, 255, 200, 255, 0, 255,
        200, 150, 150, 250, 190, 150, 255, 230, 150, 255, 255, 150, 255, 255, 200, 255, 255, 200, 255, 255, 200, 255, 0, 0,
        200, 150, 150, 250, 190, 150, 255, 230, 150, 255, 255, 150, 255, 255, 200, 255, 255, 200, 255, 255, 200, 0, 255, 0,
        200, 150, 150, 250, 190, 150, 255, 230, 150, 255, 255, 150, 255, 255, 200, 255, 255, 200, 255, 255, 200, 0, 0, 255,
};

// variables declared here for performance reasons
float Overlap;
float SignalStart;
int LedStart;
int LedEnd;
float SignalEnd;
int SignalNr;
int RocketNr;
int RocketBoost[] = {0, 0, 0, 0, 0, 0, 0, 0};
float RocketSpeedGain[] = {0, 0, 0, 0, 0, 0, 0, 0};
int Rando;

void setup() {
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {

    // turn all LED black
    for (LedStart = 0; LedStart < NUM_LEDS; LedStart++) {
        leds[LedStart] = Black;
    }

    // display random stars
    for (Rando = 0; Rando < 6; Rando++) {
        leds[random(0, NUM_LEDS)] = Star;
    }

    // draw racing rockets
    for (RocketNr = 0; RocketNr < RocketAmount; RocketNr++) {

        // randomly a rocket gains a boost
        // -- showing a different animation sprite
        if (RocketBoost[RocketNr] > 0) {
            RocketBoost[RocketNr]--;
        }

        // -- and gaining speed, which it will loose over time
        if (RocketSpeedGain[RocketNr] > 0) {
            RocketSpeedGain[RocketNr] = constrain(RocketSpeedGain[RocketNr] - (BaseSpeed / 10), 0, 9999);
        }

        if (random(1, 30) == 1) {
            RocketBoost[RocketNr] = 3;
            RocketSpeedGain[RocketNr] = BaseSpeed * 2;
        }

        // apply speed
        SignalPosition[RocketNr] = AdvancePosition(SignalPosition[RocketNr], BaseSpeed + RocketSpeedGain[RocketNr]);

        // check the LEDs on the rocket position
        for (LedStart = SignalPosition[RocketNr]; LedStart < SignalPosition[RocketNr] + RocketSegmentAmount + 1; LedStart++) {

            // and apply each color of the according animation sprite to the LED
            for (SignalNr = 0; SignalNr < RocketSegmentAmount; SignalNr++) {
                SignalStart = AdvancePosition(SignalPosition[RocketNr], SignalNr);
                LedEnd = LedStart + 1;
                SignalEnd = SignalStart + 1;

                // if the LED is not in range, skip it
                if (SignalEnd < LedStart || SignalStart > LedEnd) {
                    continue;
                }

                // subpixel animation

                // -- case A: the signal has crossed into the position of the LED
                if (SignalEnd >= LedStart && SignalEnd <= LedEnd) {
                    Overlap = SignalEnd - LedStart;
                    leds[LedStart] = CRGB(
                            // BrightnessBefore + (InputBrightness * OverlapAmount * SystemBrightness)
                            constrain(leds[LedStart][0] + (Sprites[RocketBoost[RocketNr]][RocketNr][SignalNr][0] * Overlap * Brightness), 0, 255),
                            constrain(leds[LedStart][1] + (Sprites[RocketBoost[RocketNr]][RocketNr][SignalNr][1] * Overlap * Brightness), 0, 255),
                            constrain(leds[LedStart][2] + (Sprites[RocketBoost[RocketNr]][RocketNr][SignalNr][2] * Overlap * Brightness), 0, 255)
                    );
                }

                // -- case B: the signal is moving out of the position of the LED
                if (SignalStart > LedStart && SignalStart < LedEnd) {
                    Overlap = LedEnd - SignalStart;
                    leds[LedStart] = CRGB(
                            // BrightnessBefore + (InputBrightness * OverlapAmount * SystemBrightness)
                            constrain(leds[LedStart][0] + (Sprites[RocketBoost[RocketNr]][RocketNr][SignalNr][0] * Overlap * Brightness), 0, 255),
                            constrain(leds[LedStart][1] + (Sprites[RocketBoost[RocketNr]][RocketNr][SignalNr][1] * Overlap * Brightness), 0, 255),
                            constrain(leds[LedStart][2] + (Sprites[RocketBoost[RocketNr]][RocketNr][SignalNr][2] * Overlap * Brightness), 0, 255)
                    );
                }
            }
        }
    }

    // render frame
    FastLED.show();

    // there was no need to delay frames for a 300 LED strip on the Mega2560 board, adjust if animation is running too fast
    // delay(10);
}

// used to loop the coordinates around
float AdvancePosition(float Position, float Speed) {
    Position += Speed;

    if (Position > 300) {
        Position -= 300;
    }

    return Position;
}
