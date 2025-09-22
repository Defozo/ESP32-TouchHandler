#ifndef TouchHandler_h
#define TouchHandler_h

#include <Arduino.h>

/// @brief Configuration object for TouchHandler.
/// @details Groups all parameters with default values to avoid long constructor signatures.
struct TouchConfig {
  static constexpr int samplePeriod = 10;      ///< Sampling period in milliseconds.
  static constexpr int initPeriod = 5000;      ///< Initialization period in milliseconds.
  static constexpr int filterPeriod = 10000;   ///< Filtering period in milliseconds.
  static constexpr float sensitivity = 0.5f;    ///< Sensitivity factor for touch detection.
  static constexpr float factor = 12.0f;        ///< Scaling factor used in threshold calculation.
  static constexpr float offset = 40.0f;        ///< Offset added to baseline for threshold detection.
  static constexpr int numInitSamples = 50;    ///< Number of samples collected during initialization.

   /// Allow constexpr construction
  constexpr TouchConfig() = default;
};

class TouchHandler {
public:
  /// @brief Construct a new TouchHandler.
  /// @param touchPins Array of pin numbers used for touch sensing.
  /// @param numPins Number of pins in the array.
  /// @param config Configuration parameters (optional, defaults will be applied).
  TouchHandler(const int* touchPins, int numPins, const TouchConfig& config = TouchConfig());

  void begin();
  bool isTouched(int index);
  int getTouchValue(int index);
  float getThreshold(int index);
  void update();

  // Getter / setter
  void setNumInitSamples(int numInitSamples);
  int getNumInitSamples() const;
  void setSensitivity(float sensitivity);
  float getSensitivity() const;
  void setSamplePeriod(int samplePeriod);
  int getSamplePeriod() const;
  void setInitPeriod(int initPeriod);
  int getInitPeriod() const;
  void setFilterPeriod(int filterPeriod);
  int getFilterPeriod() const;
  void setFactor(float factor);
  float getFactor() const;
  void setOffset(float offset);
  float getOffset() const;

private:
  const int* _touchPins;
  int _numPins;
  int _samplePeriod;
  int _initPeriod;
  int _filterPeriod;
  float _sensitivity;
  float _factor;
  float _offset;
  float* _medians;
  float* _touchStdDevs;
  uint32_t _start_time;
  float* _epsilon_m;
  float* _epsilon_s;
  int _numInitSamples;
};

#endif
