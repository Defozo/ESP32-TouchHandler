# TouchHandler

TouchHandler is an Arduino library for ESP32 that provides an adaptive threshold mechanism for built-in touch sensors. It simplifies the process of detecting touch events and automatically adjusts the threshold based on environmental changes and sensor noise.

## Features

- Simple interface for working with capacitive touch sensors
- Automatic calibration of touch sensor thresholds
- No need to manually set threshold values
- Threshold values adapt over time

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
