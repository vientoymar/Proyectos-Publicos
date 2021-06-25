Usando el código de MarkerGaraje, ahora quiero sacar los datos de un SDM120M. Mi proyecto será enviar cada hora el valor de potencia total a un bot de telegram.



Este proyecto surge de la necesidad de poder leer los datos de un sensor CPA-050 de CarloGavazzi cada 500 ms, se contacta con el proveedor y este nos indica que no es posible leer a tal velocidad con los controladores que ellos ofrecen, por tanto se decide prescindir del controlador y leer directamente por modbus desde el sensor, el proyecto completo consiste en coger los datos y enviarlos mediante mqtt.


