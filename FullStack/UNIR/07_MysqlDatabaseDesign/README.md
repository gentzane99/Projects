# Diseño de Bases de Datos con MySQL

Proyecto académico centrado en el diseño, creación y consulta de bases de datos utilizando **MySQL** y **SQL**, poniendo especial atención en la correcta modelización de tablas, relaciones y consultas.

La práctica se divide en dos partes:
1. Diseño de una base de datos desde cero a partir de unos requisitos.
2. Ejecución de consultas SQL sobre una base de datos existente.

---

## Objetivos del proyecto

- Diseñar una base de datos relacional correctamente normalizada.
- Identificar tablas, campos, claves primarias y foráneas.
- Crear relaciones entre entidades.
- Insertar datos de prueba.
- Ejecutar consultas SQL complejas sobre una base de datos real.
- Trabajar con sentencias `SELECT`, `INSERT`, `UPDATE` y `DELETE`.

---

## Tecnologías utilizadas

- MySQL
- SQL
- MySQL Workbench

---

## Apartado 1: Diseño de base de datos (Plataforma de música)

Se diseña una base de datos inspirada en una plataforma de streaming musical que permite:

- Gestionar usuarios
- Almacenar artistas, álbumes y canciones
- Crear listas de reproducción
- Registrar qué canciones ha escuchado cada usuario al menos una vez

### Entidades principales
- Usuarios
- Artistas
- Álbumes
- Canciones
- Listas de reproducción

### Características del modelo
- Relaciones 1:N y N:M correctamente implementadas
- Uso de tablas intermedias
- Claves primarias y foráneas
- Tipos de datos adecuados a cada campo

Además, se incluyen:
- Datos de ejemplo (usuarios, artistas, álbumes, canciones y listas)
- Registro de canciones escuchadas por un usuario

---

## Apartado 2: Consultas SQL

Se trabaja sobre una base de datos proporcionada previamente relacionada con restaurantes y reservas.

Se realizan consultas como:
- Listado de reservas por fecha y restaurante
- Restaurantes favoritos abiertos
- Modificación y eliminación de registros
- Cálculo de aforos
- Búsqueda de mesas disponibles
- Consultas agregadas con filtros por fechas

Cada consulta incluye:
- Sentencia SQL
- Captura de pantalla mostrando la ejecución y el resultado

---

## Notas importantes

- No se incluye la carpeta `node_modules` ni archivos innecesarios.
- El proyecto está pensado para ser importado y ejecutado en MySQL Workbench.
- Las capturas del apartado 2 muestran tanto la consulta como el resultado obtenido.
