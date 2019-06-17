#include "mbed.h"
#include "TextLCD.h"
#include "DHT.h"
#include "MMA8451Q.h"

#define MMA8451_I2C_ADDRESS (0x1d<<1)                               // Direccion I2C del MMA8451Q por defecto

TextLCD lcd(PTE5, PTE4, PTE3, PTE2, PTB11, PTB10,TextLCD::LCD16x2); // Crea una interfaz para un LCD16x2
Serial BT(PTE0,PTE1);                                               // Crea un puerto serial que va emitir datos via bluetooth
PwmOut servo1(PTC9);                                                // Crea un PWM para servo de T=20ms y d=1ms(atras)~1.5ms(parado)~2ms(adelante)
PwmOut servo2(PTC8);                                                // Crea un PWM para servo de T=20ms y d=1ms(atras)~1.5ms(parado)~2ms(adelante)
DHT senTHR(PTB0,DHT11);                                             // Crea un pin tipo 1-wire del tipo AOSONG para el sensor DHT11
MMA8451Q acc(PTE25, PTE24, MMA8451_I2C_ADDRESS);                    // Crea un puerto I2C con SDA = PTE25 y SCL = PTE24 llamando a la direccion 0x01 por defecto

int main() 
{   
    int val=0;                  // variables BT
    int error=0;                // variables DHT11
    float T_C,T_F,T_K, HR;      // variables DHT11
    float x, y, z;              // variables acelerometro
    
    BT.format(8,SerialBase::None,1);
    BT.baud(9600);
    
    servo1.period_ms(20);
    servo2.period_ms(20);
    
    lcd.cls();
    
    lcd.locate(0,0);
    lcd.printf("key:%d",val); 
    lcd.locate(0,1);
    lcd.printf("MMA8451 ID: %d\n", acc.getWhoAmI() );
    wait(1.5);
    
    while(1) 
    {
        if(BT.readable()==1)
        {
            val=BT.getc();
            lcd.locate(0,0);
            lcd.printf("key:%d",val); 
        }
        /*
        error = senTHR.readData();
        if (0 == error) 
        {
            T_C   = senTHR.ReadTemperature(CELCIUS);
            T_F   = senTHR.ReadTemperature(FARENHEIT);
            T_K   = senTHR.ReadTemperature(KELVIN);
            HR    = senTHR.ReadHumidity();
            lcd.locate(6,0);
            lcd.printf("Temp:%3.1fC",T_C); 
            lcd.locate(0,1);
            lcd.printf("%3.1fF %3.1fK%3.0f%",T_F,T_K,HR);
        }  */
        
        x = (acc.getAccX());
        y = (acc.getAccY());
        z = (acc.getAccZ());
        lcd.locate(6,0);
        lcd.printf("X: %1.2f", x);
        lcd.locate(0,1);
        lcd.printf("Y: %1.2f Z: %1.2f", y, z);
        
          
        switch(val)
        {
            case 0:
                servo1.pulsewidth_us(1530);
                servo2.pulsewidth_us(1530);
            break;
            case 1:
                servo1.pulsewidth_us(1000);
                servo2.pulsewidth_us(1550);
            break;
            case 2:
                servo1.pulsewidth_us(1000);
                servo2.pulsewidth_us(2000);
            break;
            case 3:
                servo1.pulsewidth_us(1450);
                servo2.pulsewidth_us(2000);
            break;
            case 4:
                servo1.pulsewidth_us(1000);
                servo2.pulsewidth_us(1530);
            break;
            case 5:
                servo1.pulsewidth_us(2000);
                servo2.pulsewidth_us(2000);
            break;
            case 6:
                servo1.pulsewidth_us(1530);
                servo2.pulsewidth_us(2000);
            break;
            case 7:
                servo1.pulsewidth_us(2000);
                servo2.pulsewidth_us(1450);
            break;
            case 8:
                servo1.pulsewidth_us(2000);
                servo2.pulsewidth_us(1000);
            break;
            case 9:
                servo1.pulsewidth_us(1550);
                servo2.pulsewidth_us(1000);
            break;
            default:
                servo1.pulsewidth_us(1530);
                servo2.pulsewidth_us(1530);
            break;

        }
    }
}
