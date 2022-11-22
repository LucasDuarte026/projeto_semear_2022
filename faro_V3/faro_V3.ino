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
int voltar(int vel) {
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  analogWrite(6, vel);
  analogWrite(10, vel);

  Serial.print("voltando em velocidade: ");
  Serial.println(vel);
}
void parar() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  analogWrite(6, 0);
  analogWrite(10, 0);
  Serial.println("Parar");
}
int esquerda(int vel) {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  analogWrite(6, vel / 1.85);
  analogWrite(10, vel / 1.15);
  Serial.print("Esquerda em velocidade: ");
  Serial.println(vel);
}
int direita(int vel) {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  analogWrite(6, 1.25 * vel);
  analogWrite(10, vel / 1.85);
  Serial.print("direita em velocidade: ");
  Serial.println(vel);
}
int rodar(int vel) {
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  analogWrite(6, vel);
  analogWrite(10, vel);
  Serial.print("rodando ");
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
// ranges da leitura analógica para os calores de alto e baixo
int high_value = 500;
int low_value = 300;
//logica da leitura (pode inverter A com B)
int A = 0;
int B = 1;
int* readIRSensor(int* vector) {
  int value = 0;
  for (int i = 0; i < 5; i++) {
    switch (i) {
      case 0:
        value = analogRead(A4);
        if (value > high_value) {
          vector[i] = A;

        } else if (value < low_value) {
          vector[i] = B;
        }
        value = 0;
        break;
      case 1:
        value = analogRead(A3);
        if (value > high_value) {
          vector[i] = A;

        } else if (value < low_value) {
          vector[i] = B;
        }
        value = 0;
        break;
      case 2:
        value = analogRead(A2);
        if (value > high_value) {
          vector[i] = A;

        } else if (value < low_value) {
          vector[i] = B;
        }
        value = 0;
        break;
      case 3:
        value = analogRead(A1);
        if (value > high_value) {
          vector[i] = A;

        } else if (value < low_value) {
          vector[i] = B;
        }
        value = 0;
        break;
      case 4:
        value = analogRead(A0);
        if (value > high_value) {
          vector[i] = A;

        } else if (value < low_value) {
          vector[i] = B;
        }
        value = 0;
        break;
    }
  }
  return vector;
}




//================== SETUP MACROS ==================
int VELOCIDADE = 130;                           // 0 -> 255  ( 130 É BOM)
const unsigned long TIME_TO_ROLL_360 = 44000;   //  60000;  // em milisseconds
// const unsigned long TIME_TO_ROLL_180 = 70000;  //160000;  // em milisseconds
unsigned long myTime = 0;

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
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  Serial.begin(9600);

}  // fecha void setup()

int count = 0;  // contador para o led
int velocity = 0;
const int amount = 100;  // contador para o led]
int sensors_vec[5];



//============== LOOP INFINITO ===============
void loop() {

  // lê os sensores
  readIRSensor(sensors_vec);
  for (int i = 0; i < 5; i++) {
    Serial.print(sensors_vec[i]);
    Serial.print(" ");
  }

  e2 = sensors_vec[0];
  e1 = sensors_vec[1];
  c = sensors_vec[2];
  d1 = sensors_vec[3];
  d2 = sensors_vec[4];

  // ########################  ir a frente   ########################
  if (e2 == 0 && e1 == 0 && c == 1 && d1 == 0 && d2 == 0) {
    frente(VELOCIDADE);
  } else if (e2 == 0 && e1 == 1 && c == 1 && d1 == 1 && d2 == 0) {
    frente(VELOCIDADE);

    // ########################  ir para trás   ########################

  } else if (e2 == 0 && e1 == 0 && c == 0 && d1 == 0 && d2 == 0) {
    voltar(VELOCIDADE * 1.25);
  } else if (e2 == 1 && e1 == 1 && c == 1 && d1 == 1 && d2 == 1) {
    frente(VELOCIDADE);
  }



  // ########################  virar a esquerda   ########################
  else if (e2 == 1 && e1 == 1 && c == 0 && d1 == 0 && d2 == 0) {
    direita(1.25 * VELOCIDADE);
  } else if (e2 == 1 && e1 == 0 && c == 0 && d1 == 0 && d2 == 0) {
    direita(VELOCIDADE);
  } else if (e2 == 0 && e1 == 1 && c == 0 && d1 == 0 && d2 == 0) {
    direita(VELOCIDADE);
  } else if (e2 == 1 && e1 == 1 && c == 1 && d1 == 0 && d2 == 0) {
    direita(VELOCIDADE);
  } else if (e2 == 1 && e1 == 0 && c == 1 && d1 == 0 && d2 == 0) {
    direita(VELOCIDADE);
  } else if (e2 == 0 && e1 == 1 && c == 1 && d1 == 0 && d2 == 0) {
    direita(VELOCIDADE);
  }

  // ######################## virar a direita   ########################

  else if (e2 == 0 && e1 == 0 && c == 0 && d1 == 1 && d2 == 1) {
    esquerda(1.25 * VELOCIDADE);
  } else if (e2 == 0 && e1 == 0 && c == 0 && d1 == 1 && d2 == 0) {
    esquerda(VELOCIDADE);
  } else if (e2 == 0 && e1 == 0 && c == 0 && d1 == 0 && d2 == 1) {
    esquerda(VELOCIDADE);
  } else if (e2 == 0 && e1 == 0 && c == 1 && d1 == 1 && d2 == 0) {
    esquerda(VELOCIDADE);
  } else if (e2 == 0 && e1 == 0 && c == 1 && d1 == 1 && d2 == 1) {
    esquerda(VELOCIDADE);
  } else if (e2 == 0 && e1 == 0 && c == 1 && d1 == 0 && d2 == 1) {
    esquerda(VELOCIDADE);
  }

  // ########################  parar   ########################
  else {
    frente(0.7 * VELOCIDADE);
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

  if (myTime > 3000) {

    /*
    // rodar 180 comum
    if (myTime % TIME_TO_ROLL_180 > 0 && myTime % TIME_TO_ROLL_180 < 2000) {
      unsigned long t1 = millis();
      unsigned long t2 = 0;
      int diff = t2 - t1;

      while (diff < 1250) {
        t2 = millis();
        diff = t2 - t1;

        rodar(VELOCIDADE);
      }
    }
    */
    // rodar 360 comum
    if (myTime % TIME_TO_ROLL_360 > 0 && myTime % TIME_TO_ROLL_360 < 2000) {
      unsigned long t1 = millis();
      unsigned long t2 = 0;
      int diff = t2 - t1;

      while (diff < 2200) {
        t2 = millis();
        diff = t2 - t1;

        rodar(VELOCIDADE);
      }
    }
  }

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
  myTime = millis();
  Serial.print("time : ");
  Serial.print(myTime);
  Serial.print("  | ");
}  // fecha void loop()