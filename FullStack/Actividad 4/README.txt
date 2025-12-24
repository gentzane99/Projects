# Agoodshop – Shopping Cart

Implementación del carrito de la compra para la tienda online ficticia **Agoodshop**.  
Proyecto académico centrado en la lógica del carrito, la programación orientada a objetos y la interacción con el DOM.

## Objetivo del proyecto
Desarrollar la funcionalidad completa de un carrito de la compra simulando un entorno real de e-commerce, aplicando:
- Programación orientada a objetos en JavaScript
- Consumo de datos desde una API
- Manipulación dinámica del DOM

## Tecnologías utilizadas
- HTML5
- CSS3
- JavaScript
- Programación Orientada a Objetos
- Consumo de API (JSON)

## Características principales
- Clase `Carrito` encargada de:
  - Almacenar productos
  - Gestionar unidades
  - Calcular totales
- Separación clara entre:
  - Lógica de negocio (clase Carrito)
  - Manipulación del DOM
- Listado dinámico de productos obtenidos desde una API
- Actualización del total en tiempo real según la interacción del usuario

## API
Los productos se obtienen desde una API simulada en formato JSON, que incluye:
- SKU
- Nombre del producto
- Precio
- Moneda

## Funcionamiento
- Se cargan los productos desde la API
- El usuario puede modificar la cantidad de cada producto
- El total del carrito se recalcula automáticamente en cada cambio

## Notas
- La maquetación es funcional y mínima, priorizando la lógica del carrito.
- El formulario y los botones están preparados para interacción, no para pago real.

## Ejecución
Este proyecto utiliza un archivo JSON local como fuente de datos.
Para que funcione correctamente es necesario ejecutarlo mediante un servidor local.

Ejemplo:
- Usar la extensión Live Server en VS Code
- O ejecutar `npx serve` desde la raíz del proyecto

