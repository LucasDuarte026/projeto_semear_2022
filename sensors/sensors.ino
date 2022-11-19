int* rotinaAnalog(int* vector) {
  int value = 0;
  for (int i = 0; i < 5; i++) {
    switch (i) {
      case 0:
        value = analogRead(A0);
        vector[i] = value;
        break;
      case 1:
        value = analogRead(A0);
        vector[i] = value;
        break;
      case 2:
        value = analogRead(A0);
        vector[i] = value;
        break;
      case 3:
        value = analogRead(A0);
        vector[i] = value;
        break;
      case 4:
        value = analogRead(A0);
        vector[i] = value;
        break;
    }
  }
  return vector;
}
int high_value = 500;
int low_value = 300;
int* rotina(int* vector) {
  int value = 0;
  for (int i = 0; i < 5; i++) {
    switch (i) {
      case 0:
        value = analogRead(A0);
        if (value > high_value) {
          vector[i] = 1;

        } else if (value < low_value) {
          vector[i] = 0;
        }
        value = 0;
        break;
      case 1:
        value = analogRead(A1);
        if (value > high_value) {
          vector[i] = 1;

        } else if (value < low_value) {
          vector[i] = 0;
        }
        value = 0;
        break;
      case 2:
        value = analogRead(A2);
        if (value > high_value) {
          vector[i] = 1;

        } else if (value < low_value) {
          vector[i] = 0;
        }
        value = 0;
        break;
      case 3:
        value = analogRead(A3);
        if (value > high_value) {
          vector[i] = 1;

        } else if (value < low_value) {
          vector[i] = 0;
        }
        value = 0;
        break;
      case 4:
        value = analogRead(A4);
        if (value > high_value) {
          vector[i] = 1;

        } else if (value < low_value) {
          vector[i] = 0;
        }
        value = 0;
        break;
    }
  }
  return vector;
}



void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A5, INPUT);
  Serial.begin(9600);
}

int infra[5];

void loop() {
  rotina(infra);
  // rotinaAnalog(infra);
  for (int i = 0; i < 5; i++) {
    // Serial.print(analogRead(A1));
    Serial.print(infra[i]);
    Serial.print(" ");
  }
  Serial.println();
}