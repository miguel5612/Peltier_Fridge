const int setPointA = 8;
const int setPointB = 9;
const int setPointC = 10;
const int setPointD = 11;

const int displayTempA = 3;
const int displayTempB = 4;
const int displayTempC = 5;
const int displayTempD = 6;

const int inputAnalog = A0;
const int startPulse = 2;
const int salidaPeltier = 13;

void setup() {
  // put your setup code here, to run once:
  //Pulso con el que enciende el refrigerador
  pinMode(startPulse, INPUT);
  //Entrada del lm35
  pinMode(inputAnalog, INPUT);
  //Salida hacia la peltier
  pinMode(salidaPeltier, OUTPUT);

  //Entrada de la botonera (Binario)
  pinMode(setPointA, INPUT);
  pinMode(setPointB, INPUT);
  pinMode(setPointC, INPUT);
  pinMode(setPointD, INPUT);

  //Salida la display (Lectura del lm35, rango 0-9 grados)
  pinMode(displayTempA, OUTPUT);
  pinMode(displayTempB, OUTPUT);
  pinMode(displayTempC, OUTPUT);
  pinMode(displayTempD, OUTPUT);

  //Impresion en el puerto serie
  Serial.begin(9600);

  digitalWrite(salidaPeltier, LOW);
}

void loop() {
  if(digitalRead(startPulse))
  {
    int setPoint = BCD2Integer(setPointA, setPointB, setPointC, setPointD);
    Serial.print("Temperatura deseada: ");
    Serial.println(setPoint);
    double tempActual = map(analogRead(inputAnalog), 0, 1023, 0, 50);
    integer2BCD(tempActual, displayTempA, displayTempB, displayTempC, displayTempD);
    Serial.print("Temperatura actual: ");
    Serial.println(tempActual);
    if(tempActual < setPoint)
    {
      digitalWrite(salidaPeltier, LOW);
      Serial.println("Peltier apagada");  
    }
    else
    {
      digitalWrite(salidaPeltier, HIGH);
      Serial.println("Peltier encendida"); 
    }
  }
  else
  {
    Serial.println("Nevera apagada, por favor presione el boton de encendido");
  }
  
  delay(1000);
}

void integer2BCD(int number, int pinA, int pinB, int pinC, int pinD)
{
  bool out[4];
  switch(number)
  {
    case 0:
      out[0] = 0;
      out[1] = 0;
      out[2] = 0;
      out[3] = 0;
      break;
     
    case 1:
      out[0] = 0;
      out[1] = 0;
      out[2] = 0;
      out[3] = 1;
      break;
    
    case 2:
      out[0] = 0;
      out[1] = 0;
      out[2] = 1;
      out[3] = 0;
      break;

    
    case 3:
      out[0] = 0;
      out[1] = 0;
      out[2] = 1;
      out[3] = 1;
      break;

    
    case 4:
      out[0] = 0;
      out[1] = 1;
      out[2] = 0;
      out[3] = 0;
      break;
      
    case 5:
      out[0] = 0;
      out[1] = 1;
      out[2] = 0;
      out[3] = 1;
      break;
      
    case 6:
      out[0] = 0;
      out[1] = 1;
      out[2] = 1;
      out[3] = 0;
      break;
      
    case 7:
      out[0] = 0;
      out[1] = 1;
      out[2] = 1;
      out[3] = 1;
      break;
      
    case 8:
      out[0] = 1;
      out[1] = 0;
      out[2] = 0;
      out[3] = 0;
      break;
      
    case 9:
      out[0] = 1;
      out[1] = 0;
      out[2] = 0;
      out[3] = 1;
      break;

    
    default:
      out[0] = 1;
      out[1] = 1;
      out[2] = 0;
      out[3] = 1;
      break;
      
  }
  digitalWrite(pinA, out[0]);
  digitalWrite(pinB, out[1]);
  digitalWrite(pinC, out[2]);
  digitalWrite(pinD, out[3]);
}

int BCD2Integer(int pinA, int pinB, int pinC, int pinD)
{
  int result = 0;
  if(digitalRead(pinA))
  {
    result += 1;
  }
  
  if(digitalRead(pinB))
  {
    result += 2;
  }
  
  if(digitalRead(pinC))
  {
    result += 4;
  }
  
  if(digitalRead(pinD))
  {
    result += 8;
  }  
  return result;
}
