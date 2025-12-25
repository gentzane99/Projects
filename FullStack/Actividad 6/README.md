# Angular Users CRUD – External API

Aplicación desarrollada en **Angular** que implementa un CRUD completo (Create, Read, Update, Delete) de usuarios consumiendo una **API externa**.  
Proyecto académico enfocado en el uso de componentes, rutas, servicios e integración con APIs REST.

## Objetivo del proyecto
Desarrollar una aplicación Angular completa que permita:
- Consultar un listado de usuarios desde una API externa
- Visualizar el detalle de un usuario
- Crear nuevos usuarios mediante un formulario
- Actualizar usuarios reutilizando el mismo formulario
- Eliminar usuarios con confirmación previa

Todo ello utilizando un sistema de rutas y componentes bien estructado.

## Tecnologías utilizadas
- Angular
- TypeScript
- HTML5
- CSS3
- Bootstrap
- Consumo de API REST (HTTP Client)

## API utilizada
Los datos se obtienen desde la siguiente API externa de pruebas:
https://peticiones.online/users


> Nota: La API es de tipo mock. Las operaciones de creación, actualización y eliminación no son persistentes, pero devuelven respuestas válidas para su gestión en el frontend.

## Funcionalidades principales
- Sistema de rutas:
  - `/home` → listado completo de usuarios
  - `/user/:id` → vista de detalle de un usuario
  - `/newuser` → formulario de alta de usuario
  - `/updateuser/:id` → formulario de actualización reutilizado
- Listado de usuarios en formato grid
- Vista detalle con:
  - Información completa del usuario
  - Botones de volver, actualizar y eliminar
- Formularios con validaciones:
  - Campos obligatorios
  - Validación de email
- Confirmación de eliminación de usuario
- Comunicación entre componentes mediante servicios

## Arquitectura
- Separación entre:
  - Componentes
  - Servicios
  - Interfaces
- Uso de servicios Angular para:
  - Obtener usuarios
  - Crear usuarios
  - Actualizar usuarios
  - Eliminar usuarios
- Uso de interfaces para tipar los datos recibidos de la API


## Ejecución
Instalar dependencias y arrancar el proyecto:
```bash
npm install
ng serve
```

Acceder a la aplicación en:
http://localhost:4200

## Notas
- No existe persistencia real de datos debido a que la API es de pruebas
- Las respuestas del API se gestionan para mostrar mensajes de éxito o error al usuario
- El formulario de alta y actualización reutiliza el mismo componente
