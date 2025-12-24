/*
  File: products.js
  Author: Gentzane Pastor
  Date: 30/06/2025
  Description: Javascript file to manage the DOM and the products.
*/
const init = (products) => {
    const carrito = new Carrito(products.products);
    const currency = products.currency;
    const productListItemTpl = document.querySelector("#products-list-item");
    const productsList = document.querySelector(".products-list");

    products.products.forEach((product) => {
        //Clone the template and get the elements to modify
        const newProductListItem = productListItemTpl.content.cloneNode(true);
        const tr = newProductListItem.querySelector(".carrito-product");
        const priceTotal = tr.querySelector(".price-total");
        const inputQuantity = tr.querySelector(".product-amount");
        const buttonPlus = tr.querySelector(".button-plus");
        const buttonMinus = tr.querySelector(".button-minus");

        //Set the data of the products
        tr.querySelector(".product-name").textContent = product.title;
        tr.querySelector(".product-sku").textContent = `Ref: ${product.SKU}`;
        tr.querySelector(".price-unit").textContent = `${Number(
            product.price
        ).toFixed(2)}${currency}`;
        tr.querySelector(".price-total").textContent = `0${currency}`;

        //Event for + button
        buttonPlus.addEventListener("click", () => {
            //Update the input value and the cart
            inputQuantity.value = Number(inputQuantity.value) + 1;
            carrito.actualizarUnidades(product.SKU, inputQuantity.value);

            priceTotal.textContent = `${Number(
                carrito.obtenerInformacionProducto(product.SKU).price_total
            ).toFixed(2)}${currency}`;

            //Update total chart
            showTotal(product);
        });

        //Event for - button
        buttonMinus.addEventListener("click", () => {
            //Check that the input value is greater than 0 before decrementing
            if (inputQuantity.value > 0) {
                //Update the input value and the cart
                inputQuantity.value = Number(inputQuantity.value) - 1;
                carrito.actualizarUnidades(product.SKU, inputQuantity.value);

                //Update the price total of each product
                let price = carrito.obtenerInformacionProducto(
                    product.SKU
                ).price_total;
                if (price <= 0) {
                    priceTotal.textContent = `0${currency}`;
                } else {
                    priceTotal.textContent = `${Number(price).toFixed(
                        2
                    )}${currency}`;
                }
                //Update total chart
                showTotal(product);
            }
        });

        //Event for input quantity change
        inputQuantity.addEventListener("change", () => {
            //Check that the input value is non-negative and an integer
            let value = parseInt(inputQuantity.value, 10);
            if (isNaN(value) || value < 0) {
                value = 0;
            }

            //Update the input value and the cart
            inputQuantity.value = value;
            carrito.actualizarUnidades(product.SKU, value);

            //Update the price total of each product
            let price = carrito.obtenerInformacionProducto(
                product.SKU
            ).price_total;

            if (price <= 0) {
                priceTotal.textContent = `0${currency}`;
            } else {
                priceTotal.textContent = `${Number(price).toFixed(
                    2
                )}${currency}`;
            }
            //Update total chart
            showTotal(product);
        });

        //Add the row to the DOM
        productsList.append(tr);
    });

    //Manage the total element chart
    function showTotal(currentItem) {
        const currentProducts = carrito.obtenerCarrito().products;
        const productListItemTp2 = document.querySelector(
            "#products-list-item2"
        );
        const productsList2 = document.querySelector(".products-list2");

        //Check if the product already exists in the aside chart
        let productTotalDiv = productsList2.querySelector(
            `.products-total[data-sku="${currentItem.SKU}"]`
        );
        const item = currentProducts.find(
            (item) => item.sku === currentItem.SKU
        );

        //If the product exists, just update
        if (item && item.quantity > 0) {
            if (productTotalDiv) {
                productTotalDiv.querySelector(
                    ".product-price-total"
                ).textContent = `${Number(item.price_total).toFixed(
                    2
                )}${currency}`;
            } else {
                //If the product does not exist, create a new one
                const newProductListItem =
                    productListItemTp2.content.cloneNode(true);
                const div = newProductListItem.querySelector(".products-total");
                const productPrice = div.querySelector(".product-price-total");
                const productName = div.querySelector(".product-name-total");

                div.setAttribute("data-sku", currentItem.SKU);
                productName.textContent = currentItem.title;
                productPrice.textContent = `${Number(item.price_total).toFixed(
                    2
                )}${currency}`;

                productsList2.append(div);
            }
        } else {
            //Remove the product with quantity 0 from the aside chart
            if (productTotalDiv) {
                productTotalDiv.remove();
            }
        }

        // Update the total price in the aside chart
        const totalPrice = carrito.obtenerCarrito().total;
        if (totalPrice <= 0) {
            document.querySelector(
                ".price-total-aside"
            ).textContent = `0${currency}`;
        } else {
            document.querySelector(
                ".price-total-aside"
            ).textContent = `${Number(totalPrice).toFixed(2)}${currency}`;
        }
    }
};
