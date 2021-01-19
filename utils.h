#ifndef UTILS_H
#define UTILS_H

unsigned long GTRandom() {
  return millis();
}

int GTRandom(int mini, int maxi) {
  return (GTRandom() % (mini, maxi)) + mini;
}

#endif
