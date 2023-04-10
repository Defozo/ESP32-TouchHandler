#ifndef TouchHandler_h
#define TouchHandler_h

#include <Arduino.h>

class TouchHandler {
public:
  TouchHandler(const int* touchPins, int numPins, int samplePeriod = 10, int initPeriod = 5000, int filterPeriod = 10000, float factor = 6.0, float offset = 20.0);
  void begin();
  bool isTouched(int index);
  int getTouchValue(int index);
  float getThreshold(int index);
  void update();

private:
  const int* _touchPins;
  int _numPins;
  int _samplePeriod;
  int _initPeriod;
  int _filterPeriod;
  float _factor;
  float _offset;
  float* _medians;
  float* _touchStdDevs;
  uint32_t _start_time;
  float* _epsilon_m;
  float* _epsilon_s;
};

#endif
