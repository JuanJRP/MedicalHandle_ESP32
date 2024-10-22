# Documentación del Proyecto MedicalHandle

## Descripción General
MedicalHandle es un sistema de monitoreo médico basado en ESP32 que permite la medición y registro de signos vitales importantes, incluyendo ritmo cardíaco, saturación de oxígeno (SpO2), temperatura corporal, y condiciones ambientales (temperatura y humedad).

## Características Principales
- Medición de ritmo cardíaco (BPM)
- Medición de saturación de oxígeno (SpO2)
- Medición de temperatura corporal
- Monitoreo de temperatura ambiente
- Monitoreo de humedad ambiente
- Visualización en pantalla OLED
- Exportación de datos a Excel mediante PLX-DAQ

## Componentes de Hardware
- ESP32 (Microcontrolador principal)
- MAX30100 (Sensor de pulso y oximetría)
- MLX90614 (Sensor de temperatura infrarrojo)
- DHT11 (Sensor de temperatura y humedad ambiental)
- Pantalla OLED SH1106G (128x64 píxeles)

## Configuración de Pines
- DHT11: Pin 4
- I2C Address (Pantalla OLED): 0x3c

## Estructura del Código

### 1. ESP32_Medical_Handle_V3.ino
Archivo principal que contiene:
- Inclusión de librerías necesarias
- Definición de constantes
- Inicialización de objetos
- Configuración inicial del sistema

```cpp
Constantes principales:
- SCREEN_WIDTH: 128
- SCREEN_HEIGHT: 64
- REPORTING_PERIOD_MS: 1000
- numBeats: 70
```

### 2. Display.ino
Maneja la visualización de datos en la pantalla OLED:
- Ritmo cardíaco
- SpO2
- Temperatura corporal
- Humedad
- Temperatura ambiente
- Índice de medición

### 3. Functions.ino
Contiene funciones utilitarias:
- `testModules()`: Verifica la inicialización de todos los sensores
- `heartBeat(int numBeats)`: Calcula el promedio del ritmo cardíaco

### 4. PLX-DAQ.ino
Gestiona la exportación de datos a Excel mediante el protocolo PLX-DAQ:
- Fecha
- Hora
- Tiempo transcurrido
- BPM
- SpO2
- Temperatura corporal
- Humedad
- Temperatura ambiente

### 5. main.ino (Loop Principal)
Controla el flujo principal del programa:
- Actualización de lecturas de sensores
- Control de visualización
- Gestión de estados (detección de dedo, escaneo, visualización de datos)
- Reset automático cada 33 ciclos

## Estados del Sistema

1. **Estado Inicial**
   - Muestra mensaje "IU Pascual Bravo" y "MedicalHandle Project"
   
2. **Detección de Dedo**
   - Muestra "Finger Detected" y "Scanning..."
   - Inicia el timer para PLX-DAQ
   
3. **Medición Activa**
   - Muestra todas las lecturas de sensores
   - Exporta datos a Excel
   
## Protocolo de Comunicación PLX-DAQ
El sistema utiliza comandos específicos para la comunicación con Excel:
- `CLEARDATA`: Limpia los datos existentes
- `RESETROW`: Reinicia la fila actual
- `RESETTIMER`: Reinicia el temporizador
- `LABEL`: Define las cabeceras de las columnas
- `DATA`: Envía datos de medición

## Consideraciones Técnicas
1. **Frecuencia de Muestreo**
   - Período de reporte: 1000ms (1 segundo)
   - Promedio de ritmo cardíaco: 70 muestras

2. **Calibración del Sensor MAX30100**
   - Corriente LED IR: 11mA

3. **Gestión de Datos**
   - Reset automático cada 33 mediciones
   - Validación de lecturas de SpO2 y ritmo cardíaco

## Limitaciones y Consideraciones
- El sensor de pulso requiere contacto directo y estable
- Las lecturas de SpO2 deben ser mayores a 0 para considerarse válidas
- El sistema realiza un reset automático cada 33 mediciones para evitar sobrecarga de datos

## Mantenimiento y Solución de Problemas
1. **Verificación de Sensores**
   - El sistema realiza pruebas de inicialización automáticas
   - Muestra mensajes de SUCCESS/FAILED para cada componente

2. **Códigos de Error**
   - Fallo en oxímetro: Bucle infinito
   - Fallo en MLX90614: Bucle infinito
   - Fallo en Display: Bucle infinito
   - Fallo en DHT11: Mensaje de error sin bloqueo

## Recomendaciones de Uso
1. Asegurar una buena colocación del dedo en el sensor MAX30100
2. Mantener el sistema en un ambiente con temperatura estable
3. Verificar la conexión Serial para la exportación de datos
4. Monitorear el índice de reset para control de datos
