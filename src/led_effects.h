
//////////////////////Functions/////////////////////

void brightnessNodelay() {
  for(int i = 255; i >= 0; i--) 
  {
    for(byte count = 0; count <= 3; count++) 
    {
      ledcWrite(redPin[count], i);
      ledcWrite(bluePin[count], i);
      ledcWrite(greenPin[count], i);
    }
  }
}
void brightness() {
  for (int i = 255; i >= 0; i--) 
  {
    for(byte count = 0; count <= 3; count++) 
    {
      ledcWrite(redPin[count], i);
      ledcWrite(bluePin[count], i);
      ledcWrite(greenPin[count], i);
    }
    delay(5);
  }
}

void ledOff(int clearSpeed) {
  for(byte count = 0; count <= 3; count++) 
  {
    ledcWrite(redPin[count], 0);
    ledcWrite(bluePin[count], 0);
    ledcWrite(greenPin[count], 0);
    delay(clearSpeed);
  }
}

void ledOffR(int clearSpeed) {
  for(byte count = 3; count >= 0; count--) 
  {
    ledcWrite(redPin[count], 0);
    ledcWrite(bluePin[count], 0);
    ledcWrite(greenPin[count], 0);
    delay(clearSpeed);
  }
}

void Red(int startPin, int endPin, int ledBT) {
  for (byte count = startPin; count <= endPin; count++) {
    ledcWrite(redPin[count], 255);
    ledcWrite(bluePin[count], 0);
    ledcWrite(greenPin[count], 0);
  }
}

void Pink(int startPin, int endPin, int ledBT) {
  for (byte count = startPin; count <= endPin; count++) {
    ledcWrite(redPin[count], 255);
    ledcWrite(bluePin[count], 255);
    ledcWrite(greenPin[count], 0);
    delay(ledBT);
  }
}

void Green(int startPin, int endPin, int ledBT) {
  for (byte count = startPin; count <= endPin; count++) {
    ledcWrite(greenPin[count], 255);
    ledcWrite(redPin[count], 0);
    ledcWrite(bluePin[count], 0);
    delay(ledBT);
  }
}

void Yellow(int startPin, int endPin, int ledBT) {
  for (byte count = startPin; count <= endPin; count++) {
    ledcWrite(redPin[count], 255);
    ledcWrite(greenPin[count], 255);
    ledcWrite(bluePin[count], 0);
    delay(ledBT);
  }
}

void Blue(int startPin, int endPin, int ledBT) {
  for (byte count = startPin; count <= endPin; count++) {
    ledcWrite(bluePin[count], 255);
    ledcWrite(redPin[count], 0);
    ledcWrite(greenPin[count], 0);
    delay(ledBT);
  }
}

void Cyan(int startPin, int endPin, int ledBT) {
  for (byte count = startPin; count <= endPin; count++) {
    ledcWrite(greenPin[count], 255);
    ledcWrite(bluePin[count], 255);
    ledcWrite(redPin[count], 0);
    delay(ledBT);
  }
}

void White(int startPin, int endPin, int ledBT) {
  for(byte count = startPin; count <= endPin; count++) {
    ledcWrite(redPin[count], 255);
    ledcWrite(greenPin[count], 255);
    ledcWrite(bluePin[count], 255);
    delay(ledBT);
  }
}

