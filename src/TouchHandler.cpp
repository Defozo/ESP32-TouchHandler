#include "TouchHandler.h"

TouchHandler::TouchHandler(const int* touchPins, int numPins, int samplePeriod, int initPeriod, int filterPeriod, float factor, float offset)
  : _touchPins(touchPins), _numPins(numPins), _samplePeriod(samplePeriod), _initPeriod(initPeriod), _filterPeriod(filterPeriod), _factor(factor), _offset(offset) {
  _medians = new float[_numPins];
  _touchStdDevs = new float[_numPins];
  _epsilon_m = new float[_numPins];
  _epsilon_s = new float[_numPins];
}

void TouchHandler::begin() {
  _start_time = millis();

  // Initialize touch sensor medians and touchStdDevs
  for (int i = 0; i < _numPins; i++) {
    uint16_t initialValue = touchRead(_touchPins[i]);
    _medians[i] = initialValue;
    _touchStdDevs[i] = 0.0;

    for (int j = 0; j < 20; j++) {
      uint16_t newValue = touchRead(_touchPins[i]);
      float diff = newValue - initialValue;
      _touchStdDevs[i] += abs(diff);
      delay(_samplePeriod);
    }
    _touchStdDevs[i] /= 20;
    _epsilon_m[i] = _medians[i] * _samplePeriod / _filterPeriod;
    _epsilon_s[i] = _touchStdDevs[i] * _samplePeriod / _filterPeriod;
  }
}

bool TouchHandler::isTouched(int index) {
  if (index >= 0 && index < _numPins) {
    int newValue = touchRead(_touchPins[index]);
    float threshold = _medians[index] - _factor * _touchStdDevs[index];
    return newValue < threshold;
  }
  return false;
}

int TouchHandler::getTouchValue(int index) {
  if (index >= 0 && index < _numPins) {
    return touchRead(_touchPins[index]);
  }
  return -1;
}

float TouchHandler::getThreshold(int index) {
  if (index >= 0 && index < _numPins) {
    return _medians[index] - _factor * _touchStdDevs[index];
  }
  return -1;
}

void TouchHandler::update() {
  for (int i = 0; i < _numPins; i++) {
    uint16_t newValue = touchRead(_touchPins[i]);

    float diff = newValue - _medians[i];
    if (millis() - _start_time < _initPeriod) {
      _medians[i] += (_offset + 2 * _samplePeriod) / (float)_initPeriod * diff;
      _touchStdDevs[i] += (_offset + 2 * _samplePeriod) / (float)_initPeriod * (abs(diff) - _touchStdDevs[i]);
    } else {
      _medians[i] += (newValue > _medians[i]) ? _epsilon_m[i] : -_epsilon_m[i];
      _touchStdDevs[i] += ((diff * diff) > (_touchStdDevs[i] * _touchStdDevs[i])) ? _epsilon_s[i] : -min(_epsilon_s[i], _touchStdDevs[i]);
    }
  }
}
