#include <ModbusMaster.h> //ModbusMaster by Doc Walker Version 2.0.1

//Registros
#define regTension 0x30001
#define regCorriente 0x30017
#define regPotenciaActiva 0x30013 
#define regPotenciaReactiva 0x30025
#define regPotenciaAparente 0x30019
#define regFactorPotencia 0x30031
#define regFrecuencia 0x30071
#define regTHD 0x30343


// Objeto modbus maestro.
ModbusMaster node;    

void setup() {
	Serial.begin(9600);   // Inicio puerto serie debug.
  Serial1.begin(2400,SERIAL_8N1,3,1);  //Inicio puerto serie modbus, velocidad 2400, 8bits sin paridad 1 bit de parada (8n1) RX TX. Valores por defecto del SDM120
	node.begin(1, Serial1); // La comunicación será con la dirección 0x01 a través del puerto serie1.

}

void loop() {
  imprimirTodo();
  delay(5000);
}

//Funciones

float leerRegistro(uint16_t registro){
  //Por defecto leemos 2 registros ya que los CPA de CarloGavazzi devuelven 32bits LSW MSW
  uint8_t result;
  uint16_t valor1,valor2;
  uint32_t valorSinSigno;
  int32_t valorConSigno;
  float resultado;

  result = node.readHoldingRegisters(registro,2); // Realizamos la petición, dirección 0x40205, 2 registros.
  if ( result == node.ku8MBSuccess ) {
		// Si la petición ha sido correcta y no ha fallado tendremos un buffer con los
		// registros, en el primero esta la parte baja del valor y en el segundo la alta.	
		valor1 = node.getResponseBuffer(0); // Primer registro LSW.
    valor2 = node.getResponseBuffer(1); // Segundo registro MSW
    valorSinSigno = valor2<<16 | valor1; //Los juntamos en un unsigned de 32 bits
    valorConSigno = (long)valorSinSigno; //Lo pasamos a un entero de 32bits con signo

    //Dependiendo del registro hay que aplicarla un factor de escala diferente
    switch (registro) {
      case regTension:
        resultado = valorConSigno/100.0;
        break;

      case regCorriente:
        resultado = valorConSigno/100.0;
        break;

      case regPotenciaActiva:
        resultado = valorConSigno/100.0; 
        break;
      
      case regPotenciaReactiva:
        resultado = valorConSigno/100.0; 
        break;

      case regPotenciaAparente:
        resultado = valorConSigno/100.0; 
        break;

      case regFactorPotencia:
        resultado = valorConSigno/100.0; 
        break;

      case regFrecuencia:
        resultado = valorConSigno/100.0; 
        break;

      case regTHD:
        resultado = valorConSigno/10000.0; 
        break;        
      

    }
    return resultado;
	}else{
    return -1;
  }
}

void imprimirTension(){
  Serial.print("Tension: ");
  Serial.print(leerRegistro(regTension));
  Serial.println(" V");
}
void imprimirCorriente(){
  Serial.print("Corriente: ");
  Serial.print(leerRegistro(regCorriente));
  Serial.println(" A");
}

void imprimirPotenciaActiva(){
  Serial.print("Potencia Activa: ");
  Serial.print(leerRegistro(regPotenciaActiva));
  Serial.println(" W");
}

void imprimirPotenciaReactiva(){
  Serial.print("Potencia Rectiva: ");
  Serial.print(leerRegistro(regPotenciaReactiva));
  Serial.println(" VAr");
}

void imprimirPotenciaAparente(){
  Serial.print("Potencia Aparente: ");
  Serial.print(leerRegistro(regPotenciaAparente));
  Serial.println(" VA");
}

void imprimirFactorPotencia(){
  Serial.print("Factor de potencia: ");
  Serial.println(leerRegistro(regFactorPotencia));
}

void imprimirFrecuencia(){
  Serial.print("Frecuencia: ");
  Serial.print(leerRegistro(regFrecuencia));
  Serial.println(" Hz");
}

void imprimirTHD(){
  Serial.print("THD: ");
  Serial.print(leerRegistro(regTHD));
  Serial.println(" %");
}

void imprimirTodo(){
  imprimirTension();
  imprimirCorriente();
  imprimirPotenciaActiva();
  imprimirPotenciaReactiva();
  imprimirPotenciaAparente();
  imprimirFactorPotencia();
  imprimirFrecuencia();
  imprimirTHD();

}
