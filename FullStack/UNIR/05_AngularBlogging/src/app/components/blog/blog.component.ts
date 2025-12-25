/*
  File: blog.component.ts
  Author: Gentzane Pastor
  Date: 13/07/2025
  Description: Component blog que carga y muestra una lista de noticias.
*/
import { Component, Input } from '@angular/core';
import { INoticia } from '../../interfaces/inoticia.interface';
import { FormsModule } from '@angular/forms';

@Component({
    selector: 'app-blog',
    imports: [FormsModule ],
    templateUrl: './blog.component.html',
    styleUrl: './blog.component.css',
})
export class BlogComponent {

    //Noticia que se usa para los inputs del formulario
    noticia: INoticia = { id: 0,  titulo: '', img: '', texto: '', fecha: '' };
    
    //Array de noticias que se recive del app
    @Input() arrayNoticias: INoticia[] = [];

    //Añade la noticia actual al array y reinicia los campos
    cargarDatos() {
        this.noticia.id = this.arrayNoticias.length + 1;
        this.arrayNoticias.push(this.noticia);
        this.noticia = {id: 0, titulo: '', img: '', texto: '', fecha: ''};
    }
}
