#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5

int adc_key_in = 0;
int tecla = -1;

int lee_botones_LCD()
{
  adc_key_in = analogRead(A0);

  if (adc_key_in > 1000)
    return btnNONE; // Ninguno
  if (adc_key_in < 50)
    return btnRIGHT; // Derecha
  if (adc_key_in < 250)
    return btnUP; // Arriba
  if (adc_key_in < 450)
    return btnDOWN; // Abajo
  if (adc_key_in < 650)
    return btnLEFT; // Izquierda
  if (adc_key_in < 850)
    return btnSELECT; // Seleccionar
  return btnNONE;     // Cuando todo falla, devuelve btnNONE
}

const int anios[] = {2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012,
                     2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020,
                     2021, 2022};

const int goles[] = {5, 6, 13, 19, 29, 34, 45, 53, 58, 59, 56, 54, 42,
                     42, 43, 25, 34, 41};

const int totalAnios = sizeof(anios) / sizeof(anios[0]);

int indiceActual = 0;

void setup()
{
  lcd.begin(16, 2);
  lcd.clear();

  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("Goles de");
  lcd.setCursor(0, 1);
  lcd.print("Cristiano");

  delay(3000);

  mostrarDatos();
}

void loop()
{
  tecla = lee_botones_LCD();

  if (tecla != btnNONE)
  {
    delay(200);
    switch (tecla)
    {
    case btnRIGHT:
      if (indiceActual < totalAnios - 1)
      {
        indiceActual++;
        mostrarDatos();
      }
      break;
    case btnLEFT:
      if (indiceActual > 0)
      {
        indiceActual--;
        mostrarDatos();
      }
      break;
    case btnUP:

      Serial.print("PLAY_AUDIO_");
      Serial.println(anios[indiceActual]);

      // Mostrar mensaje en el LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Reproduciendo");
      lcd.setCursor(0, 1);
      lcd.print("audio...");

      delay(2000);    // Mantiene el mensaje durante 2 segundos
      mostrarDatos(); // Vuelve a mostrar los datos
      break;

    default:
      break;
    }
  }

  delay(100);
}

// Función para mostrar los datos en el LCD
void mostrarDatos()
{
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Year: ");
  lcd.print(anios[indiceActual]);

  lcd.setCursor(0, 1);
  lcd.print("Goals: ");
  lcd.print(goles[indiceActual]);
}
