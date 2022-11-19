//============== NOMEAR PINOS ===============

/*
Pinagem motores:
 -By CHARLES
Motor esquerda
  ENA = ~10 port
  IN1 =   2 port
  IN2 =   3 port

Motor direita:
  IN3 =   4
  IN4 =   5
  ENB = ~6 port

*/




//=========== INCLUIR BIBLIOTECAS ===========
//=========== VARIÁVEIS E TABELAS ===========
int e2, e1, c, d2, d1;
//================ SUB-ROTINAS ==============
//================= FUNÇÕES =================
void leitura() {
  // e2 = digitalRead(A4);
  // e1 = digitalRead(A3);
  // c = digitalRead(A2);
  // d1 = digitalRead(A1);
  // d2 = digitalRead(A0);
  e2 = 0;
  e1 = 0;
  c = 1;
  d1 = 0;
  d2 = 0;
}
int frente(int vel) {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  analogWrite(6, vel);
  analogWrite(10, vel);

  Serial.print("Frente em velocidade: ");
  Serial.println(vel);
}
void parar() {
  digitalWrite(3, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(7, HIGH);
  analogWrite(5, 0);
  analogWrite(10, 0);
  Serial.println("Parar");
}
int esquerda(int vel) {
  digitalWrite(3, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(7, LOW);
  analogWrite(5, vel);
  analogWrite(10, 0);
  Serial.print("Esquerda em velocidade: ");
  Serial.println(vel);
}
int direita(int vel) {
  digitalWrite(3, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(7, LOW);
  analogWrite(10, vel);
  analogWrite(5, 0);
  Serial.print("direita em velocidade: ");
  Serial.println(vel);
}
void routine_test() {
  for (int i = 0; i < 5; i++) {
    for (int velo = 120; velo < 255; velo++) {
      switch (i) {
        case 0:
          frente(200);
          break;
        case 1:
          frente(200);
          break;
        case 2:
          esquerda(200);

          break;
        case 3:
          parar();
          break;
        case 4:
          direita(200);
          break;
      }
      if (velo % 20 == 0) {
        digitalWrite(11, HIGH);
      } else if (velo % 20 == 10) {
        digitalWrite(11, LOW);
      }
    }
  }
}
int* readIRSensor(int* vector) {
  int value = 0;
  for (int i = 0; i < 5; i++) {
    switch (i) {
      case 0:
        value = analogRead(A0);
        if (value > 600) {
          vector[i] = 1;

        } else if (value < 400) {
          vector[i] = 0;
        }
        value = 0;
        break;
      case 1:
        value = analogRead(A1);
        if (value > 600) {
          vector[i] = 1;

        } else if (value < 400) {
          vector[i] = 0;
        }
        value = 0;
        break;
      case 2:
        value = analogRead(A2);
        if (value > 600) {
          vector[i] = 1;

        } else if (value < 400) {
          vector[i] = 0;
        }
        value = 0;
        break;
      case 3:
        value = analogRead(A3);
        if (value > 600) {
          vector[i] = 1;

        } else if (value < 400) {
          vector[i] = 0;
        }
        value = 0;
        break;
      case 4:
        value = analogRead(A4);
        if (value > 600) {
          vector[i] = 1;

        } else if (value < 400) {
          vector[i] = 0;
        }
        value = 0;
        break;
    }
  }
  return vector;
}
//================== SETUP ==================
int VELOCIDADE = 180;  // 0 -> 255
void setup() {
  pinMode(2, OUTPUT);   // IN1
  pinMode(3, OUTPUT);   // IN2
  pinMode(4, OUTPUT);   // IN3
  pinMode(5, OUTPUT);   // IN4
  pinMode(6, OUTPUT);   // enable B
  pinMode(8, OUTPUT);   // buzzer
  pinMode(10, OUTPUT);  // enable A
  pinMode(11, OUTPUT);  // led de identificação
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);

  // pinMode(9, OUTPUT); // não usa
  // pinMode(7, OUTPUT); // não usa

  //---------- CONDIÇÕES INICIAIS ----------
  // digitalWrite(3, LOW);
  // digitalWrite(2, LOW);
  // digitalWrite(6, LOW);
  // digitalWrite(7, LOW);
  Serial.begin(9600);

}  // fecha void setup()

int count = 0;  // contador para o led
int velocity = 0;
const int amount = 100;  // contador para o led]
int sensors_vec[5];
//============== LOOP INFINITO ===============
void loop() {
  // lê os sensores
  // leitura();
  // teste_routine();
  readIRSensor(sensors_vec);
  for (int i = 0; i < 5; i++) {
    Serial.print(sensors_vec[i]);
    Serial.print(" ");
  }
  // Serial.println();

  e2 = sensors_vec[0];
  e1 = sensors_vec[1];
  c = sensors_vec[2];
  d1 = sensors_vec[3];
  d2 = sensors_vec[4];
  // frente
  if (e2 == 0 && d2 == 0 && e1 == 0 && d1 == 0 && c == 1) {
    frente(VELOCIDADE);
  }
  // virar a esquerda
  else if (e2 == 1 && e1 == 1 && c == 0 && d1 == 0 && d2 == 0) {
    esquerda(VELOCIDADE);
  } else if (e2 == 1 && e1 == 0 && c == 0 && d1 == 0 && d2 == 0) {
    esquerda(VELOCIDADE);
  } else if (e2 == 0 && e1 == 1 && c == 0 && d1 == 0 && d2 == 0) {
    esquerda(VELOCIDADE);
  }
  // virar a direita

  else if (e2 == 0 && e1 == 0 && c == 0 && d1 == 1 && d2 == 1) {
    direita(VELOCIDADE);
  } else if (e2 == 0 && e1 == 0 && c == 0 && d1 == 1 && d2 == 0) {
    direita(VELOCIDADE);
  } else if (e2 == 0 && e1 == 0 && c == 0 && d1 == 0 && d2 == 1) {
    direita(VELOCIDADE);
  }
  // parar
  else {
    parar();
  }

  // Serial.println("esquerdo 2:");
  // Serial.println(e2);
  // Serial.println("esquerdo 1:");
  // Serial.println(e1);
  // Serial.println("centrao:");
  // Serial.println(c);
  // Serial.println("direito 1:");
  // Serial.println(d1);
  // Serial.println("direito 2:");
  // Serial.println(d2);

  // blink led code
  if (count % amount * 5 == 0) {
    digitalWrite(11, LOW);
  } else if (count % amount * 5 == amount * 4) {
    digitalWrite(11, HIGH);
  }
  // Serial.println(count % amount *5);
  if (count > 10000)
    count = 0;
  count++;

}  // fecha void loop()