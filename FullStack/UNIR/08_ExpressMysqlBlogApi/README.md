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
**Autores**
- nombre
- email
- imagen

**Posts**
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

## Notas
- Base de datos incluida mediante fichero SQL
- Proyecto orientado a prácticas de backend y diseño de APIs