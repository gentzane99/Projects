/*
  File: Carrito.js
  Author: Gentzane Pastor
  Date: 30/06/2025
  Description: Javascript file to store anda mange the products data.
*/
class Carrito {
    // Clase Carrito que representa un carrito de compra
    constructor(products) {
        this.products = products;
        this.carrito = this.products.map((product) => {
            return {
                sku: product.SKU,
                quantity: 0,
                price_unit: product.price,
                price_total: 0,
            };
        });

        this.total = 0;
    }

    // Actualiza el número de unidades que se quieren comprar de un producto
    actualizarUnidades(sku, unidades) {
        this.carrito = this.carrito.map((product) => {
            if (product.sku === sku) {
                this.total -= product.price_total;
                let totalPrecioUnidades = product.price_unit * unidades;
                this.total += totalPrecioUnidades;

                return {
                    sku: product.sku,
                    quantity: unidades,
                    price_unit: product.price_unit,
                    price_total: totalPrecioUnidades,
                };
            }

            return product;
        });
    }

    // Obtiene la información de un producto específico del carrito
    obtenerInformacionProducto(sku) {
        const product = this.carrito.find((item) => item.sku === sku);
        if (product) {
            return {
                sku: product.sku,
                quantity: product.quantity,
                price_unit: product.price_unit,
                price_total: product.price_total,
            };
        } else {
            console.error(
                `Producto con SKU ${sku} no encontrado en el carrito.`
            );
            return null;
        }
    }

    // Obtiene el carrito con el total
    obtenerCarrito() {
        return {
            total: this.total,
            currency: "€",
            products: this.carrito.filter((product) => product.quantity > 0),
        };
    }
}
