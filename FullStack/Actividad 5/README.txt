# Angular Blogging System

Sistema de blogging desarrollado en **Angular** que permite crear y listar publicaciones dentro de una Single Page Application (SPA).  
Proyecto académico enfocado en la gestión de datos desde un formulario y su representación dinámica en la vista.

## Objetivo del proyecto
Desarrollar un sistema de publicación de noticias que permita:
- Mostrar un listado inicial de publicaciones
- Crear nuevas entradas mediante un formulario
- Validar los datos introducidos antes de su inserción
- Actualizar el listado de forma dinámica

Todo ello dentro de un único componente Angular.

## Tecnologías utilizadas
- Angular
- TypeScript
- HTML5
- CSS3
- Programación basada en componentes

## Características principales
- SPA desarrollada con Angular
- Componente `BlogComponent` que incluye:
  - Formulario de creación de noticias
  - Listado de publicaciones
- Uso de:
  - Eventos de Angular
  - Data binding
  - Directivas de templating
- Array de objetos inicializado con dos noticias por defecto
- Validación de formulario:
  - Todos los campos son obligatorios
  - No se inserta la noticia si falta algún dato

## Modelo de datos
Cada publicación contiene:
- Título
- Imagen (URL)
- Texto de la noticia
- Fecha de publicación


## Funcionamiento
- Al cargar la aplicación se muestran dos noticias iniciales
- El usuario puede añadir una nueva noticia desde el formulario
- Si algún campo está vacío, se muestra un aviso y no se añade la publicación
- Al añadir una noticia válida, esta se refleja automáticamente en el listado

## Ejecución
Instalar dependencias y arrancar el proyecto:
```bash
npm install
ng serve

Acceder a la aplicación en:
http://localhost:4200

##Notas
- No se utiliza backend ni persistencia de datos
- Los datos se gestionan únicamente en memoria mediante arrays