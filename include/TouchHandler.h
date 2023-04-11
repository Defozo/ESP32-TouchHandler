#ifndef TouchHandler_h
#define TouchHandler_h

#include <Arduino.h>

class TouchHandler {
public:
  TouchHandler(const int* touchPins, int numPins, int samplePeriod = 10, int initPeriod = 5000, int filterPeriod = 10000, float sensitivity = 0.5, float factor = 12.0, float offset = 40.0);
  void begin();
  bool isTouched(int index);
  int getTouchValue(int index);
  float getThreshold(int index);
  void update();
  void setNumInitSamples(int numInitSamples);
  int getNumInitSamples() const;

  // Getter and setter functions
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
