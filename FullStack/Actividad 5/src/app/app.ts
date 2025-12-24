/*
  File: app.ts
  Author: Gentzane Pastor
  Date: 13/07/2025
  Description: Componente principal del proyecto de Angular.
*/
import { Component } from '@angular/core';
import { BlogComponent } from './components/blog/blog.component';
import { INoticia } from './interfaces/inoticia.interface';

@Component({
    selector: 'app-root',
    imports: [BlogComponent],
    templateUrl: './app.html',
    styleUrl: './app.css'
})
export class App {
    
    protected title = 'Actividad5';

    //Array de noticias inicializada con dos noticias que se pasa como Input para el blog component
    array2Noticias: INoticia[] = [
        {
            id: 1,
            titulo: "One Piece revela nuevo tráiler del arco de Elbaf",
            img: "https://www.dexerto.com/cdn-image/wp-content/uploads/2024/10/21/one-piece-prince-loki.jpeg?width=1200&quality=60&format=auto",
            texto: "La esperada llegada al país de los gigantes, Elbaf, ya tiene tráiler oficial en el anime de One Piece. Los fans están emocionados por la animación y los nuevos personajes que se presentarán en este arco cargado de acción, emoción y revelaciones importantes para la historia de Luffy y su tripulación.",
            fecha: "2025-07-03"
        },
        {
            id: 2,
            titulo: "Studio Ghibli celebra su 40 aniversario con una exposición internacional",
            img: "https://storage.googleapis.com/tribunamexico/2025/06/Studio-Ghibli-Aniversario-2-905x613.jpg.webp",
            texto: "Con motivo de su 40 aniversario, Studio Ghibli ha anunciado una exposición internacional que recorrerá ciudades como París, Nueva York y Tokio. La muestra incluirá bocetos originales, recreaciones de escenarios y proyecciones especiales de sus películas más queridas, como Mi vecino Totoro o El viaje de Chihiro.",
            fecha: "2025-07-06"
        }
    ]
}
