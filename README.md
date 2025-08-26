# Philosophers

Este proyecto es una implementación del clásico **problema de los filósofos comensales**, que forma parte del cursus de 42.  
El objetivo principal es **aprender sobre concurrencia, sincronización y gestión de hilos** utilizando únicamente herramientas básicas del lenguaje C, **sin bonus ni funcionalidades extra**.

---

## 📖 ¿En qué consiste el proyecto?

- **Contexto**: Cinco filósofos están sentados alrededor de una mesa redonda. Cada filósofo alterna entre **comer**, **dormir** y **pensar**.  
  Sin embargo, hay un número limitado de recursos (tenedores), lo que puede provocar condiciones de carrera o *deadlocks* si no se gestiona correctamente.  

- **Objetivo**:  
  - Simular este comportamiento garantizando que **ningún filósofo muera de hambre**.  
  - Evitar **data races** y **deadlocks** mediante sincronización adecuada.  
  - Usar exclusivamente **hilos (threads)** y **mutexes**.  

- **Restricciones**:  
  - Solo se permite el uso de `pthread`, `usleep` y funciones estándar de C.  
  - No se pueden usar semáforos ni librerías externas.  
  - El proyecto **no incluye bonus**, únicamente la parte obligatoria.  

---

## ✨ Características implementadas

- **Gestión de hilos (threads)** para simular a cada filósofo.  
- **Protección de recursos compartidos** mediante `pthread_mutex_t`.  
- **Control preciso de tiempos** para comer, dormir y detectar la muerte de un filósofo.  
- **Estructura modular y clara** del código.  
- **Logs ordenados** para seguir la actividad de cada filósofo en tiempo real.  

---

## 📌 Estado actual

- **El proyecto está casi finalizado.**  
- La simulación funciona correctamente bajo la mayoría de escenarios.  
- **Faltan algunos ajustes menores**:  
  - Mejorar la gestión de errores en casos extremos.  
  - Revisar condiciones límite (por ejemplo, cuando solo hay 1 filósofo).  
  - Optimizar y limpiar el código.  

---

## ⚙️ Cómo compilar y ejecutar

```bash
make            # Compila el proyecto
./philo args     # Ejecuta la simulación