//////////////////////////////////////////////////////EFFECT 1
void effect_1(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    Red(0, 3, 0);
    brightness();
    ledOff(0);

    Yellow(0, 3, 0);
    brightness();
    ledOff(0);

    Green(0, 3, 0);
    brightness();
    ledOff(0);

    White(0, 3, 0);
    brightness();
    ledOff(0);

    Cyan(0, 3, 0);
    brightness();
    ledOff(0);

    Blue(0, 3, 0);
    brightness();
    ledOff(0);

    Pink(0, 3, 0);
    brightness();
    ledOff(0);
  }
}
//////////////////////////////////////////////////////effect_2
void effect_2(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 0; i <= 3; i++ ) {
      Red(0, i, 0);
      delay(50);
      ledOff(0);

      Yellow(0, i, 0);
      delay(50);
      ledOff(0);

      Green(0, i, 0);
      delay(50);
      ledOff(0);

      White(0, i, 0);
      delay(50);
      ledOff(0);

      Cyan(0, i, 0);
      delay(50);
      ledOff(0);

      Blue(0, i, 0);
      delay(50);
      ledOff(0);

      Pink(0, i, 0);
      delay(50);
      ledOff(0);
    }
  }
}
//////////////////////////////////////////////////////effect_3
void effect_3(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 0; i <= 3; i++) {
      ledcWrite(redPin[i], 255);
      delay(100);
    } ledOff(30);
    for (int i = 3; i >= 0; i--) {
      ledcWrite(redPin[i], 255);
      ledcWrite(bluePin[i], 255);
      delay(100);
    } ledOffR(30);

    for (int i = 0; i <= 3; i++) {
      ledcWrite(greenPin[i], 255);
      delay(100);
    } ledOff(30);

    for (int i = 3; i >= 0; i--) {
      ledcWrite(redPin[i], 255);
      ledcWrite(greenPin[i], 255);
      delay(100);
    } ledOffR(30);

    for (int i = 0; i <= 3; i++) {
      ledcWrite(bluePin[i], 255);
      delay(100);
    } ledOff(30);

    for (int i = 3; i >= 0; i--) {
      ledcWrite(bluePin[i], 255);
      ledcWrite(greenPin[i], 255);
      delay(100);
    } ledOffR(30);

    for (int i = 0; i <= 3; i++) {
      ledcWrite(bluePin[i], 255);
      ledcWrite(redPin[i], 255);
      ledcWrite(greenPin[i], 255);
      delay(100);
    } ledOff(30);
  }
}
//////////////////////////////////////////////////////effect_4
void effect_4(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    int count = 3;
    for (int i = 0; i < 3; i++) {
      ledOff(5);
      ledcWrite(redPin[i], 255);  // chaser 1
      ledcWrite(bluePin[count], 255); // chaser 2
      delay(10);
      count--;
    }
    count = 3;
    for (int i = 0; i < 3; i++) {
      ledOff(5);
      ledcWrite(redPin[i], 255);  // chaser 1
      ledcWrite(greenPin[i], 255);
      ledcWrite(bluePin[count], 255); // chaser 2
      delay(10);
      count--;
    }
    count = 3;
    for (int i = 0; i < 3; i++) {
      ledOff(5);
      ledcWrite(redPin[i], 255);  // chaser 1
      ledcWrite(bluePin[i], 255);
      ledcWrite(greenPin[count], 255); // chaser 2
      delay(10);
      count--;
    }
  }
}
//////////////////////////////////////////////////////effect_5
void effect_5(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    int count = 3;
    for (int i = 0; i <= 3; i++) {
      ledOff(0);
      ledcWrite(redPin[i], 255);  // chaser 1
      ledcWrite(redPin[i - 1], 255);
      brightnessNodelay();
      ledcWrite(bluePin[count], 255); // chaser 2
      ledcWrite(bluePin[count - 1], 255); // chaser 2
      count--;
      delay(100);
    }
  }
}
//////////////////////////////////////////////////////effect_6
void effect_6(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    int count = 3;
    for (int i = 0; i <= 3; i++) {
      Cyan(0, i, 0);
      Cyan(0, i - count, 0);
      brightnessNodelay();
      Pink(0, count, 0);
      Pink(0, count - i, 0);
      count--;
      delay(100);
    }
    brightnessNodelay();
    count = 3;
    for (int i = 0; i <= 3; i++) {
      Red(0, i, 0);
      Red(0, i - count, 0);
      brightnessNodelay();
      Yellow(0, count, 0);
      Yellow(0, count - i, 0);
      count--;
      delay(100);
    }
    brightnessNodelay();
    count = 3;
    for (int i = 0; i <= 3; i++) {
      Blue(0, i, 0);
      Blue(0, i - count, 0);
      brightnessNodelay();
      Green(0, count, 0);
      Green(0, count - i, 0);
      count--;
      delay(100);
    }
  }

}
//////////////////////////////////////////////////////effect_7
void effect_7(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 3; i >= 0; i--) {
      for (int k = 0; k < i; k++) {
        ledcWrite(redPin[k], 255);
        ledcWrite(greenPin[k], 255);
        delay(50);
        ledcWrite(redPin[k], 0);
        ledcWrite(greenPin[k], 0);
        delay(30);
      }
      ledcWrite(bluePin[i], 255);
      delay(20);
    }
  }
}
//////////////////////////////////////////////////////effect_8
void effect_8(int repeatEffect) {
    for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 0; i <= 3; i++) {
      ledcWrite(redPin[i], 255);
      delay(30);
      ledcWrite(redPin[i - 1], 0);
      delay(10);
    } ledOff(0);
    for (int i = 3; i >= 0; i--) {
      ledcWrite(bluePin[i], 255);
      delay(30);
      ledcWrite(bluePin[i + 1], 0);
      delay(10);
    } ledOff(0);
    for (int i = 0; i <= 3; i++) {
      ledcWrite(greenPin[i], 255);
      delay(30);
      ledcWrite(greenPin[i - 1], 0);
      delay(10);
    } ledOff(0);
    for (int i = 3; i >= 0; i--) {
      ledcWrite(bluePin[i], 255);
      ledcWrite(greenPin[i], 255);
      ledcWrite(redPin[i], 255);
      delay(30);
      ledcWrite(bluePin[i + 1], 0);
      ledcWrite(greenPin[i + 1], 0);
      ledcWrite(redPin[i + 1], 0);
      delay(10);
    }
  }
}
//////////////////////////////////////////////////////effect_9
void effect_9(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 0; i <= 3; i++) {
      for (int k = i; k <= 2; k++)
      {
        ledcWrite(redPin[k], 255);
        ledcWrite(bluePin[3 - k], 255);
        delay(100);
        ledcWrite(redPin[k], 0);
        ledcWrite(bluePin[3 - k], 0);
        delay(100);
      }
      ledcWrite(greenPin[i], 255);
      ledcWrite(bluePin[3 - i], 255);
      ledcWrite(greenPin[3 - i], 255);
    }
  }

}
/////////////////////////////////////////////////////Effect_10
void effect_10(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int k = 0; k <= 3; k++) {
      for (int i = 0; i <= k; i++) {
        Red(0, i, 0);
        brightnessNodelay();
      }
      for (int i = 0; i <= k; i++) {
        Yellow(0, i, 0);
        brightnessNodelay();
      }
      for (int i = 0; i <= k; i++) {
        Green(0, i, 0);
        brightnessNodelay();
      }
      for (int i = 0; i <= k; i++) {
        White(0, i, 0);
        brightnessNodelay();
      }
      for (int i = 0; i <= k; i++) {
        Cyan(0, i, 0);
        brightnessNodelay();
      }
      for (int i = 0; i <= k; i++) {
        Blue(0, i, 0);
        brightnessNodelay();
      }
      for (int i = 0; i <= k; i++) {
        Pink(0, i, 0);
        brightnessNodelay();
      }
    }
  }
}
/////////////////////////////////////////////////////Effect_11
void effect_11(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 0; i <= 3; i++) {
      ledcWrite(redPin[i], 255);
      i++;
      ledcWrite(greenPin[i], 255);
      delay(100);
      ledcWrite(redPin[i - 1], 0);
      delay(50);
    } ledOff(0);
    for (int i = 3; i >= 0; i--) {
      ledcWrite(bluePin[i], 255);
      i--;
      ledcWrite(redPin[i], 255);
      delay(100);
      ledcWrite(bluePin[i + 1], 0);
      delay(50);
    }
  }
}
/////////////////////////////////////////////////////effect_12
void effect_12(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    int count = 3;
    for (int i = 0; i <= 3; i++) {
      ledcWrite(bluePin[i], 255);  // chaser 1
      ledcWrite(bluePin[i - 1], 255);
      ledcWrite(bluePin[count], 255); // chaser 2
      ledcWrite(bluePin[count - 1], 255); // chaser 2
      count--;
      delay(100);
    }
    ledOff(0);
    count = 2;
    for (int i = 2; i >= 0; i--) {
      ledcWrite(redPin[i], 255);  // chaser 1
      ledcWrite(redPin[i - 1], 255);
      ledcWrite(redPin[count], 255); // chaser 2
      ledcWrite(redPin[count - 1], 255); // chaser 2
      count++;
      delay(100);
    }
    ledOff(0);
    count = 3;
    for (int i = 0; i <= 3; i++) {
      ledcWrite(greenPin[i], 255);  // chaser 1
      ledcWrite(greenPin[i - 1], 255);
      ledcWrite(greenPin[count], 255); // chaser 2
      ledcWrite(greenPin[count - 1], 255); // chaser 2
      count--;
      delay(100);
    }
    ledOff(0);
    count = 2;
    for (int i = 2; i >= 0; i--) {
      ledcWrite(redPin[i], 255);
      ledcWrite(bluePin[i], 255);
      ledcWrite(greenPin[i], 255);
      brightnessNodelay();
      ledcWrite(redPin[i - 1], 255);
      ledcWrite(bluePin[i - 1], 255);
      ledcWrite(greenPin[i - 1], 255);
      brightnessNodelay();
      ledcWrite(redPin[count], 255);
      ledcWrite(bluePin[count], 255);
      ledcWrite(greenPin[count], 255);
      brightnessNodelay();
      ledcWrite(redPin[count - 1], 255);
      ledcWrite(bluePin[count - 1], 255);
      ledcWrite(greenPin[count - 1], 255);
      brightnessNodelay();
      count++;
      delay(100);
    }
    ledOff(0);
  }
}
/////////////////////////////////////////////////////effect_13
void effect_13(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    Red(0, 1, 0);
    Yellow(2, 3, 0);
    Green(4, 5, 0);
    White(6, 6, 0);
    Cyan(7, 7, 0);
    Blue(8, 9, 0);
    Pink(10, 3, 0);
    //brightness();
  }
}