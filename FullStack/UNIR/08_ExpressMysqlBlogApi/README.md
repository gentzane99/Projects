# Blog API con Express y MySQL

API REST desarrollada con **Express.js** y **MySQL** para la gestión de un sistema de blog con autores y posts.  
Proyecto académico enfocado a la creación de un CRUD completo y al uso de relaciones en bases de datos relacionales.

## Tecnologías
- Node.js
- Express.js
- MySQL
- SQL
- JavaScript

## Funcionalidades
- Gestión de autores (crear y listar)
- Gestión de posts (crear y listar)
- Relación post–autor mediante clave foránea
- Obtención de posts junto con la información completa del autor
- Obtención de todos los posts de un autor concreto
- API estructurada bajo el prefijo `/api`

## Estructura de la base de datos

### Autores
- nombre
- email
- imagen

### Posts
- título
- descripción
- fecha de creación
- categoría
- autor_id

## Endpoints principales
- `/api/autores`
- `/api/posts`
- `/api/autores/:id/posts`

## Ejecución
```bash
npm install
npm start
```
## Configuración del entorno

Para que la aplicación funcione correctamente es necesario tener **MySQL en ejecución** en el ordenador.

El proyecto incluye un archivo **`.env.example`** que debe utilizarse como referencia para crear el archivo de configuración real.

### Pasos a seguir
- Asegurarse de que el servicio de **MySQL** está activo
- Crear un archivo `.env` en la raíz del proyecto
- Copiar el contenido de `.env.example`
- Ajustar los valores según la configuración local de MySQL

### Ejemplo de configuración del archivo `.env`
```env
PORT=3000
NODE_ENV=development

DB_HOST=localhost
DB_USER=root
DB_PASSWORD=12345
DB_PORT=3306
DB_NAME=Blog
```

## Pruebas de la API

El proyecto incluye un archivo **`pruebas.rest`** para realizar pruebas de los endpoints utilizando la extensión **REST Client** de Visual Studio Code.

Este archivo contiene peticiones preparadas para:
- Crear autores
- Listar autores
- Crear posts
- Listar posts
- Obtener los posts de un autor concreto

### Para ejecutar las pruebas
- Instalar la extensión **REST Client** en VS Code
- Arrancar el servidor con:
```bash
npm start
```

- Abrir el archivo `pruebas.rest`
- Ejecutar las peticiones directamente desde el editor

## Notas
- Base de datos incluida mediante fichero SQL
- Es necesario un entorno MySQL local correctamente configurado
- El proyecto está orientado a prácticas de backend y diseño de APIs
