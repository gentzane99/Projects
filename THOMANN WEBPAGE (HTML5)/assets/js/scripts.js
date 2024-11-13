// Cerciorarme de que cuando el event listener sepa que ha terminado la carga de todos los elementos
window.addEventListener("load", function(){

    new Glider(document.querySelector(".carrusel-items"), {

        //Glider es mobile first
        slidesToShow: 1, 
        slidesToScroll: 1,
        draggable: true,
        dots: ".carrusel-indicadores",
        responsive:[
            {
                //pantallas mayores de >= 798px (tablets)
                breakpoint: 768,
                settings:{
                    slidesToShow:2,
                    slidesToScroll:1,
                    draggable: false,
                    arrows: {
                        prev: ".boton-carrusel-anterior",
                        next: ".boton-carrusel-siguiente"
                    }
                }
            },
            {
                //pantallas mayores de >= 992px 
                breakpoint: 992,
                settings:{
                    slidesToShow:3,
                    slidesToScroll:1,
                    draggable: false,
                    arrows: {
                        prev: ".boton-carrusel-anterior",
                        next: ".boton-carrusel-siguiente"
                    }
                }
            }
        ]
    });

const menuBar = this.document.getElementById("menu-bar");
const menuDesplegableELement = this.document.getElementById("menu-desplegable");

const botonPrincipal1 = this.document.getElementById("boton-principal1");
const botonPrincipal2 = this.document.getElementById("boton-principal2");
const botonPrincipal3 = this.document.getElementById("boton-principal3");
const botonPrincipal4 = this.document.getElementById("boton-principal4");
const botonPrincipal5 = this.document.getElementById("boton-principal5");
const botonPrincipal6 = this.document.getElementById("boton-principal6");

menuBar.addEventListener("click", function(){

    menuDesplegableELement.classList.toggle("menu-desplegable-show");

});

botonPrincipal1.addEventListener("click", function(){

    menuDesplegableELement.classList.toggle("menu-desplegable-show");

});

botonPrincipal2.addEventListener("click", function(){

    menuDesplegableELement.classList.toggle("menu-desplegable-show");

});

botonPrincipal3.addEventListener("click", function(){

    menuDesplegableELement.classList.toggle("menu-desplegable-show");

});

botonPrincipal4.addEventListener("click", function(){

    menuDesplegableELement.classList.toggle("menu-desplegable-show");

});

botonPrincipal5.addEventListener("click", function(){

    menuDesplegableELement.classList.toggle("menu-desplegable-show");

});

botonPrincipal6.addEventListener("click", function(){

    menuDesplegableELement.classList.toggle("menu-desplegable-show");

});









});