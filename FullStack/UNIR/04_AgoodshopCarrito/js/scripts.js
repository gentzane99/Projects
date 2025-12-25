/*
  File: scripts.js
  Author: Gentzane Pastor
  Date: 30/06/2025
  Description: Javascript file to load the json with the products.
*/
document.addEventListener("DOMContentLoaded", () => {
    // Importing the json file to fetch products
    const request = fetch('./json/products.json');

    // Request to fetch the products was successful
    request
        .then((res) => res.json())
        .then((products) => {
            init(products);
        });

    //Error handling for the fetch request
    request.catch((err) => {
        console.log("Error al cargar los productos:", err);
    });
});
