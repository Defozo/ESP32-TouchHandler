[![PlatformIO Registry](https://badges.registry.platformio.org/packages/defozo/library/TouchHandler.svg)](https://registry.platformio.org/libraries/defozo/TouchHandler)

# TouchHandler

TouchHandler is an Arduino library for ESP32 that provides an adaptive threshold mechanism for built-in touch sensors. It simplifies the process of detecting touch events and automatically adjusts the threshold based on environmental changes and sensor noise.

## Features

- Simple interface for working with capacitive touch sensors
- Automatic calibration of touch sensor thresholds
- Adaptive threshold values that adjust over time
- No need to manually set threshold values
- Responsive and accurate touch detection

## Installation

### Arduino IDE

1. Download the library as a ZIP file.
2. In the Arduino IDE, navigate to Sketch > Include Library > Add .ZIP Library.
3. Select the downloaded ZIP file and click "Open" to install the library.

### PlatformIO

Open your platformio.ini file in the root directory of your project.

Under the [env:...] section corresponding to your development board, add the following line:

```
lib_deps =
    https://github.com/Defozo/ESP32-TouchHandler/
```

Save the changes to platformio.ini.

Now, when you build your project, PlatformIO will download the library from the provided repository and link it to your project.

## Usage

1. Include the `TouchHandler.h` library in your Arduino sketch.

```cpp
#include <TouchHandler.h>
```

2. Create a TouchHandler object, providing an array of touch sensor pins and the number of pins.

```cpp
const int touchPins[NUM_TOUCH_PINS] = {4, 12, 13, 14, 15, 27, 32, 33};
TouchHandler touchHandler(touchPins, NUM_TOUCH_PINS);
```

3. In the setup() function, call the begin() method on the TouchHandler object.

```cpp
void setup() {
  touchHandler.begin();
}
```

4. In the loop() function, call the update() method on the TouchHandler object to update the touch sensor values and thresholds.

```cpp
void loop() {
  touchHandler.update();
}
```

5. Use the provided methods to check if a touch sensor is touched, get the touch sensor value, and get the touch sensor threshold.

```cpp
if (touchHandler.isTouched(index)) {
  // Do something when the touch sensor is touched
}

uint16_t touchValue = touchHandler.getTouchValue(index);
float threshold = touchHandler.getThreshold(index);
```

## Adaptive Threshold Mechanism

The TouchHandler library uses an adaptive threshold mechanism to provide a more reliable way to detect touch events. The mechanism dynamically adjusts the threshold for each touch sensor based on the sensor's median and standard deviation values. This approach allows the library to account for environmental changes and sensor noise.

The adaptive threshold mechanism works as follows:

1. During the initialization phase, the library computes the initial median and standard deviation values for each touch sensor. The initialization phase lasts for a user-defined period (`init_period`).

2. After the initialization phase, the library continuously updates the median and standard deviation values for each touch sensor. The update rate is determined by the `sample_period`, `filter_period`, `epsilon_m`, and `epsilon_s` parameters.

3. The library calculates a dynamic threshold for each touch sensor by subtracting a user-defined factor (`factor`) multiplied by the standard deviation from the median.

4. A touch event is detected when the sensor's touch value falls below the calculated threshold.

This adaptive threshold mechanism allows the library to maintain a high level of accuracy and responsiveness while minimizing the impact of environmental changes and sensor noise.

## Default Parameter Values

The library has several default parameter values that have been chosen based on empirical testing and research. These values provide a good starting point for most applications, but they can be adjusted to fine-tune the touch sensor behavior according to specific use cases.

Here is an explanation of the default values:

- `samplePeriod` (10 ms): The time interval between touch sensor readings. A shorter period results in faster updates, but may increase noise.

- `initPeriod` (5000 ms): The duration of the initialization phase during which the library computes the initial median and standard deviation values for each touch sensor.

- `filterPeriod` (10000 ms): The time period over which the median and standard deviation values are updated after the initialization phase.

- `sensitivity` (0.5): A value between 0 and 1 that controls the sensitivity of touch detection. A higher value makes the touch detection more sensitive but may also increase the likelihood of false positives.

- `factor` (12.0): A multiplier applied to the standard deviation when calculating the touch threshold. A higher factor makes the touch detection less sensitive to noise but may also decrease the responsiveness.

- `offset` (40.0): A constant value subtracted from the median when calculating the touch threshold. This value helps to account for any baseline shifts in the touch sensor readings.

These default values can be changed during the initialization of the TouchHandler object or by using the provided getter and setter functions.

## Customizing the Library

The TouchHandler library provides a set of getter and setter functions that allow developers to customize the behavior of the library. These functions can be used to adjust the parameters on-the-fly, making it easy to fine-tune the touch sensor behavior for specific use cases.

Here are some examples of the available functions:

- `setSensitivity(float sensitivity)`: Set the sensitivity parameter value.
- `getSensitivity() const`: Get the current sensitivity parameter value.
- `setSamplePeriod(int samplePeriod)`: Set the sample period parameter value.
- `getSamplePeriod() const`: Get the current sample period parameter value.

These functions can be called at any time during the execution of the program, allowing developers to dynamically adjust the touch sensor behavior as needed.

For a complete list of available functions, please refer to the TouchHandler.h header file.

## Example Application

Here is an example of how to use the TouchHandler library in a simple Arduino sketch:

```cpp
#include <TouchHandler.h>

const int NUM_TOUCH_PINS = 8;
const int touchPins[NUM_TOUCH_PINS] = {4, 12, 13, 14, 15, 27, 32, 33};
TouchHandler touchHandler(touchPins, NUM_TOUCH_PINS);

void setup() {
  Serial.begin(115200);
  touchHandler.begin();
  Serial.println("TouchHandler initialized.");
  delay(2000);
}

void loop() {
  touchHandler.update();

  for (int i = 0; i < NUM_TOUCH_PINS; i++) {
    bool touched = touchHandler.isTouched(i);
    uint16_t touchValue = touchHandler.getTouchValue(i);
    float threshold = touchHandler.getThreshold(i);

    Serial.print("Touch Pin ");
    Serial.print(i);
    Serial.print(": Value=");
    Serial.print(touchValue);
    Serial.print(", Threshold=");
    Serial.print(threshold);

    if (touched) {
      Serial.print(" (Touched)");
    }

    Serial.println();
  }

  Serial.println("-------------------------------");
  delay(1000); // Adjust this value if you need more or less time to read the text via Serial Monitor
}

```

In this example, the TouchHandler object is initialized with an array of touch sensor pins and the number of pins. The `begin()` method is called in the `setup()` function to initialize the touch sensors, and the `update()` method is called in the `loop()` function to update the touch sensor values and thresholds. The `isTouched()` method is used to check if each touch sensor is touched and print a message to the serial monitor.

This example sketch will print the touch sensor values, thresholds, and touch status for each touch pin every second. You can adjust the delay at the end of the loop function if you need more or less time to read the text via the Serial Monitor.

## Troubleshooting

If you encounter any issues while using the TouchHandler library, here are some steps you can take to troubleshoot the problem:

1. **Check the wiring**: Ensure that the touch sensors are properly connected to the touch pins on the ESP32 board.

2. **Adjust the sensitivity**: If the touch detection is too sensitive or not sensitive enough, try adjusting the sensitivity parameter value using the `setSensitivity()` function. Keep in mind that higher sensitivity values may result in more false positives, while lower values may decrease responsiveness.

3. **Adjust the sample period and filter period**: If the touch detection is not stable or responsive enough, try changing the samplePeriod and filterPeriod parameter values. A shorter sample period will result in faster updates, but may increase noise. A longer filter period will smooth out the touch sensor values, but may decrease responsiveness.

4. **Adjust the factor and offset**: If the touch detection is still not working as expected, try fine-tuning the factor and offset parameter values. These parameters control the calculation of the touch threshold and can be adjusted to account for specific sensor characteristics or environmental conditions.

5. **Check for special GPIO usage**: If you are experiencing issues with the touch sensors, ensure that you are not using a special GPIO pin, such as GPIO2. On many ESP32 development boards, GPIO2 is connected to an on-board LED, which may interfere with the touch sensor functionality. If you suspect this is the issue, try using a different GPIO pin and see if the problem persists.

6. **Check for other hardware issues**: If you're still having trouble with the touch detection, there may be an issue with the touch sensors or the ESP32 board itself. Test the touch sensors and the board with other libraries or example code to rule out any hardware problems.

## Contributions and Support

The TouchHandler library is an open-source project, and we welcome contributions from the community. If you have any suggestions, bug reports, or feature requests, please feel free to submit an issue or pull request on the GitHub repository.

For general questions or support, you can also reach out to the community on forums like Stack Overflow or the [ESP32 subreddit](https://www.reddit.com/r/esp32/).

## License

The TouchHandler library is released under the MIT License. This means that you are free to use, modify, and distribute the library for any purpose, as long as you include the copyright notice and the license in any copies or substantial portions of the software.

## Disclaimer

This code and documentation have been generated using ChatGPT, a large language model based on OpenAI's GPT-4 architecture. While efforts have been made to provide accurate information and guidance, please be aware that the content may not be perfect and should be used at your own discretion.