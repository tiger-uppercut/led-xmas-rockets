# led-xmas-rockets
Arduino LED animation for a 300 LED strip

The animation depicts racing rocket ships of different teams to a starry backdrop.

- Smooth subpixel animation, usually limited a bit by the LED minimum brightness
- Built for a Mega2560 board, may work on others
- Built for a WS2812B LED strip, may work on others 
- Led Strip is attached to Pin Digital 8 
- Performance seems to be mainly limited by the code, not by the FastLED library, as the NeoPixel library yielded the same speed
- You may need to add a delay at the end of the loop if it runs too fast on your setup
